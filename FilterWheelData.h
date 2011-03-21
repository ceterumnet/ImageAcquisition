#ifndef __FilterWheelData_h
#define __FilterWheelData_h
#include "IPixInsightFilterWheel.h"
#include <pcl/Mutex.h>
namespace pcl
{
    struct FilterWheelData
    {
        Mutex mutex;
        IPixInsightFilterWheel *fw;
        FilterWheelData() : mutex(), fw(0) {};
    };


PCL_BEGIN_LOCAL
    extern FilterWheelData* filterWheelData;
PCL_END_LOCAL
}

#endif

