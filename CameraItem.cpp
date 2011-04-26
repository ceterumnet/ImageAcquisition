// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
