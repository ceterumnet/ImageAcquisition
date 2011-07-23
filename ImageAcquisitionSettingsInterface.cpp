// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#include "ImageAcquisitionSettingsInterface.h"
#include "ImageAcquisitionSettingsProcess.h"
#include "ExposeImageInterface.h"

#include <pcl/Sizer.h>
#include <pcl/Label.h>
#include <pcl/ComboBox.h>
#include <pcl/CheckBox.h>
#include <pcl/Edit.h>
#include <pcl/RadioButton.h>
#include <pcl/PushButton.h>
#include <pcl/Dialog.h>
#include <pcl/FileDialog.h>
#include <pcl/ColorDialog.h>
#include <pcl/Graphics.h>
#include <pcl/GlobalSettings.h>
#include <pcl/ErrorHandler.h>
#include <pcl/Console.h>
#include <pcl/Settings.h>
#include "CameraData.h"
#include "FilterWheelData.h"

#ifdef __PCL_MACOSX
#include <dlfcn.h>
#endif

#define CAMERALIST_MINHEIGHT( fnt )  (8*fnt.Height() + 2)

namespace pcl
{

    ImageAcquisitionSettingsInterface* TheImageAcquisitionSettingsInterface = 0;

#include "ImageAcquisitionSettingsIcon.xpm"

    ImageAcquisitionSettingsInterface::ImageAcquisitionSettingsInterface() :
        ProcessInterface(), instance( TheImageAcquisitionSettingsProcess ), GUI( 0 )
    {
        TheImageAcquisitionSettingsInterface = this;
    }

    ImageAcquisitionSettingsInterface::~ImageAcquisitionSettingsInterface()
    {
        if ( GUI != 0 )
            delete GUI, GUI = 0;
    }

    IsoString ImageAcquisitionSettingsInterface::Id() const
    {
        return "ImageAcquisitionSettings";
    }

    MetaProcess* ImageAcquisitionSettingsInterface::Process() const /***** new member function *****/
    {
        return TheImageAcquisitionSettingsProcess;
    }

    uint32 ImageAcquisitionSettingsInterface::Version() const
    {
        return 0x100;
    }

    const char** ImageAcquisitionSettingsInterface::IconImageXPM() const
    {
        return ImageAcquisitionSettingsIcon_XPM;
    }

    InterfaceFeatures ImageAcquisitionSettingsInterface::Features() const
    {
        return InterfaceFeature::DefaultGlobal;
    }

    void ImageAcquisitionSettingsInterface::ApplyInstance() const
    {
        instance.LaunchGlobal();
    }


    void ImageAcquisitionSettingsInterface::UpdateControls()
    {
        UpdateCameraList();
		UpdateFWList();
    }

    void ImageAcquisitionSettingsInterface::ResetInstance()
    {
        ImageAcquisitionSettingsInstance defaultInstance( TheImageAcquisitionSettingsProcess );
        ImportProcess( defaultInstance );
    }

    bool ImageAcquisitionSettingsInterface::Launch( const MetaProcess& P, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/)
    {
        // ### Deferred initialization
        if ( GUI == 0 )
        {
            GUI = new GUIData( *this );
            SetWindowTitle( "Image Acquisition Settings" );
            //LoadUserSettings();
            UpdateControls();
        }

        if( cameraData == 0 )
            cameraData = new CameraData;
		if( filterWheelData == 0 )
			filterWheelData = new FilterWheelData;
        dynamic = false;
        return &P == TheImageAcquisitionSettingsProcess;
    }

    ProcessImplementation* ImageAcquisitionSettingsInterface::NewProcess() const
    {
        return new ImageAcquisitionSettingsInstance( instance );
    }

    bool ImageAcquisitionSettingsInterface::ValidateProcess( const ProcessImplementation& p, pcl::String& whyNot ) const
    {
        const ImageAcquisitionSettingsInstance* r = dynamic_cast<const ImageAcquisitionSettingsInstance*> ( &p );
        if ( r == 0 )
        {
            whyNot = "Not an ImageAcquisitionSettings instance.";
            return false;
        }

        whyNot.Clear();
        return true;
    }

    bool ImageAcquisitionSettingsInterface::RequiresInstanceValidation() const
    {
        return true;
    }

    bool ImageAcquisitionSettingsInterface::ImportProcess( const ProcessImplementation& p )
    {
        instance.Assign( p );
        UpdateControls();
        return true;
    }

    static size_type TreeInsertionIndex( const TreeBox& tree )
    {
        const TreeBox::Node* n = tree.CurrentNode();
        return (n != 0) ? tree.ChildIndex( n ) + 1 : tree.NumberOfChildren();
    }

    void theLogger( String text )
    {
        Console().Write( text );
    }

    void ImageAcquisitionSettingsInterface::__LoadSaveSettingsButtons_Click( Button& sender, bool checked )
    {
        if( sender == GUI->LoadSettings_PushButton )
        {
            instance.LoadCameras();
            instance.LoadFilterWheels();
            UpdateControls();
        }
        else if ( sender == GUI->SaveSettings_PushButton )
        {
            instance.SaveCameras( );
            instance.SaveFilterWheels( );
        }
    }

    /*
     *   CAMERA STUFF START
     */
    void ImageAcquisitionSettingsInterface::AddCamera()
    {
        // Not sure if this should be a new instance...or just reuse...I think reuse is better.
        //CameraDialog dlg = new CameraDialog;
        if ( GUI->CamDlg.Execute() )
        {
            size_type i0 = TreeInsertionIndex( GUI->CameraList_TreeBox );
            for ( size_type i = 0, n = instance.installedCameras.Length(); i < n; ++i )
            {
                String theCameraName = GUI->CamDlg.GetCameraName();
                if ( theCameraName.Compare( instance.installedCameras[i].cameraName ) == 0 )
                    throw Error( "Please use a unique camera name for each camera." );
            }
            instance.installedCameras.Insert( instance.installedCameras.At( i0++ ), CameraItem( GUI->CamDlg.GetCameraName(),
                    GUI->CamDlg.GetDriverFile() ) );
        }
    }

	
	void ImageAcquisitionSettingsInterface::UpdateCameraItem( size_type i )
    {
        TreeBox::Node* node = GUI->CameraList_TreeBox[i];
        if ( node == 0 )
            return;
        const CameraItem& item = instance.installedCameras[i];
        //TODO:  This is not the correct icon.  We need an icon that indicates that our camera is either primary or not.
        node->SetIcon( 0, Bitmap( String( item.enabled ? ":/images/icons/enabled.png" : ":/images/icons/disabled.png" ) ) );
        node->SetAlignment( 0, TextAlign::Left );
        node->SetText( 1, item.cameraName );
        node->SetAlignment( 1, TextAlign::Right );
        node->SetIcon( 2, Bitmap( String( ":/images/icons/file.png" ) ) );
        String fileName = File::ExtractName( item.driverPath ) + File::ExtractExtension( item.driverPath );
        node->SetText( 2, fileName );
        node->SetToolTip( 2, item.driverPath );
        node->SetAlignment( 2, TextAlign::Left );
    }

    void ImageAcquisitionSettingsInterface::UpdateCameraList()
    {
        int currentIdx = GUI->CameraList_TreeBox.ChildIndex( GUI->CameraList_TreeBox.CurrentNode() );

        GUI->CameraList_TreeBox.DisableUpdates();
        GUI->CameraList_TreeBox.Clear();

        for ( size_type i = 0; i < instance.installedCameras.Length(); ++i )
        {
            new TreeBox::Node( GUI->CameraList_TreeBox );
            UpdateCameraItem( i );
        }

        GUI->CameraList_TreeBox.AdjustColumnWidthToContents( 0 );
        GUI->CameraList_TreeBox.AdjustColumnWidthToContents( 1 );
        GUI->CameraList_TreeBox.AdjustColumnWidthToContents( 2 );

        if ( !instance.installedCameras.IsEmpty() )
            if ( currentIdx >= 0 && currentIdx < GUI->CameraList_TreeBox.NumberOfChildren() )
                GUI->CameraList_TreeBox.SetCurrentNode( GUI->CameraList_TreeBox[currentIdx] );

        GUI->CameraList_TreeBox.EnableUpdates();
    }

    CameraItem *ImageAcquisitionSettingsInterface::GetPrimaryImager()
    {
        for ( size_type i = 0; i < instance.installedCameras.Length(); ++i )
            if ( instance.installedCameras[i].enabled )
                return &instance.installedCameras[i];
        return NULL;
    }

    void ImageAcquisitionSettingsInterface::__CameraListButtons_Click( Button& sender, bool checked )
    {
        Console console;
        if ( sender == GUI->AddCamera_PushButton )
        {
            try
            {
                AddCamera();
                UpdateCameraList();
            }
            ERROR_HANDLER
        }
        //TODO:  decide how to handle edit if camera is not active etc...
        //  I think we need to invoke the configuration dialog of the driver here.
        // I'm not sure we need to have edit functionality here...it is pretty easy to add/delete...
        else if ( sender == GUI->EditCamera_PushButton )
        {
            //int currentIdx = GUI->CameraList_TreeBox.ChildIndex( GUI->CameraList_TreeBox.CurrentNode() );
            //instance.installedCameras[currentIdx]
        }
        else if ( sender == GUI->DeleteCamera_PushButton )
        {
            try
            {
                int currentIdx = GUI->CameraList_TreeBox.ChildIndex( GUI->CameraList_TreeBox.CurrentNode() );
                if( instance.installedCameras[currentIdx].GetDevice() && instance.installedCameras[currentIdx].GetDevice()->Connected() )
                    throw Error( "Can't delete an imager while it is connected.");
                ImageAcquisitionSettingsInstance::camera_list newCameraList;
                for ( int i = 0, n = GUI->CameraList_TreeBox.NumberOfChildren(); i < n; ++i )
                    if ( !GUI->CameraList_TreeBox[i]->IsSelected() )
                        newCameraList.Add( instance.installedCameras[i] );
                instance.installedCameras = newCameraList;
                UpdateCameraList();
            }

            ERROR_HANDLER
        }
        else if ( sender == GUI->MakePrimary_PushButton )
        {
            try {
                int currentIdx = GUI->CameraList_TreeBox.ChildIndex( GUI->CameraList_TreeBox.CurrentNode() );
                for ( int i = 0, n = GUI->CameraList_TreeBox.NumberOfChildren(); i < n; ++i )
                    if ( GUI->CameraList_TreeBox[i]->IsEnabled() )
                        if ( cameraData->cam && cameraData->cam->Connected() )
                            throw Error( "Cannot change primary imager while camera is connected." );
                        else
                            instance.installedCameras[i].enabled = false;
                CameraItem *theItem = &instance.installedCameras[currentIdx];
                theItem->enabled = true;
                if( theItem->GetDevice() == NULL)
                    theItem->InitializeDevice();
                cameraData->mutex.Lock();
                if( theItem->GetDevice() == NULL)
                    throw Error("Device not properly initialized...");
                IPixInsightCamera *c = instance.installedCameras[currentIdx].GetDevice();
                cameraData->cam = c;
                cameraData->mutex.Unlock();
                UpdateCameraList();

                //TODO:  Deal with a non active window...
                if ( TheExposeImageInterface && TheExposeImageInterface->IsVisible() )
                    TheExposeImageInterface->UpdateCameraControls();
                else
                {
                    //this is broken...need to rework this anyways...it is crappy.
    //                TheExposeImageInterface->UpdateCameraControls();
                }
            }
            ERROR_HANDLER
        }
        else
        {
            //TODO:  maybe just throw an exception here...
        }
    }

    //TODO:  Prune this handler if we have no use for it...
    void ImageAcquisitionSettingsInterface::__CameraList_CurrentNodeUpdated( TreeBox& sender, TreeBox::Node& current, TreeBox::Node& oldCurrent )
    {

    }

    //TODO:  Prune this handler if we have no use for it...
    void ImageAcquisitionSettingsInterface::__CameraList_NodeActivated( TreeBox& sender, TreeBox::Node& node, int col )
    {

    }

    void ImageAcquisitionSettingsInterface::__CameraList_NodeSelectionUpdated( TreeBox& sender )
    {
        bool isOne = sender.SelectedNodes().Length() == 1;
        GUI->MakeGuider_PushButton.Enable( isOne );
        GUI->MakePrimary_PushButton.Enable( isOne );
        GUI->EditCamera_PushButton.Enable( isOne );
        bool isOneOrMore = sender.SelectedNodes().Length() > 0;
        GUI->DeleteCamera_PushButton.Enable( isOneOrMore );
    }

    /*
     *   CAMERA STUFF END
     */

    /*
     *   FW STUFF START
     */

	void ImageAcquisitionSettingsInterface::AddFW()
    {
        // Not sure if this should be a new instance...or just reuse...I think reuse is better.
        if ( GUI->DevDrvDlg.Execute() )
        {
            size_type i0 = TreeInsertionIndex( GUI->FWList_TreeBox );
			for ( size_type i = 0, n = instance.installedFilterWheels.Length(); i < n; ++i )
            {
                String theFWName = GUI->DevDrvDlg.GetDeviceName();
                if ( theFWName.Compare( instance.installedFilterWheels[i].filterWheelName ) == 0 )
                    throw Error( "Please use a unique filter wheel name for each filter wheel." );
            }
			instance.installedFilterWheels.Insert( instance.installedFilterWheels.At( i0++ ), FilterWheelItem( GUI->DevDrvDlg.GetDeviceName(),
                    GUI->DevDrvDlg.GetDriverFile() ) );
        }
    }

	void ImageAcquisitionSettingsInterface::UpdateFWList()
	{
	    int currentIdx = GUI->FWList_TreeBox.ChildIndex( GUI->FWList_TreeBox.CurrentNode() );

        GUI->FWList_TreeBox.DisableUpdates();
        GUI->FWList_TreeBox.Clear();

        for ( size_type i = 0; i < instance.installedFilterWheels.Length(); ++i )
        {
			new TreeBox::Node( GUI->FWList_TreeBox );
			UpdateFWItem( i );
        }

        GUI->FWList_TreeBox.AdjustColumnWidthToContents( 0 );
        GUI->FWList_TreeBox.AdjustColumnWidthToContents( 1 );
        GUI->FWList_TreeBox.AdjustColumnWidthToContents( 2 );

        if ( !instance.installedFilterWheels.IsEmpty() )
            if ( currentIdx >= 0 && currentIdx < GUI->FWList_TreeBox.NumberOfChildren() )
                GUI->FWList_TreeBox.SetCurrentNode( GUI->FWList_TreeBox[currentIdx] );

        GUI->FWList_TreeBox.EnableUpdates();
	}

	void ImageAcquisitionSettingsInterface::UpdateFWItem( pcl::size_type i )
	{
        TreeBox::Node* node = GUI->FWList_TreeBox[i];
        if ( node == 0 )
            return;
        const FilterWheelItem& item = instance.installedFilterWheels[i];
        //TODO:  This is not the correct icon.  We need an icon that indicates that our filter wheel is either primary or not.
        node->SetIcon( 0, Bitmap( String( item.enabled ? ":/images/icons/enabled.png" : ":/images/icons/disabled.png" ) ) );
        node->SetAlignment( 0, TextAlign::Left );
        node->SetText( 1, item.filterWheelName );
        node->SetAlignment( 1, TextAlign::Right );
        node->SetIcon( 2, Bitmap( String( ":/images/icons/file.png" ) ) );
        String fileName = File::ExtractName( item.driverPath ) + File::ExtractExtension( item.driverPath );
        node->SetText( 2, fileName );
        node->SetToolTip( 2, item.driverPath );
        node->SetAlignment( 2, TextAlign::Left );
	}
	
    void ImageAcquisitionSettingsInterface::__FilterWheelButtons_Click( Button& sender, bool checked )
    {
        Console console;
        if ( sender == GUI->AddFW_PushButton )
        {
            try
            {
                AddFW();
                UpdateFWList();
            }
            ERROR_HANDLER
        }

    }

	//TODO:  Prune this handler if we have no use for it...
	void ImageAcquisitionSettingsInterface::__FilterWheel_CurrentNodeUpdated( TreeBox& sender, TreeBox::Node& current, TreeBox::Node& oldCurrent )
    {

    }

    //TODO:  Prune this handler if we have no use for it...
    void ImageAcquisitionSettingsInterface::__FilterWheel_NodeActivated( TreeBox& sender, TreeBox::Node& node, int col )
    {

    }

    void ImageAcquisitionSettingsInterface::__FilterWheel_NodeSelectionUpdated( TreeBox& sender )
    {
        bool isOne = sender.SelectedNodes().Length() == 1;
        GUI->MakeFW_PushButton.Enable( isOne );
        bool isOneOrMore = sender.SelectedNodes().Length() > 0;
        GUI->DeleteFW_PushButton.Enable( isOneOrMore );
    }


    ImageAcquisitionSettingsInterface::GUIData::GUIData( ImageAcquisitionSettingsInterface& w )
    {
        pcl::Font fnt = w.Font();
        int buttonWidth = fnt.Width( "Set as Primary Filter Wheel" ) * 1.5;
        Console c;
        c << "width: ";
        c << buttonWidth;
        /************ CAMERA PANEL ***********/
        CameraList_TreeBox.SetMinHeight( CAMERALIST_MINHEIGHT(fnt) );

        CameraList_TreeBox.SetNumberOfColumns( 3 );
        CameraList_TreeBox.HideHeader();
        CameraList_TreeBox.EnableMultipleSelections();
        CameraList_TreeBox.DisableRootDecoration();
        CameraList_TreeBox.EnableAlternateRowColor();

        CameraList_TreeBox.OnCurrentNodeUpdated( (TreeBox::node_navigation_event_handler) &ImageAcquisitionSettingsInterface::__CameraList_CurrentNodeUpdated,
                w );
        CameraList_TreeBox.OnNodeActivated( (TreeBox::node_event_handler) &ImageAcquisitionSettingsInterface::__CameraList_NodeActivated, w );
        CameraList_TreeBox.OnNodeSelectionUpdated( (TreeBox::tree_event_handler) &ImageAcquisitionSettingsInterface::__CameraList_NodeSelectionUpdated, w );

        AddCamera_PushButton.SetText( "Add Camera" );
        AddCamera_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w );
        AddCamera_PushButton.SetFixedWidth( buttonWidth );
        EditCamera_PushButton.SetText( "Edit Camera" );
        EditCamera_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w );
        EditCamera_PushButton.Enable( false );
        DeleteCamera_PushButton.SetText( "Delete Camera" );
        DeleteCamera_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w );
        DeleteCamera_PushButton.Enable( false );
        MakePrimary_PushButton.SetText( "Set as Primary Imager" );
        MakePrimary_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w );
        MakePrimary_PushButton.Enable( false );
        MakeGuider_PushButton.SetText( "Set as Guider" );
        MakeGuider_PushButton.Enable( false );
        MakeGuider_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w );

        CameraSelection_Control.SetSizer( CameraSelection_Sizer );
        CameraSelection_Control.AdjustToContents();

        CameraSelection_Sizer.Add( CameraList_TreeBox );

        CameraSelection_Sizer.Add( CameraListButtons_Sizer );

        LoadSettings_PushButton.SetText( "Load Current Settings" );
        SaveSettings_PushButton.SetText( "Save Settings" );

        LoadSettings_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__LoadSaveSettingsButtons_Click, w );
        SaveSettings_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__LoadSaveSettingsButtons_Click, w );

        LoadSaveSettings_Sizer.Add( LoadSettings_PushButton );
        LoadSaveSettings_Sizer.Add( SaveSettings_PushButton );

        CameraListButtons_Sizer.Add( AddCamera_PushButton );
        CameraListButtons_Sizer.Add( EditCamera_PushButton );
        CameraListButtons_Sizer.Add( DeleteCamera_PushButton );
        CameraListButtons_Sizer.Add( MakePrimary_PushButton );
        CameraListButtons_Sizer.Add( MakeGuider_PushButton );

        CameraListButtons_Sizer.SetSpacing( 4 );
        CameraListButtons_Sizer.AddStretch();
        /************ END CAMERA PANEL ***********/

        /************ FILTER_WHEEL PANEL ***********/
        FWList_TreeBox.SetMinHeight( CAMERALIST_MINHEIGHT(fnt) );

        FWList_TreeBox.SetNumberOfColumns( 3 );
        FWList_TreeBox.HideHeader();
        FWList_TreeBox.EnableMultipleSelections();
        FWList_TreeBox.DisableRootDecoration();
        FWList_TreeBox.EnableAlternateRowColor();

        FWList_TreeBox.OnCurrentNodeUpdated( (TreeBox::node_navigation_event_handler) &ImageAcquisitionSettingsInterface::__FilterWheel_CurrentNodeUpdated,
                w );
        FWList_TreeBox.OnNodeActivated( (TreeBox::node_event_handler) &ImageAcquisitionSettingsInterface::__FilterWheel_NodeActivated, w );
        FWList_TreeBox.OnNodeSelectionUpdated( (TreeBox::tree_event_handler) &ImageAcquisitionSettingsInterface::__FilterWheel_NodeSelectionUpdated, w );

        AddFW_PushButton.SetText( "Add Filter Wheel" );
        AddFW_PushButton.SetFixedWidth( buttonWidth );
        AddFW_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__FilterWheelButtons_Click, w );
        DeleteFW_PushButton.SetText( "Delete Filter Wheel" );
        DeleteFW_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__FilterWheelButtons_Click, w );
        DeleteFW_PushButton.Enable( false );
        MakeFW_PushButton.SetText( "Set as Primary Filter Wheel" );
        MakeFW_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__FilterWheelButtons_Click, w );
        MakeFW_PushButton.Enable( false );

        FWSelection_Control.SetSizer( FWSelection_Sizer );
        FWSelection_Control.AdjustToContents();

        FWSelection_Sizer.Add( FWList_TreeBox );

        FWSelection_Sizer.Add( FWListButtons_Sizer );

        FWListButtons_Sizer.Add( AddFW_PushButton );
        FWListButtons_Sizer.Add( DeleteFW_PushButton );
        FWListButtons_Sizer.Add( MakeFW_PushButton );

        FWListButtons_Sizer.SetSpacing( 4 );
        FWListButtons_Sizer.AddStretch();


        /********* END FILTER WHEEL ********/

        LoadSettings_PushButton.SetText( "Load Current Settings" );
        SaveSettings_PushButton.SetText( "Save Settings" );

        LoadSettings_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__LoadSaveSettingsButtons_Click, w );
        SaveSettings_PushButton.OnClick( (Button::click_event_handler) &ImageAcquisitionSettingsInterface::__LoadSaveSettingsButtons_Click, w );

        LoadSaveSettings_Sizer.Add( LoadSettings_PushButton );
        LoadSaveSettings_Sizer.Add( SaveSettings_PushButton );


        ImageAcquisitionSettings_TabBox.AddPage( CameraSelection_Control, "Camera" );
        ImageAcquisitionSettings_TabBox.AddPage( FWSelection_Control, "Filter Wheel" );

        Global_Sizer.SetMargin( 8 );
        Global_Sizer.SetSpacing( 6 );
        Global_Sizer.Add( ImageAcquisitionSettings_TabBox );
        Global_Sizer.Add( LoadSaveSettings_Sizer );

        w.SetSizer( Global_Sizer );
        w.SetFixedWidth();
        w.AdjustToContents();
    }



} // pcl
