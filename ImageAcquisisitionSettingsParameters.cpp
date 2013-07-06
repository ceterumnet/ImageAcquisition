// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
