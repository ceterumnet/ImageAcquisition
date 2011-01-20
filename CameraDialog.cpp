#include "CameraDialog.h"

namespace pcl
{

  CameraDialog::CameraDialog( ) :
    Dialog()
  {
    pcl::Font fnt = Font();
	String cameraDriverStr( "Select your camera driver" );
    int labelWidth = fnt.Width( cameraDriverStr + 'M' );
	
	CameraName_Label.SetText("Camera Name");
	CameraName_Label.SetToolTip("The camera name must be unique, but you can name it something like \"QHY11S - ASCOM\"");

	SelectCameraDriver_Button.SetText(cameraDriverStr);
	SelectCameraDriver_Button.SetDefault();
	SelectCameraDriver_Button.SetCursor(StdCursor::Arrow);
	SelectCameraDriver_Button.OnClick( (pcl::Button::click_event_handler)&CameraDialog::Button_Click, *this );

	CameraName_Sizer.Add(CameraName_Label);
	CameraName_Sizer.Add(CameraName_TextBox);
	CameraSetting_Sizer.Add(CameraName_Sizer);
    CameraSetting_Sizer.Add(SelectCameraDriver_Button);
	
    //CameraSetting_GroupBox.SetSizer(CameraSetting_Sizer);
    
	OK_PushButton.SetText( "OK" );
    OK_PushButton.SetDefault();
    OK_PushButton.SetCursor( StdCursor::Checkmark );
    OK_PushButton.OnClick( (pcl::Button::click_event_handler)&CameraDialog::Button_Click, *this );

    Cancel_PushButton.SetText("Cancel");
    Cancel_PushButton.SetDefault();
    Cancel_PushButton.SetCursor( StdCursor::Crossmark );
    Cancel_PushButton.OnClick( (pcl::Button::click_event_handler)&CameraDialog::Button_Click, *this );
	
	BottomSection_Sizer.Add(OK_PushButton);
	BottomSection_Sizer.Add(Cancel_PushButton);
	
	Global_Sizer.Add(CameraSetting_Sizer);
	Global_Sizer.Add(BottomSection_Sizer);

    SetSizer( Global_Sizer );
    AdjustToContents();
	
    SetFixedSize();

    //	OnReturn( (pcl::Dialog::return_event_handler)&CameraDialog::Dialog_Return, *this );
  }

  void CameraDialog::Button_Click( Button& sender, bool /*checked*/ )
  {
    if ( sender == OK_PushButton )
      Ok();
    else if ( sender == Cancel_PushButton )
      Cancel();
  }
  //
  //void CameraDialog::Dialog_Return(pcl::Dialog &sender, int retVal)
  //{
  //	Console().WriteLn("Dialog Returned\n");
  //}


}
