#include "CameraDialog.h"

namespace pcl
{

    CameraDialog::CameraDialog() :
        Dialog()
    {
        pcl::Font fnt = Font();
        String cameraDriverStr( "Camera Driver:" );
        int labelWidth = fnt.Width( cameraDriverStr + 'M' );
        int editWidth = fnt.Width( String( "/usr/local/lib/some/fairly/long/path/that/might/be/seen.so" + 'T' ) );
        CameraName_Label.SetText( "Camera Name:" );
        CameraName_Label.SetToolTip( "The camera name must be unique, but you can name it something like \"QHY11S - ASCOM\"" );
        CameraName_Label.SetTextAlignment( TextAlign::Right | TextAlign::VertCenter );
        CameraName_Label.SetFixedWidth( labelWidth );

        //CameraDriver_ToolButton.SetText(cameraDriverStr);
        CameraDriver_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" ) ) );
        CameraDriver_ToolButton.SetCursor( StdCursor::Arrow );
        CameraDriver_ToolButton.OnClick( (pcl::Button::click_event_handler) &CameraDialog::Button_Click, *this );

        CameraName_Sizer.Add( CameraName_Label );
        CameraName_Sizer.Add( CameraName_Edit );
        CameraName_Sizer.SetSpacing( 4 );

        CameraDriver_Label.SetText( cameraDriverStr );
        CameraDriver_Label.SetTextAlignment( TextAlign::Right | TextAlign::VertCenter );
        CameraDriver_Label.SetFixedWidth( labelWidth );
        CameraDriver_Edit.SetFixedWidth( editWidth );
        CameraDriver_ToolButton.OnClick( (pcl::Button::click_event_handler) &CameraDialog::Button_Click, *this );
        CameraDriver_Sizer.Add( CameraDriver_Label );
        CameraDriver_Sizer.Add( CameraDriver_Edit );
        CameraDriver_Sizer.Add( CameraDriver_ToolButton );
        CameraDriver_Sizer.SetSpacing( 4 );

        CameraSetting_Sizer.Add( CameraName_Sizer );
        CameraSetting_Sizer.Add( CameraDriver_Sizer );
        CameraSetting_Sizer.SetSpacing( 4 );

        OK_PushButton.SetText( "OK" );
        OK_PushButton.SetDefault();
        OK_PushButton.SetCursor( StdCursor::Checkmark );
        OK_PushButton.OnClick( (pcl::Button::click_event_handler) &CameraDialog::Button_Click, *this );
        Cancel_PushButton.SetText( "Cancel" );
        Cancel_PushButton.SetCursor( StdCursor::Crossmark );
        Cancel_PushButton.OnClick( (pcl::Button::click_event_handler) &CameraDialog::Button_Click, *this );

        BottomSection_Sizer.Add( OK_PushButton );
        BottomSection_Sizer.Add( Cancel_PushButton );
        BottomSection_Sizer.SetSpacing( 4 );

        Global_Sizer.Add( CameraSetting_Sizer );
        Global_Sizer.Add( BottomSection_Sizer );

        SetSizer( Global_Sizer );
        AdjustToContents();

        SetFixedSize();

        OnReturn( (pcl::Dialog::return_event_handler) &CameraDialog::Dialog_Return, *this );
    }

    void CameraDialog::Button_Click( Button& sender, bool /*checked*/)
    {
        if ( sender == OK_PushButton )
		{
			CameraName = CameraName_Edit.Text();
			DriverFile = CameraDriver_Edit.Text();
            Ok();
		}
        else if ( sender == Cancel_PushButton )
            Cancel();
        else if ( sender == CameraDriver_ToolButton )
        {
            OpenFileDialog ofDlg;
            ofDlg.SetInitialPath( PixInsightSettings::GlobalString( "Application/CoreDirectory" ) );
            ofDlg.SetSelectedFileExtension( ".dll" );
            ofDlg.Execute();
            CameraDriver_Edit.SetText( ofDlg.FileName() );
        }
    }

    void CameraDialog::Dialog_Return( pcl::Dialog &sender, int retVal )
    {
        Console().WriteLn( "Dialog Returned\n" );
        Console().WriteLn( String( "Selected Driver: " + CameraDriver_Edit.Text() ) );
    }

	String CameraDialog::GetCameraName()
	{
		return CameraName;
	}

	String CameraDialog::GetDriverFile()
	{
		return DriverFile;
	}

}
