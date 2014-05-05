#ifndef __ExposeImageThread_h
#define __ExposeImageThread_h

#include <pcl/Mutex.h>
#include <pcl/ProcessInterface.h>
#include "CameraData.h"
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

    class ExposeImageThread : public Thread
    {
    public:
        ExposeImageThread( IPixInsightCamera *_cam,
                           double _exposureDuration,
                           short _binX,
                           short _binY,
                           long _startX,
                           long _startY,
                           long _numX,
                           long _numY);

        virtual ~ExposeImageThread();
        IPixInsightCamera::CameraStateEnum CameraState();
        const bool IsExposing();
        virtual void Run();

    private:
        short binX;
        short binY;
        long startX;
        long startY;
        long numX;
        long numY;
        bool exposing;
        IPixInsightCamera *cam;
        double exposureDuration;
        //friend class ExposeImageProcess;


    };
}
#endif
