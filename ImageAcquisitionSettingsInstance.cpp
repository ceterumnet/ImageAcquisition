#include "ImageAcquisitionSettingsInstance.h"

namespace pcl
{

  ImageAcquisitionSettingsInstance::ImageAcquisitionSettingsInstance( const MetaProcess* m) : 
    ProcessImplementation( m ),
    installedCameras()
  {
  }

  ImageAcquisitionSettingsInstance::ImageAcquisitionSettingsInstance( const ImageAcquisitionSettingsInstance& x ) :
    ProcessImplementation( x )
  {
    Assign( x );
  }

  void ImageAcquisitionSettingsInstance::Assign( const ProcessImplementation& p )
  {
    const ImageAcquisitionSettingsInstance* x = dynamic_cast<const ImageAcquisitionSettingsInstance*>( &p );
    if ( x != 0 )
      {
		  installedCameras = x->installedCameras;
      }
  }

  bool ImageAcquisitionSettingsInstance::IsHistoryUpdater( const View& view ) const
  {
    return false;
  }

  bool ImageAcquisitionSettingsInstance::CanExecuteOn( const View& view, String& whyNot ) const 
  {
    whyNot = "ImageAcquisitionSettings can only be executed in the global context.";
    return false;
  }

  bool ImageAcquisitionSettingsInstance::CanExecuteGlobal(String &whyNot) const
  {
    return true;
  }

  bool ImageAcquisitionSettingsInstance::ExecuteGlobal() 
  {
    return false;
  }

  void* ImageAcquisitionSettingsInstance::LockParameter( const MetaParameter* p, size_type tableRow )
  {
	  if ( p == TheIAInstalledCameraEnabledParameter )
		  return &installedCameras[tableRow].enabled;
	  if ( p == TheIAInstalledCameraDriverPathParameter )
		  return installedCameras[tableRow].driverPath.c_str();
	  if ( p == TheIAInstalledCameraNameParameter )
		  return installedCameras[tableRow].cameraName.c_str();
	  return 0;
  }


  bool ImageAcquisitionSettingsInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
  {
	  if ( p == TheIAInstalledCamerasParameter )
	  {
		  installedCameras.Clear();
		  if( sizeOrLength > 0)
			  installedCameras.Add( CameraItem(), sizeOrLength );
	  }
	  else if ( p == TheIAInstalledCameraDriverPathParameter )
	  {
		  installedCameras[tableRow].driverPath.Clear();
		  if ( sizeOrLength > 0 )
			  installedCameras[tableRow].driverPath.Reserve( sizeOrLength );
	  }
	  else if (p == TheIAInstalledCameraNameParameter )
	  {
		  installedCameras[tableRow].cameraName.Clear();
		  if ( sizeOrLength > 0)
			  installedCameras[tableRow].cameraName.Reserve( sizeOrLength );
	  }
	  else
		  return false;

	  return true;
  }
  size_type ImageAcquisitionSettingsInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
  {
    if ( p == TheIAInstalledCamerasParameter )
		return installedCameras.Length();
	if ( p == TheIAInstalledCameraDriverPathParameter )
		return installedCameras[tableRow].driverPath.Length();
	if ( p == TheIAInstalledCameraNameParameter )
		return installedCameras[tableRow].cameraName.Length();
    return 0;
  }
}
