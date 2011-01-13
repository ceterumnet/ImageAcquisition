
#ifndef __ExposeImageProcess_h
#define __ExposeImageProcess_h

#include <pcl/MetaProcess.h>

namespace pcl
{

// ----------------------------------------------------------------------------

class ExposeImageProcess : public MetaProcess
{
public:

   ExposeImageProcess();

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
extern ExposeImageProcess* TheExposeImageProcess;
PCL_END_LOCAL

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ExposeImageProcess_h
