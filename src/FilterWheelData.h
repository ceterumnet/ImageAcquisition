// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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

