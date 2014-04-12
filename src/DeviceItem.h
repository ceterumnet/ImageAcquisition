// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __DeviceItem_h
#define __DeviceItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>
#include "IPixInsightDevice.h"

namespace pcl
{

   typedef IPixInsightDevice* (*MyFuncPtr)();

   class DeviceItem
   {
   public:
       pcl_bool enabled;
       String driverPath;

       DeviceItem( );
       DeviceItem( const String& dp);
       DeviceItem( const DeviceItem& x );

       virtual IPixInsightDevice* GetDevice() const = 0;

       void InitializeDevice( );
	   void DisposeDevice();

   protected:
       void *libHandle;
       IPixInsightDevice *device;
   };
}

#endif
