// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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