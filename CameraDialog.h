// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __CameraDialog_h
#define __CameraDialog_h

#include <pcl/Dialog.h>
#include <pcl/Sizer.h>
#include <pcl/GroupBox.h>
#include <pcl/PushButton.h>
#include <pcl/RadioButton.h>
#include <pcl/CheckBox.h>
#include <pcl/Edit.h>
#include <pcl/ToolButton.h>
#include <pcl/Console.h>
#include <pcl/Label.h>
#include <pcl/FileDialog.h>
#include <pcl/GlobalSettings.h>

namespace pcl
{
	class CameraDialog : public Dialog
	{
	public:
		CameraDialog();

		String GetCameraName();
		String GetDriverFile();

	private:
		String DriverFile;
		String CameraName;

		VerticalSizer     Global_Sizer;
			VerticalSizer   CameraSetting_Sizer;
				HorizontalSizer CameraName_Sizer;
					Label			CameraName_Label;
					Edit			CameraName_Edit;
				HorizontalSizer CameraDriver_Sizer;
					Label			CameraDriver_Label;
					Edit			CameraDriver_Edit;
					ToolButton	    CameraDriver_ToolButton;
				HorizontalSizer   BottomSection_Sizer;
					PushButton      OK_PushButton;
					PushButton      Cancel_PushButton;
	

		void Button_Click( Button& sender, bool checked );
		void Dialog_Return( Dialog& sender, int retVal );
	};

	class DeviceDriverDialog : public Dialog
	{
	public:
		DeviceDriverDialog();

		String GetDeviceName();
		String GetDriverFile();

	private:
		String DriverFile;
		String DeviceName;

		VerticalSizer     Global_Sizer;
			VerticalSizer   DeviceDriverSetting_Sizer;
				HorizontalSizer DeviceDriverName_Sizer;
					Label			DeviceDriverName_Label;
					Edit			DeviceDriverName_Edit;
				HorizontalSizer DeviceDriverDriver_Sizer;
					Label			DeviceDriverDriver_Label;
					Edit			DeviceDriverDriver_Edit;
					ToolButton	    DeviceDriverDriver_ToolButton;
				HorizontalSizer   BottomSection_Sizer;
					PushButton      OK_PushButton;
					PushButton      Cancel_PushButton;
	

		void Button_Click( Button& sender, bool checked );
		void Dialog_Return( Dialog& sender, int retVal );
	};

}

#endif
