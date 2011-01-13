#include "ImageAcquisitionSettingsParameters.h"


namespace pcl
{
	IAInstalledCameras* TheIAInstalledCamerasParameter = 0;
	IAInstalledCameraEnabled* TheIAInstalledCameraEnabledParameter = 0;
	IAInstalledCameraDriverPath* TheIAInstalledCameraDriverPathParameter = 0;
	IAInstalledCameraName* TheIAInstalledCameraNameParameter = 0;


	IAInstalledCameras::IAInstalledCameras( MetaProcess* P) : MetaTable( P )
	{
		TheIAInstalledCamerasParameter = this;
	}

	IsoString IAInstalledCameras::Id() const
	{
		return "installedCameras";
	}

	IAInstalledCameraEnabled::IAInstalledCameraEnabled( MetaTable* T) : MetaBoolean( T )
	{
		TheIAInstalledCameraEnabledParameter = this;
	}

	IsoString IAInstalledCameraEnabled::Id() const
	{
		return "installedCameraEnabled";
	}



	IAInstalledCameraDriverPath::IAInstalledCameraDriverPath( MetaTable* T) : MetaString( T )
	{
		TheIAInstalledCameraDriverPathParameter = this;
	}

	IsoString IAInstalledCameraDriverPath::Id() const
	{
		return "installedCameraDriverPath";
	}

	IAInstalledCameraName::IAInstalledCameraName( MetaTable* T) : MetaString( T )
	{
		TheIAInstalledCameraNameParameter = this;
	}

	IsoString IAInstalledCameraName::Id() const
	{
		return "installedCameraName";
	}

}