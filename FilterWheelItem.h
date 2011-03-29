#ifndef __FilterWheelItem_h
#define __FilterWheelItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>
#include "DeviceItem.h"
#include "IPixInsightFilterWheel.h"

namespace pcl
{
   class FilterWheelItem : public DeviceItem
   {
   public:
       String filterWheelName;
       pcl_bool enabled;
       String driverPath;

       FilterWheelItem( );
       FilterWheelItem( const String& fn, const String& dp);
       FilterWheelItem( const FilterWheelItem& x );

       void AddToRawData( ByteArray& ) const;
       ByteArray::const_iterator GetFromRawData( ByteArray::const_iterator );

       virtual IPixInsightFilterWheel* GetDevice() const;

   };
}

#endif
