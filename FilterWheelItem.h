#ifndef __FilterWheelItem_h
#define __FilterWheelItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>

namespace pcl
{
    class IPixInsightFilterWheel;
   class FilterWheelItem
   {
   public:
       pcl_bool enabled;
       String driverPath;
       String filterWheelName;
       mutable IPixInsightFilterWheel *fw;
#ifdef __PCL_MACOSX
       mutable void* libHandle;
#endif
#ifdef __PCL_WINDOWS

       mutable HINSTANCE libHandle;
#endif

       FilterWheelItem( );
       FilterWheelItem( const String& cn, const String& dp);
       FilterWheelItem( const FilterWheelItem& x );

       void AddToRawData( ByteArray& ) const;
       ByteArray::const_iterator GetFromRawData( ByteArray::const_iterator );
   };
}

#endif
