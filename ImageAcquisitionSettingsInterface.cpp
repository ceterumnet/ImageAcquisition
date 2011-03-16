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

#ifdef __PCL_MACOSX
#include <dlfcn.h>
#endif

#define CAMERALIST_MINHEIGHT( fnt )  (8*fnt.Height() + 2)

namespace pcl
{

    ImageAcquisitionSettingsInterface* TheImageAcquisitionSettingsInterface = 0;

#include "ImageAcquisitionSettingsIcon.xpm"

    // ----------------------------------------------------------------------------

    ImageAcquisitionSettingsInterface::ImageAcquisitionSettingsInterface() :
        ProcessInterface(), instance( TheImageAcquisitionSettingsProcess ), GUI( 0 )
    {
        TheImageAcquisitionSettingsInterface = this;
    }

    ImageAcquisitionSettingsInterface::~ImageAcquisitionSettingsInterface()
    {
        //globalItemControls.Clear();
        if ( GUI != 0 )
            delete GUI, GUI = 0;
    }

    IsoString ImageAcquisitionSettingsInterface::Id() const
    {
        return "ImageAcquisitionSettings";
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
            UpdateControls();
        }

        if( cameraData == 0 )
            cameraData = new CameraData;
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
            whyNot = "Not a ImageAcquisitionSettings instance.";
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
            instance.installedCameras.Insert( instance.installedCameras.At( i0++ ), ImageAcquisitionSettingsInstance::CameraItem( GUI->CamDlg.GetCameraName(),
                    GUI->CamDlg.GetDriverFile() ) );
        }
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
        else if ( sender == GUI->EditCamera_PushButton )
        {
            int currentIdx = GUI->CameraList_TreeBox.ChildIndex( GUI->CameraList_TreeBox.CurrentNode() );
            //instance.installedCameras[currentIdx]
        }
        else if ( sender == GUI->DeleteCamera_PushButton )
        {
            try
            {
                int currentIdx = GUI->CameraList_TreeBox.ChildIndex( GUI->CameraList_TreeBox.CurrentNode() );
                if( instance.installedCameras[currentIdx].cam && instance.installedCameras[currentIdx].cam.Connected() )
                    throw Error( "Can't delete an imager while it is connected.");

                //TODO: I need to deal with the user deleting the primary imager.
                //The expose image interface will still work I think because there is a global reference
                //to the cameraData...maybe this will get figured out with the persistant camera settings.
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

                instance.installedCameras[currentIdx].enabled = true;
                if( instance.installedCameras[currentIdx].cam == NULL)
                    InitializeCamera( instance.installedCameras[currentIdx] );
                cameraData->mutex.Lock();
                cameraData->cam = instance.installedCameras[currentIdx].cam;
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

    void ImageAcquisitionSettingsInterface::__CameraList_CurrentNodeUpdated( TreeBox& sender, TreeBox::Node& current, TreeBox::Node& oldCurrent )
    {

    }

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

    ImageAcquisitionSettingsInterface::GUIData::GUIData( ImageAcquisitionSettingsInterface& w )
    {
        pcl::Font fnt = w.Font();
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

        CameraListButtons_Sizer.Add( AddCamera_PushButton );
        CameraListButtons_Sizer.Add( EditCamera_PushButton );
        CameraListButtons_Sizer.Add( DeleteCamera_PushButton );
        CameraListButtons_Sizer.Add( MakePrimary_PushButton );
        CameraListButtons_Sizer.Add( MakeGuider_PushButton );

        CameraListButtons_Sizer.SetSpacing( 4 );
        CameraListButtons_Sizer.AddStretch();


        ImageAcquisitionSettings_TabBox.AddPage( CameraSelection_Control, "Camera" );
        ImageAcquisitionSettings_TabBox.AddPage( FWSelection_Control, "Filter Wheel" );

        Global_Sizer.SetMargin( 8 );
        Global_Sizer.SetSpacing( 6 );
        Global_Sizer.Add( ImageAcquisitionSettings_TabBox );

        w.SetSizer( Global_Sizer );
        w.SetFixedWidth();
        w.AdjustToContents();
    }

    void ImageAcquisitionSettingsInterface::UpdateCameraItem( size_type i )
    {
        TreeBox::Node* node = GUI->CameraList_TreeBox[i];
        if ( node == 0 )
            return;
        const ImageAcquisitionSettingsInstance::CameraItem& item = instance.installedCameras[i];
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
        Console c = Console();
        c << "UpdateCameraList() called\n";
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

    ImageAcquisitionSettingsInstance::CameraItem *ImageAcquisitionSettingsInterface::GetPrimaryImager()
    {
        for ( size_type i = 0; i < instance.installedCameras.Length(); ++i )
            if ( instance.installedCameras[i].enabled )
                return &instance.installedCameras[i];
        return NULL;
    }

    typedef IPixInsightCamera* (*MyFuncPtr)();
    void ImageAcquisitionSettingsInterface::InitializeCamera( const ImageAcquisitionSettingsInstance::CameraItem &cItem )
    {
        IsoString theString = cItem.driverPath;
        const char * chars = theString.c_str();
        MyFuncPtr InitializePtr = NULL;
        if ( cItem.cam == 0 )
        {
#ifdef __PCL_WINDOWS

            //HINSTANCE loadedLib = NULL;
            cItem.libHandle = LoadLibrary(chars);
            InitializePtr = (MyFuncPtr) (// get the function pointer
                    GetProcAddress( cItem.libHandle, "InitializeCamera" )
            );

#endif
#ifdef __PCL_MACOSX
            cItem.libHandle = dlopen( chars, RTLD_NOW );
            if ( cItem.libHandle == NULL )
            {
                throw Error( "Problem loading driver" );
                Console().WriteLn( dlerror() );
            }
            else
            {
                InitializePtr = (MyFuncPtr) dlsym( cItem.libHandle, "InitializeCamera" );
            }
#endif

            if ( InitializePtr == NULL )
            {
                throw Error( "Failed to load library.  Make sure that you've pointed to a valid driver file." );
            }
            else
            {
                cItem.cam = dynamic_cast<IPixInsightCamera *> ( InitializePtr() );
                String theString = cItem.cam->Description();
                Console().Write( "Loaded driver: " );
                Console().WriteLn( theString );
            }
        }
        else
        {
            Console().Write( "Camera Already Intialized: " );
        }
    }
} // pcl
