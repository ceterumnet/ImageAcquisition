#ifndef __ImageAcquisitionSettingsInstance_h
#define __ImageAcquisitionSettingsInstance_h

#include <pcl/ProcessImplementation.h>
#include "IPixInsightCamera.h"
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
   struct CameraItem
   {
	   pcl_bool enabled;
	   String driverPath;
	   String cameraName;
	   mutable IPixInsightCamera *cam;
#ifdef __PCL_MACOSX
	   mutable void* libHandle;
#endif
#ifdef __PCL_WINDOWS

	   mutable HINSTANCE libHandle;
#endif

	   CameraItem(  const String& cn = String(), const String& dp = String()) :
	       enabled( false ), driverPath( dp ), cameraName( cn ), cam( 0 ), libHandle( 0 )
	   {
	   }
	   CameraItem( const CameraItem& x ) :
	       enabled( x.enabled ), driverPath( x.driverPath ), cameraName( x.cameraName ), cam( x.cam ), libHandle( x.libHandle )
	   {
	   }
   };
   
private:


	typedef Array<CameraItem> camera_list;
	camera_list installedCameras;

	friend class ImageAcquisitionSettingsInterface;
	friend class CameraSelectorDialog;
	friend class ExposeImageInterface;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionSettingsInstance_h

// ****************************************************************************
// EOF ImageAcquisitionSettingsInstance.h - Released 2010/12/14 09:34:27 UTC
