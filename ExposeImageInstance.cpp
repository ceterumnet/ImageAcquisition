#include "ExposeImageInstance.h"

namespace pcl
{
    struct ExposeImageData
    {
       ExposeImageData() :
       mutex(), image(), imageProgress( 0 ), imageReady( false ),
       abort( false ), error( false ), paused( false ), waitingToBeRead( true ), errorMessage()
       {
       }

       Mutex       mutex;         // To protect data from concurrent accesses
       UInt16Image *image;         // The image being acquired
       int         imageProgress; // Progress indicator, e.g. from 0 to 100
       bool        imageReady;    // Flag true if a new image is now ready
       bool        abort;         // Flag true if the user wants to abort
       bool        error;         // Flag true if an error occurs
       bool        paused;
       bool        waitingToBeRead;
       String      errorMessage;  // Error information
    };

    ExposeImageData *data = 0;
    class ExposeImageThread: public Thread
    {

    public:
        ExposeImageThread( IPixInsightCamera *_cam, double _exposureDuration, uint32 _exposureCount )
        {
            cam = _cam;
            exposureDuration = _exposureDuration;
            exposureCount = _exposureCount;
            exposing = true;

        }

        virtual ~ExposeImageThread()
        {
            Console().WriteLn( "Deleted Camera Connection Thread" );
        }

        IPixInsightCamera::CameraStateEnum CameraState()
        {
            return cam->CameraState();
        }

        const bool IsExposing()
        {
            return exposing;
        }

        virtual void Run()
        {

            for ( size_type i = 0, n = exposureCount; i < n; ++i )
            {
                data->mutex.Lock();
                data->imageReady = false;
                bool d_abort = data->abort;
                data->mutex.Unlock();

                if( d_abort )
                    break;

                cam->StartExposure( exposureDuration );
                pcl::Sleep( exposureDuration );
                while ( !cam->ImageReady() )
                {
                    // Possibly set the state of the data to "reading" here later...
                    pcl::Sleep( .1 );
                };
                //now the image is ready ...
                data->mutex.Lock();
                data->imageReady = true;
                data->paused = true;
                data->mutex.Unlock();

                //wait for image var to be set...
                while( true )
                {
                    data->mutex.Lock();
                    bool wToBeRead = data->waitingToBeRead;
                    data->mutex.Unlock();
                    if( !wToBeRead )
                    {
                        break;
                    }

                    pcl::Sleep( .1 );
                }

                data->mutex.Lock();
                cam->ImageArray( data->image );
                data->paused = false;
                // This is probably not needed...may create a bug?
                data->waitingToBeRead = true;
                data->imageReady = false;
                data->mutex.Unlock();
            }

            // Exposures are finished...
            data->mutex.Lock();
            data->paused = false;
            exposing = false;
            data->imageReady = false;
            data->image = 0;
            data->waitingToBeRead = true;
            data->mutex.Unlock();
        }
    private:
        ImageWindow *window;
        bool exposing;
        IPixInsightCamera *cam;
        double exposureDuration;
        uint32 exposureCount;
    };

    ExposeImageInstance::ExposeImageInstance( const MetaProcess* m ) :
        ProcessImplementation( m ), exposureDuration( 1 ), exposureCount( 1 ), cameraName( "cam_name" ), setTemperature( -15 ), filter( "NONE" ),
                binModeX( 1 ), binModeY( 1 ), subFrameX1( 0 ), subFrameY1( 0 ), subFrameX2( 0 ), subFrameY2( 0 ), delayBetweenExposures( 1 )
    {

    }

    ExposeImageInstance::ExposeImageInstance( const ExposeImageInstance& x ) :
        ProcessImplementation( x )
    {
        Assign( x );
    }

    void ExposeImageInstance::Assign( const ProcessImplementation& p )
    {
        const ExposeImageInstance* x = dynamic_cast<const ExposeImageInstance*> ( &p );
        if ( x != 0 )
        {
            exposureCount = x->exposureCount;
            exposureDuration = x->exposureDuration;
            cameraName = x->cameraName;
            filterWheelName = x->filterWheelName;
            setTemperature = x->setTemperature;
            filter = x->filter;
            binModeX = x->binModeX;
            binModeY = x->binModeY;
            subFrameX1 = x->subFrameX1;
            subFrameY1 = x->subFrameY1;
            subFrameX2 = x->subFrameX2;
            subFrameY2 = x->subFrameY2;
            delayBetweenExposures = x->delayBetweenExposures;
            fileOutputPath = x->fileOutputPath;
            fileOutputPattern = x->fileOutputPattern;
        }
    }

    bool ExposeImageInstance::IsHistoryUpdater( const View& view ) const
    {
        return false;
    }

    bool ExposeImageInstance::CanExecuteOn( const View& view, String& whyNot ) const
    {
        whyNot = "ExposeImage can only be executed in the global context.";
        return false;
    }

    bool ExposeImageInstance::CanExecuteGlobal( String &whyNot ) const
    {
        return false;
    }

    void aLogger( String text )
    {
        Console().Write( text );
    }

    bool ExposeImageInstance::ExecuteGlobal()
    {
        {
            String why;
            if ( !CanExecuteGlobal( why ) )
                throw Error( why );

            if ( !fileOutputPath.IsEmpty() && !File::DirectoryExists( fileOutputPath ) )
                throw("The specified output directory does not exist: " + fileOutputPath);

        }
        ExposeImages();
        return true;
    }

    bool ExposeImageInstance::ExposeImages()
    {
        if( data == 0)
            data = new ExposeImageData;
        Console console;

        console << "Starting Image Exposure Process: \n";
        IPixInsightCamera *cam = TheImageAcquisitionSettingsInterface->activeCamera;
        //cam->SetLogger( &aLogger );

        exposeThread = new ExposeImageThread( TheImageAcquisitionSettingsInterface->activeCamera, exposureDuration, exposureCount );
        exposeThread->Start();

        while ( exposeThread->IsExposing() )
        {
            //console << "exposing .... \n";
            pcl::Sleep( .10 );
            ProcessInterface::ProcessEvents();

            data->mutex.Lock();
            bool myImageReady = data->imageReady;
            data->mutex.Unlock();

            if ( myImageReady )
            {
                Console().WriteLn("Image is ready...");
                ImageWindow window( cam->NumX(), // width
                        cam->NumY(), // height
                        1, // numberOfChannels
                        16, // bitsPerSample
                        false, // floatSample
                        false, // color
                        true, // initialProcessing
                        String( "exposure" ) // id
                        );
                View view = window.MainView();
                ImageVariant v = view.Image();
                UInt16Image* image = static_cast<UInt16Image*> ( v.AnyImage() );

                data->mutex.Lock();
                data->image = image;
                data->waitingToBeRead = false;
                data->mutex.Unlock();

                //wait for thread to read data from ImageArray
                while( true )
                {
                    data->mutex.Lock();
                    bool isPaused = data->paused;
                    data->mutex.Unlock();
                    if( !isPaused )
                        break;
                }

                window.Show();
                window.ZoomToFit( false ); // don't allow zoom > 1
            }
        }

        return true;
    }

    void* ExposeImageInstance::LockParameter( const MetaParameter* p, size_type tableRow )
    {
        if ( p == TheExposureDurationParameter )
            return &exposureDuration;
        if ( p == TheExposureCountParameter )
            return &exposureCount;
        if ( p == TheCameraNameParameter )
            return cameraName.c_str();
        if ( p == TheDelayBetweenExposuresParameter )
            return &delayBetweenExposures;
        if ( p == TheBinModeXParameter )
            return &binModeX;
        if ( p == TheBinModeYParameter )
            return &binModeY;
        if ( p == TheFileOutputPathParameter )
            return fileOutputPath.c_str();
        if ( p == TheFileOutputPatternParameter )
            return fileOutputPattern.c_str();
        if ( p == TheFilterParameter )
            return filter.c_str();
        if ( p == TheFilterWheelNameParameter )
            return filterWheelName.c_str();
        if ( p == TheSetTemperatureParameter )
            return &setTemperature;
        if ( p == TheSubFrameX1Parameter )
            return &subFrameX1;
        if ( p == TheSubFrameY1Parameter )
            return &subFrameY1;
        if ( p == TheSubFrameX2Parameter )
            return &subFrameX2;
        if ( p == TheSubFrameY2Parameter )
            return &subFrameY2;
        return NULL;
    }
    //
    //
    bool ExposeImageInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
    {
        if ( p == TheExposureDurationParameter )
        {
        }
        if ( p == TheExposureCountParameter )
        {
        }
        if ( p == TheCameraNameParameter )
        {
        }
        {
            cameraName.Clear();
            if ( sizeOrLength > 0 )
                cameraName.Reserve( sizeOrLength );
        }
        if ( p == TheDelayBetweenExposuresParameter )
        {
        }
        if ( p == TheBinModeXParameter )
        {
        }
        if ( p == TheBinModeYParameter )
        {
        }
        if ( p == TheFileOutputPathParameter )
        {
            fileOutputPath.Clear();
            if ( sizeOrLength > 0 )
                fileOutputPath.Reserve( sizeOrLength );
        }
        if ( p == TheFileOutputPatternParameter )
        {
            fileOutputPattern.Clear();
            if ( sizeOrLength > 0 )
                fileOutputPattern.Reserve( sizeOrLength );
        }
        if ( p == TheFilterParameter )
        {
            filter.Clear();
            if ( sizeOrLength > 0 )
                filter.Reserve( sizeOrLength );
        }
        if ( p == TheFilterWheelNameParameter )
        {
            filterWheelName.Clear();
            if ( sizeOrLength > 0 )
                filterWheelName.Reserve( sizeOrLength );
        }
        if ( p == TheSetTemperatureParameter )
        {
        }
        if ( p == TheSubFrameX1Parameter )
        {
        }
        if ( p == TheSubFrameY1Parameter )
        {
        }
        if ( p == TheSubFrameX2Parameter )
        {
        }
        if ( p == TheSubFrameY2Parameter )
        {
        }
        else
            return false;
        return true;
    }

    size_type ExposeImageInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
    {
        if ( p == TheCameraNameParameter )
            return cameraName.Length();
        if ( p == TheFileOutputPathParameter )
            return fileOutputPath.Length();
        if ( p == TheFileOutputPatternParameter )
            return fileOutputPattern.Length();
        if ( p == TheFilterParameter )
            return filter.Length();
        if ( p == TheFilterWheelNameParameter )
            return filterWheelName.Length();
        return 0;
    }

}
