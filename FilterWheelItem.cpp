#include "FilterWheelItem.h"
#include "ImageAcquisitionModule.h"
#include "SerializableTraits.h"
#include <pcl/Console.h>
namespace pcl
{

    FilterWheelItem::FilterWheelItem( ) : filterWheelName( String() )
    {
    }

    FilterWheelItem::FilterWheelItem( const String& fn, const String& dp ) : DeviceItem( dp ), filterWheelName( fn )
    {
    }

    FilterWheelItem::FilterWheelItem( const FilterWheelItem& x ) : DeviceItem( x ),
        filterWheelName( x.filterWheelName )
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

    IPixInsightFilterWheel* FilterWheelItem::GetDevice() const
    {
        IPixInsightFilterWheel* c = static_cast<IPixInsightFilterWheel *> ( device );
        return c;
    }
}
