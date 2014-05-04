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
#include <pcl/ErrorHandler.h>
#include "ExposeImageThread.h"

namespace pcl
{

    ExposeImageData* ExposeImageInstance::exposeImageData = 0;

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
        console.EnableAbort();
        {
            String why;
            if ( !CanExecuteGlobal( why ) )
                throw Error( why );
        }

        ExposeImages();
        return true;
    }

    bool ExposeImageInstance::ExposeImagesWithCCD()
    {
        IPixInsightCamera *cam = cameraData->cam;

        if( ExposeImageInstance::exposeImageData == 0 )
            ExposeImageInstance::exposeImageData = new ExposeImageData;

        Console console;

        console << "Starting ExposeImage Process: \n";

        console << "Camera state: " << cameraData->cam->CameraState() << "\n";
        console << "startX: " << subFrameX1 << "\n";

        for(int exp_i = 0;exp_i < exposureCount;++exp_i) {
            exposeThread = new ExposeImageThread( cameraData->cam, exposureDuration, binModeX, binModeY, subFrameX1, subFrameY1, subFrameX2, subFrameY2);

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

            bool myImageReady = false;
            // Wait for thread to finish exposure
            while ( !myImageReady )
            {
                // These 2 lines allow PixInsight to stay responsive while it is exposing
                pcl::Sleep( .10 );
                ProcessInterface::ProcessEvents();
                ExposeImageInstance::exposeImageData->mutex.Lock();
                myImageReady = ExposeImageInstance::exposeImageData->imageReady;
                ExposeImageInstance::exposeImageData->mutex.Unlock();
            }

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

            ExposeImageInstance::exposeImageData->mutex.Lock();
            cam->ImageArray( image );
            ExposeImageInstance::exposeImageData->mutex.Unlock();


            //Not sure if we are going to have a thread timing issue here if we have extremely fast exposures...
            if ( !outputFile.WriteImage( *image ) )
                throw CatchedException();
            if ( !view.AreHistogramsAvailable() )
                view.CalculateHistograms();
            if ( !view.AreStatisticsAvailable() )
                view.CalculateStatistics();
            View::statistics_list S;
            //View::statistics_container S;
            View::stf_list F;
            //View::stf_container F;

            view.GetStatistics( S );
            double c0 = 0, m = 0;

            c0 += S[0]->Median() + -1.25 * S[0]->AvgDev();
            m  += S[0]->Median();

            c0 = Range( c0, 0.0, 1.0 );

            m = HistogramTransformation::MTF(.25, m - c0);


            F.Add( new HistogramTransformation( m, c0 ) );

            view.SetScreenTransferFunctions(F);
            view.EnableScreenTransferFunctions();

            F.Destroy();
            S.Destroy();

            window.ZoomToFit( false ); // don't allow zoom > 1
            window.Show();

            delete exposeThread;
            delete ExposeImageInstance::exposeImageData;
            ExposeImageInstance::exposeImageData = new ExposeImageData;
        }
        return true;
    }

    bool ExposeImageInstance::ExposeImagesWithDSLR()
    {
        if( ExposeImageInstance::exposeImageData == 0 )
            ExposeImageInstance::exposeImageData = new ExposeImageData;

        Console console;

        // Enable abort button
        console.EnableAbort();

        console << "Starting ExposeImage Process: \n";

        IPixInsightCamera *cam = cameraData->cam;
        console << "Camera state: " << cameraData->cam->CameraState() << "\n";

        for(int exp_i = 0;exp_i < exposureCount;++exp_i) {
            exposeThread = new ExposeImageThread( cameraData->cam, exposureDuration, binModeX, binModeY, 0, 0, 0, 0);
            console << "exposeThread->Start()\n";

            exposeThread->Start();



            bool myImageReady = false;
            bool doAbort     = false;
            // Wait for thread to finish exposure
            console <<"Exposure duration:   0 s.";
            while ( !myImageReady && !doAbort )
            {
                // These 2 lines allow PixInsight to stay responsive while it is exposing#
                int expTime=(int) cam->LastExposureDuration();
                pcl::IsoString expTime_str = pcl::IsoString(expTime);

                console <<"\b\b\b\b\b\b\b"<<String().Format("%4d s.",(int) cam->LastExposureDuration());
                pcl::Sleep( .10 );
                ProcessInterface::ProcessEvents();
                ExposeImageInstance::exposeImageData->mutex.Lock();
                myImageReady = ExposeImageInstance::exposeImageData->imageReady;
                ExposeImageInstance::exposeImageData->mutex.Unlock();
                doAbort = console.AbortRequested();
            }
            console <<"\n";

            if (doAbort){
                console <<"Received abort request. Stopping exposure and killing thread ...";console.Flush();
                cam->StopExposure();
                exposeThread->Kill();
                console <<"done.\n";
                return false;
            }

            if (cam->CameraState()==cam->CameraError)
                throw Error(String("A camera error occured! -- ") + cam->LastError());

            //pcl::String fileName(cam->getImageFileName());
            pcl::IsoString fileFormatExtension=pcl::IsoString(".CR2");
            //image exposure finished - downloading image from DSLR camera
            console <<"Start downloading image...";
            if (!cam->downloadImageFromCamera(pcl::IsoString(fileOutputPath+fileOutputPattern+IsoString(exp_i)+fileFormatExtension).c_str()))
                throw Error(pcl::String("Download failed!"));
            console <<"done.\n";


            // Load ImageWindow from file

            console << "creating ImageWindow(...)\n";

            Array<ImageWindow> imgArray = ImageWindow::Open(fileOutputPath+fileOutputPattern+IsoString(exp_i)+fileFormatExtension, IsoString("iw")+IsoString(exp_i));

            imgArray[0].ZoomToFit( false ); // don't allow zoom > 1
            imgArray[0].Show();

            delete exposeThread;
            delete ExposeImageInstance::exposeImageData;
            ExposeImageInstance::exposeImageData = new ExposeImageData;
            if (exp_i>=1){
                ImageWindow windowToClose = ImageWindow::WindowById(IsoString("iw")+IsoString(exp_i-1));
                windowToClose.Close();
            }

        }
        return true;

    }

    bool ExposeImageInstance::ExposeImages()
    {
        //FIXME Requires refactoring: Too much code dupliction
        switch (cameraData->cam->getCameraType()){
        case IPixInsightCamera::TypeCCD:
            return ExposeImagesWithCCD();
        case IPixInsightCamera::TypeDSLR:
            return ExposeImagesWithDSLR();
        default:
            return false;
        }
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
