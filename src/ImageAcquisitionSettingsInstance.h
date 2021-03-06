// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __ImageAcquisitionSettingsInstance_h
#define __ImageAcquisitionSettingsInstance_h

#include <pcl/ProcessImplementation.h>
#include <pcl/Settings.h>
#include "IPixInsightCamera.h"
#include "ImageAcquisitionSettingsParameters.h"
#include "CameraItem.h"
#include "FilterWheelItem.h"
namespace pcl
{

    // ----------------------------------------------------------------------------


    class ImageAcquisitionSettingsInstance: public ProcessImplementation
    {
    public:
        typedef Array<CameraItem> camera_list;
        typedef Array<FilterWheelItem> filter_wheel_list;

        ImageAcquisitionSettingsInstance( const MetaProcess* );
        ImageAcquisitionSettingsInstance( const ImageAcquisitionSettingsInstance& );

        virtual void Assign( const ProcessImplementation& );

        virtual bool CanExecuteOn( const View&, String& whyNot ) const;
        virtual bool IsHistoryUpdater( const View& v ) const;

        virtual bool CanExecuteGlobal( String& whyNot ) const;
        virtual bool ExecuteGlobal();

        virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/);
        virtual bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow );
        virtual size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const;

        void SaveCameras();
        void LoadCameras();

        void LoadFilterWheels();
        void SaveFilterWheels();

    private:
        camera_list installedCameras;
        filter_wheel_list installedFilterWheels;

        friend class ImageAcquisitionSettingsInterface;
        friend class CameraSelectorDialog;
        friend class ExposeImageInterface;
    };

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionSettingsInstance_h
// ****************************************************************************
// EOF ImageAcquisitionSettingsInstance.h - Released 2010/12/14 09:34:27 UTC
