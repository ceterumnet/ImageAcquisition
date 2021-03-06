// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.



#ifndef __ImageAcquisitionSettingsParameters_h
#define __ImageAcquisitionSettingsParameters_h

#include <pcl/MetaParameter.h>

namespace pcl
{

	PCL_BEGIN_LOCAL

		// ----------------------------------------------------------------------------

	class IAInstalledCameras: public MetaTable
	{
	public:
		IAInstalledCameras ( MetaProcess* );
		virtual IsoString Id() const;
	};
	extern IAInstalledCameras* TheIAInstalledCamerasParameter ;

	class IAInstalledCameraEnabled: public MetaBoolean
	{
	public:
		IAInstalledCameraEnabled ( MetaTable* );
		virtual IsoString Id() const;
	};
	extern IAInstalledCameraEnabled* TheIAInstalledCameraEnabledParameter ;

	class IAInstalledCameraDriverPath: public MetaString
	{
	public:
		IAInstalledCameraDriverPath ( MetaTable* );
		virtual IsoString Id() const;
	};
	extern IAInstalledCameraDriverPath* TheIAInstalledCameraDriverPathParameter ;

	class IAInstalledCameraName: public MetaString
	{
	public:
		IAInstalledCameraName ( MetaTable* );
		virtual IsoString Id() const;
	};
	extern IAInstalledCameraName* TheIAInstalledCameraNameParameter ;


	class IAInstalledFilterWheels: public MetaTable
    {
    public:
        IAInstalledFilterWheels( MetaProcess* );
        virtual IsoString Id() const;
    };
    extern IAInstalledFilterWheels* TheIAInstalledFilterWheelsParameter;

    class IAInstalledFilterWheelEnabled: public MetaBoolean
    {
    public:
        IAInstalledFilterWheelEnabled( MetaTable* );
        virtual IsoString Id() const;
    };
    extern IAInstalledFilterWheelEnabled* TheIAInstalledFilterWheelEnabledParameter;

    class IAInstalledFilterWheelDriverPath: public MetaString
    {
    public:
        IAInstalledFilterWheelDriverPath( MetaTable* );
        virtual IsoString Id() const;
    };
    extern IAInstalledFilterWheelDriverPath* TheIAInstalledFilterWheelDriverPathParameter;

    class IAInstalledFilterWheelName: public MetaString
    {
    public:
        IAInstalledFilterWheelName( MetaTable* );
        virtual IsoString Id() const;
    };
    extern IAInstalledFilterWheelName* TheIAInstalledFilterWheelNameParameter;

	// ----------------------------------------------------------------------------

	PCL_END_LOCAL

} // pcl

#endif   // __ImageAcquisitionSettingsParameters_h
