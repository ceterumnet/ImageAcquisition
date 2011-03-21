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

    IAInstalledFilterWheels* TheIAInstalledFilterWheelsParameter = 0;
    IAInstalledFilterWheelEnabled* TheIAInstalledFilterWheelEnabledParameter = 0;
    IAInstalledFilterWheelDriverPath* TheIAInstalledFilterWheelDriverPathParameter = 0;
    IAInstalledFilterWheelName* TheIAInstalledFilterWheelNameParameter = 0;


    IAInstalledFilterWheels::IAInstalledFilterWheels( MetaProcess* P) : MetaTable( P )
    {
        TheIAInstalledFilterWheelsParameter = this;
    }

    IsoString IAInstalledFilterWheels::Id() const
    {
        return "installedFilterWheels";
    }

    IAInstalledFilterWheelEnabled::IAInstalledFilterWheelEnabled( MetaTable* T) : MetaBoolean( T )
    {
        TheIAInstalledFilterWheelEnabledParameter = this;
    }

    IsoString IAInstalledFilterWheelEnabled::Id() const
    {
        return "installedFilterWheelEnabled";
    }

    IAInstalledFilterWheelDriverPath::IAInstalledFilterWheelDriverPath( MetaTable* T) : MetaString( T )
    {
        TheIAInstalledFilterWheelDriverPathParameter = this;
    }

    IsoString IAInstalledFilterWheelDriverPath::Id() const
    {
        return "installedFilterWheelDriverPath";
    }

    IAInstalledFilterWheelName::IAInstalledFilterWheelName( MetaTable* T) : MetaString( T )
    {
        TheIAInstalledFilterWheelNameParameter = this;
    }

    IsoString IAInstalledFilterWheelName::Id() const
    {
        return "installedFilterWheelName";
    }

}
