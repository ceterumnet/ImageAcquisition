#ifndef __ImageAcquisitionSettingsInstance_h
#define __ImageAcquisitionSettingsInstance_h

#include <pcl/ProcessImplementation.h>

#include "ImageAcquisitionSettingsParameters.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class ImageAcquisitionSettingsInstance : public ProcessImplementation
{
public:

   ImageAcquisitionSettingsInstance( const MetaProcess* );
   ImageAcquisitionSettingsInstance( const ImageAcquisitionSettingsInstance& );

   virtual void Assign( const ProcessImplementation& );

   virtual bool CanExecuteOn( const View&, String& whyNot ) const;
   virtual bool IsHistoryUpdater( const View& v ) const;

   virtual bool CanExecuteGlobal( String& whyNot ) const;
   virtual bool ExecuteGlobal();

   virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/ );
   virtual bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow );
   virtual size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const;

   
private:
	struct CameraItem
	{
		pcl_bool enabled;
		String driverPath;
		String cameraName;
		CameraItem( const String& dp = String(), const String& cn = String() ) : enabled( true ), driverPath( dp ), cameraName( cn )
		{
		}
		CameraItem( const CameraItem& x ) : enabled( x.enabled ), driverPath( x.driverPath ), cameraName( x.cameraName )
		{
		}
	};

	

	typedef Array<CameraItem> camera_list;
	camera_list installedCameras;

	friend class ImageAcquisitionSettingsInterface;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionSettingsInstance_h

// ****************************************************************************
// EOF ImageAcquisitionSettingsInstance.h - Released 2010/12/14 09:34:27 UTC
