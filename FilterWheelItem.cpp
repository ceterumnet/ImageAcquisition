// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
