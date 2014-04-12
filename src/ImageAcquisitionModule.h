// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
