#ifndef __CameraItem_h
#define __CameraItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>

namespace pcl
{
    class IPixInsightCamera;
   class CameraItem
   {
   public:
       pcl_bool enabled;
       String driverPath;
       String cameraName;
       mutable IPixInsightCamera *cam;
#ifdef __PCL_MACOSX
       mutable void* libHandle;
#endif
#ifdef __PCL_WINDOWS

       mutable HINSTANCE libHandle;
#endif

       CameraItem( const String& cn = String(), const String& dp = String());
       CameraItem( const CameraItem& x );

       void AddToRawData( ByteArray& ) const;

       ByteArray::const_iterator GetFromRawData( ByteArray::const_iterator );
   };
}

#endif
