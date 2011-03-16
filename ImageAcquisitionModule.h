#ifndef __ImageAcquisitionModule_h
#define __ImageAcquisitionModule_h


#include <pcl/MetaModule.h>

#include "ImageAcquisitionSettingsInterface.h"
#include "ImageAcquisitionSettingsProcess.h"
#include "ExposeImageProcess.h"
#include "ExposeImageInterface.h"
#include "CameraData.h"
#include <pcl/Console.h>

namespace pcl
{
    template <class T>
    void AddToRawData( ByteArray& b, const T& t );
    template <class T>
    ByteArray::const_iterator GetFromRawData( T& t, ByteArray::const_iterator i );
    template <class S>
    void AddStringToRawData( ByteArray& b, const S& s );
    template <class S>
    ByteArray::const_iterator GetStringFromRawData( S& s, ByteArray::const_iterator i );
    void AddToRawData( ByteArray& b, const String& s );
    ByteArray::const_iterator GetFromRawData( String& s, ByteArray::const_iterator i );
    void AddToRawData( ByteArray& b, const IsoString& s );
    ByteArray::const_iterator GetFromRawData( IsoString& s, ByteArray::const_iterator i );
    void AddToRawData( ByteArray& b, const pcl_bool& pb );
    ByteArray::const_iterator GetFromRawData( pcl_bool& pb, ByteArray::const_iterator i );

// ----------------------------------------------------------------------------
// ImageAcquisitionModule
// ----------------------------------------------------------------------------

class ImageAcquisitionModule : public MetaModule
{
public:

   ImageAcquisitionModule();

   virtual const char* Version() const;
   virtual IsoString Name() const;
   virtual String Description() const;
   virtual String Company() const;
   virtual String Author() const;
   virtual String Copyright() const;
   virtual String TradeMarks() const;
   virtual String OriginalFileName() const;
   virtual void GetReleaseDate( int& year, int& month, int& day ) const;

   static String ReadableVersion(); // for reference from ImageAcquisitionInstance
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionModule_h

// ****************************************************************************
// EOF ImageAcquisitionModule.h - Released 2011/01/09 09:34:27 UTC
