#define MODULE_VERSION_MAJOR     00
#define MODULE_VERSION_MINOR     01
#define MODULE_VERSION_REVISION  01
#define MODULE_VERSION_BUILD     0001
#define MODULE_VERSION_LANGUAGE  eng

#define MODULE_RELEASE_YEAR      2011
#define MODULE_RELEASE_MONTH     1
#define MODULE_RELEASE_DAY       9

// #define MODULE_UNIQUE_ID

#include "ImageAcquisitionModule.h"

namespace pcl
{


//
//    // Template instantiation for pcl_bool type
//    void AddToRawData( ByteArray& b, const pcl_bool& pb )
//    {
//       AddToRawData( b, uint8(pb) );
//    }
//
//    ByteArray::const_iterator GetFromRawData( pcl_bool& pb, ByteArray::const_iterator i )
//    {
//       return GetFromRawData( pb, i );
//    }

// ----------------------------------------------------------------------------

ImageAcquisitionModule::ImageAcquisitionModule() : MetaModule()
{
}

const char* ImageAcquisitionModule::Version() const
{
   return PCL_MODULE_VERSION( MODULE_VERSION_MAJOR,
                              MODULE_VERSION_MINOR,
                              MODULE_VERSION_REVISION,
                              MODULE_VERSION_BUILD,
                              MODULE_VERSION_LANGUAGE );
}

IsoString ImageAcquisitionModule::Name() const
{
   return "ImageAcquisitionModule";
}

String ImageAcquisitionModule::Description() const
{
   return "ImageAcquisitionModule Process Module";
}

String ImageAcquisitionModule::Company() const
{
   return "3Factors, LLC";
}

String ImageAcquisitionModule::Author() const
{
   return "ImageAcquisitionModule: David Raphael";
}

String ImageAcquisitionModule::Copyright() const
{
   return "Copyright (c) 2011, 3Factors, LLC";
}

String ImageAcquisitionModule::TradeMarks() const
{
   return "Astrofactors";
}

String ImageAcquisitionModule::OriginalFileName() const
{
#ifdef __PCL_LINUX
   return "ImageAcquisitionModule-pxm.so";
#endif
#ifdef __PCL_FREEBSD
   return "ImageAcquisitionModule-pxm.so";
#endif
#ifdef __PCL_MACOSX
   return "ImageAcquisitionModule-pxm.dylib";
#endif
#ifdef __PCL_WINDOWS
   return "ImageAcquisitionModule-pxm.dll";
#endif
}

void ImageAcquisitionModule::GetReleaseDate( int& year, int& month, int& day ) const
{
   year  = MODULE_RELEASE_YEAR;
   month = MODULE_RELEASE_MONTH;
   day   = MODULE_RELEASE_DAY;
}

#define READABLE_VERSION_NUMBERS_1( a, b, c, d )  #a + '.' + #b + '.' + #c + '.' + #d
#define READABLE_VERSION_NUMBERS( a, b, c, d ) READABLE_VERSION_NUMBERS_1( a, b, c, d )

String ImageAcquisitionModule::ReadableVersion()
{
   return String( "ImageAcquisitionModule module " ) +
            READABLE_VERSION_NUMBERS( MODULE_VERSION_MAJOR,
                                      MODULE_VERSION_MINOR,
                                      MODULE_VERSION_REVISION,
                                      MODULE_VERSION_BUILD );
}

// ----------------------------------------------------------------------------

} // pcl

// ----------------------------------------------------------------------------
// PCL_MODULE_EXPORT int InstallPixInsightModule( int )
//
// Module installation routine.
// If defined, the PixInsight application calls this routine just after
// loading the module shared library.
// ----------------------------------------------------------------------------

PCL_MODULE_EXPORT
int InstallPixInsightModule( int mode )
{
	
   // When the PixInsight application installs this module, we just have to
   // instantiate the meta objects describing it.

   new pcl::ImageAcquisitionModule;

   // The mode argument tells us what kind of installation is being requested
   // by the PixInsight application. Incomplete installation requests only need
   // module descriptions.

   if ( mode == pcl::InstallMode::FullInstall )
   {
	 new pcl::ImageAcquisitionSettingsProcess;
	 //pcl::ImageAcquisitionSettingsInterface *iaSettings = 
     new pcl::ImageAcquisitionSettingsInterface;
	 new pcl::ExposeImageProcess;
     new pcl::ExposeImageInterface;
   }

   // Return zero to signal successful installation
   return 0;
}

// ****************************************************************************
// EOF ImageAcquisitionModule.cpp - Released 2011/01/09 09:34:27 UTC
