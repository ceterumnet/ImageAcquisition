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

   protected:
       void *libHandle;
       IPixInsightDevice *device;
   };
}

#endif
