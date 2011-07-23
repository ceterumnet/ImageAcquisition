// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
				//TODO: This should be IntializeDevice I think...
                    GetProcAddress( (HMODULE)libHandle, "InitializeCamera" )
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
				//TODO: This should be IntializeDevice I think...
                InitializePtr = (MyFuncPtr) dlsym( libHandle, "InitializeCamera" );
            }
#endif

            if ( InitializePtr == NULL )
            {
                throw Error( "Failed to load library.  Make sure that you've pointed to a valid driver file." );
            }
            else
            {
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
            Console().Write( "Device Already Initialized: " );
        }
    }

}
