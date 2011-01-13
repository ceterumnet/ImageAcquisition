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
   return "ImageAcquisition,Preprocessing";
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
