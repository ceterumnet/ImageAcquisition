
#ifndef __ImageAcquisitionSettingsProcess_h
#define __ImageAcquisitionSettingsProcess_h

#include <pcl/MetaProcess.h>

namespace pcl
{

// ----------------------------------------------------------------------------

class ImageAcquisitionSettingsProcess : public MetaProcess
{
public:

   ImageAcquisitionSettingsProcess();

   virtual IsoString Id() const;
   virtual IsoString Category() const;

   virtual uint32 Version() const;

   virtual String Description() const;

   virtual const char** IconImageXPM() const;

   virtual ProcessInterface* DefaultInterface() const;

   virtual ProcessImplementation* Create() const;
   virtual ProcessImplementation* Clone( const ProcessImplementation& ) const;
};

PCL_BEGIN_LOCAL
extern ImageAcquisitionSettingsProcess* TheImageAcquisitionSettingsProcess;
PCL_END_LOCAL

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionSettingsProcess_h
