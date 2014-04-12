// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#include "ImageAcquisitionSettingsInstance.h"
#include <pcl/Console.h>
#include "CameraData.h"
#include "FilterWheelData.h"
#include <pcl/ErrorHandler.h>
namespace pcl
{
    ImageAcquisitionSettingsInstance::ImageAcquisitionSettingsInstance( const MetaProcess* m ) :
        ProcessImplementation( m ), installedCameras()
    {
        // Not sure if we should do this here or not...
        // installedCameras = LoadCameras();
    }

    void ImageAcquisitionSettingsInstance::LoadCameras()
    {
        try {
            cameraData->mutex.Lock();
            if( cameraData->cam && cameraData->cam->Connected() )
            {
                cameraData->mutex.Unlock();
                throw Error( "Cannot load settings while camera is connected." );
            }
            cameraData->mutex.Unlock();
        }
        ERROR_HANDLER

        installedCameras.Clear();
        ByteArray data;
        if ( Settings::Read( "CameraData", data ) )
        {
            CameraItem camera;
            ByteArray::const_iterator i = data.Begin();
            while ( i < data.End() )
            {
                i = camera.GetFromRawData( i );
                installedCameras.Add( camera );
            }
        }
    }

    void ImageAcquisitionSettingsInstance::SaveCameras()
    {
        ByteArray data;
        for ( camera_list::const_iterator i = installedCameras.Begin(); i != installedCameras.End(); ++i )
        {
            i->AddToRawData( data );
        }

		Settings::Remove( "CameraData" );
        if( data.Length() > 0)
        {
            // Don't know if this is really necessary...
            Settings::Write( "CameraData", data );
        }
    }

    void ImageAcquisitionSettingsInstance::LoadFilterWheels()
    {
        try {
            filterWheelData->mutex.Lock();
            if( filterWheelData->fw && filterWheelData->fw->Connected() )
            {
                filterWheelData->mutex.Unlock();
                throw Error( "Cannot load settings while filterWheel is connected." );
            }
            filterWheelData->mutex.Unlock();
        }
        ERROR_HANDLER
		
        installedFilterWheels.Clear();
        ByteArray data;
        if ( Settings::Read( "FilterWheelData", data ) )
        {
            FilterWheelItem fw;
            ByteArray::const_iterator i = data.Begin();
            while ( i < data.End() )
            {
                i = fw.GetFromRawData( i );
                installedFilterWheels.Add( fw );
            }
        }
    }

    void ImageAcquisitionSettingsInstance::SaveFilterWheels()
    {
        ByteArray data;
        for ( filter_wheel_list::const_iterator i = installedFilterWheels.Begin(); i != installedFilterWheels.End(); ++i )
        {
            i->AddToRawData( data );
        }

		Settings::Remove( "FilterWheelData" );
        if( data.Length() > 0)
        {
            // Don't know if this is really necessary...
            Settings::Write( "FilterWheelData", data );
        }
    }

    ImageAcquisitionSettingsInstance::ImageAcquisitionSettingsInstance( const ImageAcquisitionSettingsInstance& x ) :
        ProcessImplementation( x )
    {
        Assign( x );
    }

    void ImageAcquisitionSettingsInstance::Assign( const ProcessImplementation& p )
    {
        const ImageAcquisitionSettingsInstance* x = dynamic_cast<const ImageAcquisitionSettingsInstance*> ( &p );
        if ( x != 0 )
        {
            installedCameras = x->installedCameras;
			installedFilterWheels = x->installedFilterWheels;
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

    bool ImageAcquisitionSettingsInstance::CanExecuteGlobal( String &whyNot ) const
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

		if ( p == TheIAInstalledFilterWheelEnabledParameter )
			return &installedFilterWheels[tableRow].enabled;
		if ( p == TheIAInstalledFilterWheelDriverPathParameter )
            return installedFilterWheels[tableRow].driverPath.c_str();
		if ( p == TheIAInstalledFilterWheelNameParameter )
            return installedFilterWheels[tableRow].filterWheelName.c_str();

        return 0;
    }

    bool ImageAcquisitionSettingsInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
    {
        if ( p == TheIAInstalledCamerasParameter )
        {
            installedCameras.Clear();
            if ( sizeOrLength > 0 )
                installedCameras.Add( CameraItem(), sizeOrLength );
        }
        else if ( p == TheIAInstalledCameraDriverPathParameter )
        {
            installedCameras[tableRow].driverPath.Clear();
            if ( sizeOrLength > 0 )
                installedCameras[tableRow].driverPath.Reserve( sizeOrLength );
        }
        else if ( p == TheIAInstalledCameraNameParameter )
        {
            installedCameras[tableRow].cameraName.Clear();
            if ( sizeOrLength > 0 )
                installedCameras[tableRow].cameraName.Reserve( sizeOrLength );
        }

		else if ( p == TheIAInstalledFilterWheelsParameter )
        {
            installedFilterWheels.Clear();
            if ( sizeOrLength > 0 )
                installedFilterWheels.Add( FilterWheelItem(), sizeOrLength );
        }
        else if ( p == TheIAInstalledFilterWheelDriverPathParameter )
        {
            installedFilterWheels[tableRow].driverPath.Clear();
            if ( sizeOrLength > 0 )
                installedFilterWheels[tableRow].driverPath.Reserve( sizeOrLength );
        }
        else if ( p == TheIAInstalledFilterWheelNameParameter )
        {
            installedFilterWheels[tableRow].filterWheelName.Clear();
            if ( sizeOrLength > 0 )
                installedFilterWheels[tableRow].filterWheelName.Reserve( sizeOrLength );
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
		
		if ( p == TheIAInstalledFilterWheelsParameter )
            return installedFilterWheels.Length();
        if ( p == TheIAInstalledFilterWheelDriverPathParameter )
            return installedFilterWheels[tableRow].driverPath.Length();
        if ( p == TheIAInstalledFilterWheelNameParameter )
            return installedFilterWheels[tableRow].filterWheelName.Length();
		return 0;
    }

}
