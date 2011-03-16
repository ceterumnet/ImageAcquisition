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

    /*
     * Adds an object t to a ByteArray stream b.
     */
    template <class T>
    void AddToRawData( ByteArray& b, const T& t )
    {
       const uint8* p = reinterpret_cast<const uint8*>( &t );
       b.Add( p, p+sizeof( t ) );
    }

    /*
     * Retrieves an object t from a ByteArray stream at the specified location i.
     * Returns an iterator located at the next position in the ByteArray stream.
     */
    template <class T>
    ByteArray::const_iterator GetFromRawData( T& t, ByteArray::const_iterator i )
    {
       t = *reinterpret_cast<const T*>( i );
       return i + sizeof( T );
    }

    /*
     * Adds the contents of a string s to a ByteArray stream b.
     */
    template <class S>
    void AddStringToRawData( ByteArray& b, const S& s )
    {
       AddToRawData( b, uint32( s.Length() ) );
       if ( !s.IsEmpty() )
          b.Add( reinterpret_cast<const uint8*>( s.Begin() ), reinterpret_cast<const uint8*>( s.End() ) );
    }

    /*
     * Loads a string's character contents from the specified location i on a ByteArray.
     * Returns an iterator located at the next position in the ByteArray stream.
     */
    template <class S>
    ByteArray::const_iterator GetStringFromRawData( S& s, ByteArray::const_iterator i )
    {
       uint32 n;
       i = GetFromRawData( n, i );
       if ( n > 0 )
       {

          s.Assign( reinterpret_cast<const typename S::char_type*>( i ), 0, n );
          i += n * sizeof( typename S::char_type );
       }
       else
          s.Clear();
       return i;
    }

    /*
     * Template instantiations for the String type.
     */

    void AddToRawData( ByteArray& b, const String& s )
    {
       AddStringToRawData( b, s );
    }

    ByteArray::const_iterator GetFromRawData( String& s, ByteArray::const_iterator i )
    {
       return GetStringFromRawData( s, i );
    }

    /*
     * Template instantiations for the IsoString type.
     */

    void AddToRawData( ByteArray& b, const IsoString& s )
    {
       AddStringToRawData( b, s );
    }

    ByteArray::const_iterator GetFromRawData( IsoString& s, ByteArray::const_iterator i )
    {
       return GetStringFromRawData( s, i );
    }

    // Template instantiation for pcl_bool type
    void AddToRawData( ByteArray& b, const pcl_bool& pb )
    {
       AddToRawData( b, pb );
    }

    ByteArray::const_iterator GetFromRawData( pcl_bool& pb, ByteArray::const_iterator i )
    {
       return GetFromRawData( pb, i );
    }

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
