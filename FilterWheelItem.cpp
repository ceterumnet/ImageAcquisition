#include "FilterWheelItem.h"
#include "ImageAcquisitionModule.h"
#include "SerializableTraits.h"
#include <pcl/Console.h>
namespace pcl
{

    FilterWheelItem::FilterWheelItem( ) :
        enabled( false ), driverPath( String() ), filterWheelName( String() ), fw( 0 ), libHandle( 0 )
    {
    }

    FilterWheelItem::FilterWheelItem( const String& fn, const String& dp ) :
        enabled( false ), driverPath( dp ), filterWheelName( fn ), fw( 0 ), libHandle( 0 )
    {
    }
    FilterWheelItem::FilterWheelItem( const FilterWheelItem& x ) :
        enabled( x.enabled ), driverPath( x.driverPath ), filterWheelName( x.filterWheelName ), fw( x.fw ), libHandle( x.libHandle )
    {
    }
    void FilterWheelItem::AddToRawData( ByteArray& b) const
    {
        pcl::AddToRawData( b, filterWheelName );
        pcl::AddToRawData( b, driverPath );
        pcl::AddToRawData( b, enabled );
    }

    ByteArray::const_iterator FilterWheelItem::GetFromRawData( ByteArray::const_iterator i)
    {
        return pcl::GetFromRawData( enabled,
                  pcl::GetFromRawData( driverPath,
                     pcl::GetFromRawData( filterWheelName, i ) ) );

    }
}
