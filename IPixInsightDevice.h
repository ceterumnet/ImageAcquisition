// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __IPixInsightDevice_h
#define __IPixInsightDevice_h
#include <pcl/String.h>
#include <pcl/Vector.h>


namespace pcl
{
    class IPixInsightDevice
    {
    public:
        virtual bool Connected() = 0;
        virtual int SetConnected(bool) = 0;
        virtual String Description() = 0;
    };
}

#endif
