#ifndef __ImageAcquisitionModule_h
#define __ImageAcquisitionModule_h

#include <pcl/MetaModule.h>

namespace pcl
{

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
