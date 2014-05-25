// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions;
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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


    DeviceDriverDialog::DeviceDriverDialog() :
        Dialog()
    {
        pcl::Font fnt = Font();
        String DeviceDriverDriverStr( "Driver:" );
        int labelWidth = fnt.Width( DeviceDriverDriverStr + 'M' );
        int editWidth = fnt.Width( String( "/usr/local/lib/some/fairly/long/path/that/might/be/seen.so" + 'T' ) );
        DeviceDriverName_Label.SetText( "Name:" );
        DeviceDriverName_Label.SetToolTip( "The name must be unique, but you can name it something like \"QHY11S - ASCOM\" or My QHY Filter Wheel" );
        DeviceDriverName_Label.SetTextAlignment( TextAlign::Right | TextAlign::VertCenter );
        DeviceDriverName_Label.SetFixedWidth( labelWidth );

        //DeviceDriverDriver_ToolButton.SetText(DeviceDriverDriverStr);
        DeviceDriverDriver_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" ) ) );
        DeviceDriverDriver_ToolButton.SetCursor( StdCursor::Arrow );
        DeviceDriverDriver_ToolButton.OnClick( (pcl::Button::click_event_handler) &DeviceDriverDialog::Button_Click, *this );

        DeviceDriverName_Sizer.Add( DeviceDriverName_Label );
        DeviceDriverName_Sizer.Add( DeviceDriverName_Edit );
        DeviceDriverName_Sizer.SetSpacing( 4 );

        DeviceDriverDriver_Label.SetText( DeviceDriverDriverStr );
        DeviceDriverDriver_Label.SetTextAlignment( TextAlign::Right | TextAlign::VertCenter );
        DeviceDriverDriver_Label.SetFixedWidth( labelWidth );
        DeviceDriverDriver_Edit.SetFixedWidth( editWidth );
        DeviceDriverDriver_ToolButton.OnClick( (pcl::Button::click_event_handler) &DeviceDriverDialog::Button_Click, *this );
        DeviceDriverDriver_Sizer.Add( DeviceDriverDriver_Label );
        DeviceDriverDriver_Sizer.Add( DeviceDriverDriver_Edit );
        DeviceDriverDriver_Sizer.Add( DeviceDriverDriver_ToolButton );
        DeviceDriverDriver_Sizer.SetSpacing( 4 );

        DeviceDriverSetting_Sizer.Add( DeviceDriverName_Sizer );
        DeviceDriverSetting_Sizer.Add( DeviceDriverDriver_Sizer );
        DeviceDriverSetting_Sizer.SetSpacing( 4 );

        OK_PushButton.SetText( "OK" );
        OK_PushButton.SetDefault();
        OK_PushButton.SetCursor( StdCursor::Checkmark );
        OK_PushButton.OnClick( (pcl::Button::click_event_handler) &DeviceDriverDialog::Button_Click, *this );
        Cancel_PushButton.SetText( "Cancel" );
        Cancel_PushButton.SetCursor( StdCursor::Crossmark );
        Cancel_PushButton.OnClick( (pcl::Button::click_event_handler) &DeviceDriverDialog::Button_Click, *this );

        BottomSection_Sizer.Add( OK_PushButton );
        BottomSection_Sizer.Add( Cancel_PushButton );
        BottomSection_Sizer.SetSpacing( 4 );

        Global_Sizer.Add( DeviceDriverSetting_Sizer );
        Global_Sizer.Add( BottomSection_Sizer );

        SetSizer( Global_Sizer );
        AdjustToContents();

        SetFixedSize();

        OnReturn( (pcl::Dialog::return_event_handler) &DeviceDriverDialog::Dialog_Return, *this );
    }

    void DeviceDriverDialog::Button_Click( Button& sender, bool /*checked*/)
    {
        if ( sender == OK_PushButton )
        {
            DeviceName = DeviceDriverName_Edit.Text();
            DriverFile = DeviceDriverDriver_Edit.Text();
            Ok();
        }
        else if ( sender == Cancel_PushButton )
            Cancel();
        else if ( sender == DeviceDriverDriver_ToolButton )
        {
            OpenFileDialog ofDlg;
            ofDlg.SetInitialPath( PixInsightSettings::GlobalString( "Application/CoreDirectory" ) );
            ofDlg.SetSelectedFileExtension( ".dll" );
            ofDlg.Execute();
            DeviceDriverDriver_Edit.SetText( ofDlg.FileName() );
        }
    }

    void DeviceDriverDialog::Dialog_Return( pcl::Dialog &sender, int retVal )
    {
        Console().WriteLn( "Dialog Returned\n" );
        Console().WriteLn( String( "Selected Driver: " + DeviceDriverDriver_Edit.Text() ) );
    }

    String DeviceDriverDialog::GetDeviceName()
    {
        return DeviceName;
    }

    String DeviceDriverDialog::GetDriverFile()
    {
        return DriverFile;
    }

}
