#include "CameraItem.h"
#include "ImageAcquisitionModule.h"
#include "SerializableTraits.h"
#include <pcl/Console.h>
namespace pcl
{

    CameraItem::CameraItem( ) :
        enabled( false ), driverPath( String() ), cameraName( String() ), cam( 0 ), libHandle( 0 )
    {
    }

    CameraItem::CameraItem( const String& cn, const String& dp ) :
        enabled( false ), driverPath( dp ), cameraName( cn ), cam( 0 ), libHandle( 0 )
    {
    }
    CameraItem::CameraItem( const CameraItem& x ) :
        enabled( x.enabled ), driverPath( x.driverPath ), cameraName( x.cameraName ), cam( x.cam ), libHandle( x.libHandle )
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
}
