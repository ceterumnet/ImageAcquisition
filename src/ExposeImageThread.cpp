#include "ExposeImageThread.h"

namespace pcl
{
    ExposeImageThread::ExposeImageThread( IPixInsightCamera *_cam, double _exposureDuration, short _binX, short _binY, long _startX, long _startY, long _numX, long _numY)
    {
        cam = _cam;
        binX = _binX;
        binY = _binY;
        startX = _startX;
        startY = _startY;
        numX = _numX;
        numY = _numY;
        exposureDuration = _exposureDuration;
        exposing = true;
    }

    ExposeImageThread::~ExposeImageThread()
    {
    }

    IPixInsightCamera::CameraStateEnum ExposeImageThread::CameraState()
    {
        return cam->CameraState();
    }

    const bool ExposeImageThread::IsExposing()
    {
        return exposing;
    }

    void ExposeImageThread::Run()
    {
        ExposeImageInstance::exposeImageData->mutex.Lock();
        ExposeImageInstance::exposeImageData->imageReady = false;
        bool d_abort = ExposeImageInstance::exposeImageData->abort;
        ExposeImageInstance::exposeImageData->mutex.Unlock();
        cam->SetBinX(binX);
        cam->SetBinY(binY);
        // This might create bugs...
        if(numX > 0)
            cam->SetNumX(numX - startX);
        else
            cam->SetNumX(cam->CameraXSize()/binX);
        if(numY > 0)
            cam->SetNumY(numY - startY);
        else
            cam->SetNumY(cam->CameraYSize()/binY);
        cam->SetStartX(startX);
        cam->SetStartY(startY);

        cam->StartExposure( exposureDuration );

        if (cam->getCameraType()==IPixInsightCamera::TypeDSLR){
            pcl::Sleep( 5/* FIXME: sec - should be replaced by IsDownload completed event*/ );
        }
        else
            pcl::Sleep(exposureDuration);

        while ( !cam->ImageReady() && cam->Connected() && (cam->CameraState()!=cam->CameraError))
        {
            // Possibly set the state of the data to "reading" here later...
            pcl::Sleep( .1 );
            // Also, we need to handle aborting images here.
        };

        //now the image is ready ...
        ExposeImageInstance::exposeImageData->mutex.Lock();
        exposing = false;
        ExposeImageInstance::exposeImageData->imageReady = true;
        ExposeImageInstance::exposeImageData->mutex.Unlock();
    }
}
