#ifndef __CameraData_h
#define __CameraData_h
#include "IPixInsightCamera.h"
#include <pcl/Mutex.h>
namespace pcl 
{
	struct CameraData 
	{
		Mutex mutex;	
		CameraData() : mutex(), cam(0) {};
		IPixInsightCamera *cam;
	};
	

PCL_BEGIN_LOCAL
	extern CameraData* cameraData;
PCL_END_LOCAL
}

#endif

