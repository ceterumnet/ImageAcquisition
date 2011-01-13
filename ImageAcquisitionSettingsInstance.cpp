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

  void* ImageAcquisitionSettingsInstance::LockParameter( const MetaParameter*, size_type /*tableRow*/ )
  {
    return 0;
  }


  bool ImageAcquisitionSettingsInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
  {
    if ( p == TheIAInstalledCamerasParameter )
      {
	installedCameras.Clear();
	//we need to do something here...
      }
    else
      return false;

    return true;
  }
  size_type ImageAcquisitionSettingsInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
  {
    if ( p == TheIAInstalledCamerasParameter )
      return 1;
    return 0;
  }


}
