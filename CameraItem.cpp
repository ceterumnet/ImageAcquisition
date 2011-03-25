#include "CameraItem.h"
#include "ImageAcquisitionModule.h"
#include "SerializableTraits.h"
#include <pcl/Console.h>
#ifdef __PCL_MACOSX
#include <dlfcn.h>
#endif
namespace pcl
{

    CameraItem::CameraItem( ) : DeviceItem( ) , cameraName( String() )
    {

    }

    CameraItem::CameraItem( const String& cn, const String& dp ) : DeviceItem( dp ), cameraName( cn )
    {

    }

    CameraItem::CameraItem( const CameraItem& x ) : DeviceItem( x ),
        cameraName( x.cameraName )
    {

    }

    void CameraItem::AddToRawData( ByteArray& b) const
    {
        pcl::AddToRawData( b, cameraName );
        pcl::AddToRawData( b, driverPath );
        pcl::AddToRawData( b, enabled );
    }

    ByteArray::const_iterator CameraItem::GetFromRawData( ByteArray::const_iterator i)
    {
        return pcl::GetFromRawData( enabled,
                  pcl::GetFromRawData( driverPath,
                     pcl::GetFromRawData( cameraName, i ) ) );

    }

    IPixInsightCamera* CameraItem::GetDevice() const
    {
        IPixInsightCamera * c = static_cast<IPixInsightCamera *>(device);
        return c;
    }
}
