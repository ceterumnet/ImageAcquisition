#ifndef __ImageAcquisitionSessionProcess_h
#define __ImageAcquisitionSessionProcess_h

#include <pcl/MetaProcess.h>

namespace pcl
{
	class ImageAcquisitionSessionProcess : public MetaProcess
	{
	public:

		ImageAcquisitionSessionProcess();

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
		extern ImageAcquisitionSessionProcess* TheImageAcquisitionSessionProcess;
	PCL_END_LOCAL

}

#endif