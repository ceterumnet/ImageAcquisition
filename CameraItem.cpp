#include "CameraItem.h"
#include "ImageAcquisitionModule.h"
#include "SerializableTraits.h"
#include <pcl/Console.h>
#ifdef __PCL_MACOSX
#include <dlfcn.h>
#endif
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

    IPixInsightCamera* CameraItem::GetDevice()
    {
        return cam;
    }

    typedef IPixInsightCamera* (*MyFuncPtr)();
    void CameraItem::InitializeCamera( )
    {
        IsoString theString = driverPath;
        const char * chars = theString.c_str();
        MyFuncPtr InitializePtr = NULL;
        if ( GetDevice() == 0 )
        {
#ifdef __PCL_WINDOWS

            //HINSTANCE loadedLib = NULL;
            libHandle = LoadLibrary(chars);
            InitializePtr = (MyFuncPtr) (// get the function pointer
                    GetProcAddress( libHandle, "InitializeCamera" )
            );

#endif
#ifdef __PCL_MACOSX
            libHandle = dlopen( chars, RTLD_NOW );
            if ( libHandle == NULL )
            {
                throw Error( "Problem loading driver" );
                Console().WriteLn( dlerror() );
            }
            else
            {
                InitializePtr = (MyFuncPtr) dlsym( libHandle, "InitializeCamera" );
            }
#endif

            if ( InitializePtr == NULL )
            {
                throw Error( "Failed to load library.  Make sure that you've pointed to a valid driver file." );
            }
            else
            {
                // TODO: Add validation here that the cast was successful.  I think this
                // could be a problem if someone tries to load another driver that also responds to
                // this method...especially as we abstract the loading architecture of the drivers.
                cam = dynamic_cast<IPixInsightCamera *> ( InitializePtr() );
                String theString = cam->Description();
                Console().Write( "Loaded driver: " );
                Console().WriteLn( theString );
            }
        }
        else
        {
            Console().Write( "Camera Already Initialized: " );
        }
    }
}
