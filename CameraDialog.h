#ifndef __CameraDialog_h
#define __CameraDialog_h

#include <pcl/Dialog.h>
#include <pcl/Sizer.h>
#include <pcl/GroupBox.h>
#include <pcl/PushButton.h>
#include <pcl/RadioButton.h>
#include <pcl/CheckBox.h>
#include <pcl/Edit.h>

#include <pcl/Console.h>
#include <pcl/Label.h>

namespace pcl
{
	class CameraDialog : public Dialog
	{
	public:	
		CameraDialog();
//		CameraDialog(CameraData* );

	private:
		VerticalSizer     Global_Sizer;
		//GroupBox          CameraSetting_GroupBox;
			VerticalSizer   CameraSetting_Sizer;
				HorizontalSizer CameraName_Sizer;
					Label			CameraName_Label;
					Edit			CameraName_TextBox;
				PushButton		SelectCameraDriver_Button;
			HorizontalSizer   BottomSection_Sizer;
				PushButton      OK_PushButton;
				PushButton      Cancel_PushButton;
	

		void Button_Click( Button& sender, bool checked );
//		void Dialog_Return( Dialog& sender, int retVal );
	};
}

#endif
