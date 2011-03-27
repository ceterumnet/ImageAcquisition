#ifndef __CameraItem_h
#define __CameraItem_h
#include <pcl/String.h>
#include <pcl/Defs.h>
#include <pcl/MetaParameter.h>
#include "DeviceItem.h"
#include "IPixInsightCamera.h"
namespace pcl
{
   class CameraItem : public DeviceItem
   {
   public:
       String cameraName;

       CameraItem( );
       CameraItem( const String& cn, const String& dp);
       CameraItem( const CameraItem& x );
       //void InitializeDevice( );
       void AddToRawData( ByteArray& ) const;
       ByteArray::const_iterator GetFromRawData( ByteArray::const_iterator );
       virtual IPixInsightCamera* GetDevice() const;
       void InvokeInitializePtr( MyFuncPtr InitializePtr );
       //void SetDevice( IPixInsightCamera *device );
   };
}

#endif
