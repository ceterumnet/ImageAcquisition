#include "DeviceItem.h"
#include "ImageAcquisitionModule.h"
#include "SerializableTraits.h"
#include <pcl/Console.h>

#ifdef __PCL_MACOSX
#include <dlfcn.h>
#endif

namespace pcl
{
    DeviceItem::DeviceItem( ) : enabled( false ), driverPath( String() ), libHandle( 0 ), device( 0 )
    {

    };

    DeviceItem::DeviceItem( const String& dp) : enabled( false ), driverPath( dp ), libHandle( 0 ), device( 0 )
    {

    };

    DeviceItem::DeviceItem( const DeviceItem& x ) : enabled( x.enabled ), driverPath( x.driverPath), libHandle( x.libHandle ), device( x.device )
    {

    };

    void DeviceItem::InitializeDevice( )
    {
        IsoString theString = driverPath;
        const char * chars = theString.c_str();
        MyFuncPtr InitializePtr = NULL;
        if ( device == 0 )
        {
#ifdef __PCL_WINDOWS
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
                //Console().WriteLn( dlerror() );
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
                //InvokeInitializePtr( InitializePtr );
                //device = dynamic_cast<IPixInsightCamera*>( InitializePtr() );
                device = dynamic_cast<IPixInsightDevice*>( InitializePtr() );
                if( device )
                {
                    this->device = device;
                }
                else
                {
                    throw Error("Failed to invoke InitializePtr()");
                }
            }
        }
        else
        {
            Console().Write( "Camera Already Initialized: " );
        }
    }

}
