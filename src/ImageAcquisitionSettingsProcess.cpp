// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#include "ImageAcquisitionSettingsProcess.h"
#include "ImageAcquisitionSettingsParameters.h"
#include "ImageAcquisitionSettingsInstance.h"
#include "ImageAcquisitionSettingsInterface.h"

namespace pcl
{

// ----------------------------------------------------------------------------

ImageAcquisitionSettingsProcess* TheImageAcquisitionSettingsProcess = 0;

// ----------------------------------------------------------------------------

#include "ImageAcquisitionSettingsIcon.xpm"

// ----------------------------------------------------------------------------

ImageAcquisitionSettingsProcess::ImageAcquisitionSettingsProcess() : MetaProcess()
{
   TheImageAcquisitionSettingsProcess = this;

   // Instantiate process parameters
   new IAInstalledCameras( this );
   new IAInstalledCameraEnabled( TheIAInstalledCamerasParameter );
   new IAInstalledCameraDriverPath( TheIAInstalledCamerasParameter );
   new IAInstalledCameraName( TheIAInstalledCamerasParameter );

}

// ----------------------------------------------------------------------------

IsoString ImageAcquisitionSettingsProcess::Id() const
{
   return "ImageAcquisitionSettings";
}

// ----------------------------------------------------------------------------

IsoString ImageAcquisitionSettingsProcess::Category() const
{
   return "ImageAcquisition";
}

// ----------------------------------------------------------------------------

uint32 ImageAcquisitionSettingsProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String ImageAcquisitionSettingsProcess::Description() const
{
   return

   "";
}

// ----------------------------------------------------------------------------

const char** ImageAcquisitionSettingsProcess::IconImageXPM() const
{
   return ImageAcquisitionSettingsIcon_XPM;
}

// ----------------------------------------------------------------------------

ProcessInterface* ImageAcquisitionSettingsProcess::DefaultInterface() const
{
   return TheImageAcquisitionSettingsInterface;
}

// -------------------------------------------------------------------------

ProcessImplementation* ImageAcquisitionSettingsProcess::Create() const
{
   return new ImageAcquisitionSettingsInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* ImageAcquisitionSettingsProcess::Clone( const ProcessImplementation& p ) const
{
   const ImageAcquisitionSettingsInstance* instPtr = dynamic_cast<const ImageAcquisitionSettingsInstance*>( &p );
   return (instPtr != 0) ? new ImageAcquisitionSettingsInstance( *instPtr ) : 0;
}

// ----------------------------------------------------------------------------

} // pcl
