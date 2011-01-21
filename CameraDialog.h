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

	private:
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
}

#endif
