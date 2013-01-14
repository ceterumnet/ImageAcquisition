// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#include "ExposeImageInstance.h"
#include "CameraData.h"
#include "parsers.h"
#include <time.h>
#include <pcl/Histogram.h>
#include <pcl/HistogramTransformation.h>

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
                binModeX( 1 ), binModeY( 1 ), subFrameX1( 0 ), subFrameY1( 0 ), subFrameX2( 0 ), subFrameY2( 0 ), delayBetweenExposures( 1 ),
                fileOutputPath(""), fileOutputPattern("")
    {

    }
    ExposeImageInstance::ExposeImageInstance( const ExposeImageInstance& x ) :
        ProcessImplementation( x )
    {
        Assign( x );
    }

		/*, exposureDuration( x.exposureDuration ), exposureCount( x.exposureCount ),
            cameraName( x.cameraName ), setTemperature( x.setTemperature ), filter( x.filter ),
            binModeX( x.binModeX ), binModeY( x.binModeY ), subFrameX1( x.subFrameX1 ), subFrameY1( x.subFrameX2 ),
            subFrameX2( x.subFrameX2 ), subFrameY2( x.subFrameY2 ), delayBetweenExposures( x.delayBetweenExposures ),
            fileOutputPath( x.fileOutputPath ), fileOutputPattern( x.fileOutputPattern )*/

    void ExposeImageInstance::SerializeParameters( ByteArray &bArray )
    {

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
        bool canExecute = true;

        if( fileOutputPath.IsEmpty() )
        {
            whyNot += "\nYou must define an output directory.";
            canExecute = false;
        }
        else if ( !File::DirectoryExists( fileOutputPath ) )
        {
            whyNot += "\n" + fileOutputPath + " Doesn't exist.  You must create this directory if you want to use it.";
            canExecute = false;
        }

        if( fileOutputPattern == "" )
        {
            whyNot += "\nYou must define an output pattern.";
            canExecute = false;
        }

        return canExecute;
    }

    void aLogger( String text )
    {
        Console().Write( text );
    }

    bool ExposeImageInstance::ExecuteGlobal()
    {
		Console console;
		console << "executing global: \n";
        {
            String why;
            if ( !CanExecuteGlobal( why ) )
                throw Error( why );
        }

        ExposeImages();
        return true;
    }

    bool ExposeImageInstance::ExposeImages()
    {
        if( data == 0 )
            data = new ExposeImageData;
		else {
			delete data;
			data = new ExposeImageData;
		}

        Console console;

        console << "Starting ExposeImage Process: \n";
        IPixInsightCamera *cam = cameraData->cam;
		console << "Camera state: " << cameraData->cam->CameraState() << "\n";
        exposeThread = new ExposeImageThread( cameraData->cam, exposureDuration, exposureCount );
        console << "exposeThread->Start()\n";
		exposeThread->Start();
		
        OutputData __data;
        time_t rawtime;
        time( &rawtime );
        struct tm * timeinfo;
        timeinfo = localtime ( &rawtime );

        __data.YYYY        = String( timeinfo->tm_year + 1900 );
        __data.MM          = String( timeinfo->tm_mon + 1 );
        __data.DD          = String( timeinfo->tm_mday );
        __data.TARGET      = String( "" );
        __data.SEQUENCE_ID = String( "" );
        __data.EXP_NUM     = 0;
        __data.FILTER      = filter;

		console << "creating ImageWindow(...)\n";
        //TODO: We are reusing this window...maybe this should be an option?
        ImageWindow window( cam->NumX(), // width
                cam->NumY(), // height
                1, // numberOfChannels
                16, // bitsPerSample
                false, // floatSample
                false, // color
                true, // initialProcessing
                String( "last_exposure" ) // id
                );

        //TODO:  This code is messy.  Currently, there are 2 threads that keep running and waiting for eachother etc...
        //       What I need to do here is create and destroy the thread for each exposure...
        while ( exposeThread->IsExposing() )
        {
			// These 2 lines allow PixInsight to stay responsive while it is exposing
            pcl::Sleep( .10 );
            ProcessInterface::ProcessEvents();

            data->mutex.Lock();			
            bool myImageReady = data->imageReady;
            data->mutex.Unlock();

            if ( myImageReady )
            {
                FILEPATH:

                __data.EXP_NUM += 1;
                String theFilename = fileOutputPattern + "-" + String(__data.EXP_NUM);
                String fileName = GenerateOutputFileName( theFilename, __data );
                FileFormat outputFormat( ".fit", false, true );
                FileFormatInstance outputFile( outputFormat );
                String filePath = fileOutputPath + "/" + fileName;

                if(File::Exists( filePath + ".fit" ) )
                    goto FILEPATH;

                //TODO:  Ensure that there is a trailing slash on this path...
                outputFile.Create( filePath );

                bool floatSample = false;
                ImageOptions options;
                options.bitsPerSample = 16;
                options.ieeefpSampleFormat = floatSample;
                outputFile.SetOptions( options );

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

                //Not sure if we are going to have a thread timing issue here if we have extremely fast exposures...
                if ( !outputFile.WriteImage( *image ) )
                    throw CatchedException();
				if ( !view.AreHistogramsAvailable() )
					view.CalculateHistograms();
				if ( !view.AreStatisticsAvailable() )
					view.CalculateStatistics();

				View::statistics_container S;
				View::stf_container F;

				view.GetStatistics( S );
				double c0 = 0, m = 0;
				
				c0 += S[0]->Median() + -1.25 * S[0]->AvgDev();
				m  += S[0]->Median();
				
				c0 = Range( c0, 0.0, 1.0 );
				m = HistogramTransformation::FindMidtonesBalance( .25, m - c0 );

				F.Add( new HistogramTransformation( m, c0 ) );

				view.SetScreenTransferFunctions(F);
				view.EnableScreenTransferFunctions();

				F.Destroy();
				S.Destroy();
                window.Show();
                window.ZoomToFit( false ); // don't allow zoom > 1

            }
        }
		delete exposeThread;
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
        else if ( p == TheExposureCountParameter )
        {
        }
        else if ( p == TheCameraNameParameter )
        {
            cameraName.Clear();
            if ( sizeOrLength > 0 )
                cameraName.Reserve( sizeOrLength );
        }
        else if ( p == TheDelayBetweenExposuresParameter )
        {
        }
        else if ( p == TheBinModeXParameter )
        {
        }
        else if ( p == TheBinModeYParameter )
        {
        }
        else if ( p == TheFileOutputPathParameter )
        {
            fileOutputPath.Clear();
            if ( sizeOrLength > 0 )
                fileOutputPath.Reserve( sizeOrLength );
        }
        else if ( p == TheFileOutputPatternParameter )
        {
            fileOutputPattern.Clear();
            if ( sizeOrLength > 0 )
                fileOutputPattern.Reserve( sizeOrLength );
        }
        else if ( p == TheFilterParameter )
        {
            filter.Clear();
            if ( sizeOrLength > 0 )
                filter.Reserve( sizeOrLength );
        }
        else if ( p == TheFilterWheelNameParameter )
        {
            filterWheelName.Clear();
            if ( sizeOrLength > 0 )
                filterWheelName.Reserve( sizeOrLength );
        }
        else if ( p == TheSetTemperatureParameter )
        {
        }
        else if ( p == TheSubFrameX1Parameter )
        {
        }
        else if ( p == TheSubFrameY1Parameter )
        {
        }
        else if ( p == TheSubFrameX2Parameter )
        {
        }
        else if ( p == TheSubFrameY2Parameter )
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
