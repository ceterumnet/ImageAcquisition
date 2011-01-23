#include "ImageAcquisitionSettingsInterface.h"
#include "ImageAcquisitionSettingsProcess.h"

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
    ProcessInterface(), instance( TheImageAcquisitionSettingsProcess ), GUI( 0 ), activeCamera( 0 )
  {
    TheImageAcquisitionSettingsInterface = this;
   
  }

  ImageAcquisitionSettingsInterface::~ImageAcquisitionSettingsInterface()
  {
    //globalItemControls.Clear();
    if ( GUI != 0 )
      delete GUI, GUI = 0;
	if ( activeCamera != 0)
	  delete activeCamera;
   
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

  bool ImageAcquisitionSettingsInterface::Launch( const MetaProcess& P, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ )
  {
    // ### Deferred initialization
    if ( GUI == 0 )
    {
		GUI = new GUIData( *this );
		SetWindowTitle( "Image Acquisition Settings" );
		UpdateControls();
    }
    dynamic = false;
    return &P == TheImageAcquisitionSettingsProcess;
  }

  ProcessImplementation* ImageAcquisitionSettingsInterface::NewProcess() const
  {
    return new ImageAcquisitionSettingsInstance( instance );
  }

  bool ImageAcquisitionSettingsInterface::ValidateProcess( const ProcessImplementation& p, pcl::String& whyNot ) const
  {
    const ImageAcquisitionSettingsInstance* r = dynamic_cast<const ImageAcquisitionSettingsInstance*>( &p );
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

  typedef IPixInsightCamera* (*MyFuncPtr)();

  
  static size_type TreeInsertionIndex( const TreeBox& tree )
  {
	  const TreeBox::Node* n = tree.CurrentNode();
	  return (n != 0) ? tree.ChildIndex( n ) + 1 : tree.NumberOfChildren();
  }

  void ImageAcquisitionSettingsInterface::AddCamera()
  {
	  	// Not sure if this should be a new instance...or just reuse...I think reuse is better.
	//CameraDialog dlg = new CameraDialog;
		if(GUI->CamDlg.Execute())
		{
			size_type i0 = TreeInsertionIndex( GUI->CameraList_TreeBox );
			instance.installedCameras.Insert( instance.installedCameras.At( i0++ ), ImageAcquisitionSettingsInstance::CameraItem( GUI->CamDlg.GetCameraName(), GUI->CamDlg.GetDriverFile() ) );
#ifdef __PCL_WINDOWS
			if(activeCamera == 0)
			{
				HINSTANCE loadedLib = NULL;
				loadedLib = LoadLibrary("c:\\PCL64\\bin\\TestDriver-pxi.dll");
				MyFuncPtr InitializePtr = NULL;

				InitializePtr = (MyFuncPtr) (// get the function pointer
					GetProcAddress( loadedLib, "InitializeCamera" ) 
					);
				if(InitializePtr == NULL) 
				{
					Console().WriteLn("Failed!");	
				}
				else
				{
					activeCamera = static_cast<IPixInsightCamera *> (InitializePtr());
					String theString = activeCamera->DoSomething();
					Console().Write("we got some data from the driver: ");	
					Console().WriteLn(theString);
				}
			}
			else
			{
				Console().Write("Camera Already Instantiated: ");
			}

#endif
#ifdef __PCL_MACOSX
			Console().WriteLn("We are dealing with a mac env ");
			void* libHandle = NULL;
			libHandle = dlopen("/Applications/PixInsight64.app/Contents/MacOS/libTestMacOSXDriver-pxi.dylib", RTLD_NOW);
			if(libHandle != NULL)
			{
				MyFuncPtr InitializePtr = NULL;
				InitializePtr = (MyFuncPtr)dlsym(libHandle, "InitializeCamera");
				//(void *)(IPixInsightCamera* (*InitializePtr)(void)) = dlsym(libHandle, "InitializeCamera");
				if(InitializePtr)
				{
					Console().WriteLn("Successfully loaded function. ");
					IPixInsightCamera *theCamera = NULL;
					theCamera = static_cast<IPixInsightCamera *> (InitializePtr());
					String theString = theCamera->DoSomething();
					Console().WriteLn("From the lib: ");
					Console().WriteLn(theString);
					delete theCamera;
					dlclose(libHandle);
				}
				else
				{
					Console().WriteLn("Problem Loading Function. ");
					Console().WriteLn(dlerror());
				}
			}
			else
			{
				Console().WriteLn("Problem Loading Library. ");
				Console().WriteLn(dlerror());
			}
#endif
		}
  }

  void ImageAcquisitionSettingsInterface::__CameraListButtons_Click( Button& sender, bool checked )
  {
    if(sender == GUI->AddCamera_PushButton)
	{
		AddCamera();
		UpdateCameraList();
	}
    else if(sender == GUI->EditCamera_PushButton)
	{

	}
    else if(sender == GUI->DeleteCamera_PushButton)
	{

	}
    else
	{

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

  }

  ImageAcquisitionSettingsInterface::GUIData::GUIData( ImageAcquisitionSettingsInterface& w )
  {
    pcl::Font fnt = w.Font();
    CameraList_TreeBox.SetMinHeight(CAMERALIST_MINHEIGHT(fnt));

    CameraList_TreeBox.SetNumberOfColumns( 3 );
    //CameraList_TreeBox.HideHeader();
    //CameraList_TreeBox.EnableMultipleSelections();
    CameraList_TreeBox.DisableRootDecoration();
    CameraList_TreeBox.EnableAlternateRowColor();

    CameraList_TreeBox.OnCurrentNodeUpdated( (TreeBox::node_navigation_event_handler)&ImageAcquisitionSettingsInterface::__CameraList_CurrentNodeUpdated, w );
    CameraList_TreeBox.OnNodeActivated( (TreeBox::node_event_handler)&ImageAcquisitionSettingsInterface::__CameraList_NodeActivated, w );
    CameraList_TreeBox.OnNodeSelectionUpdated( (TreeBox::tree_event_handler)&ImageAcquisitionSettingsInterface::__CameraList_NodeSelectionUpdated, w );
	
    AddCamera_PushButton.SetText("Add Camera");
    AddCamera_PushButton.OnClick( (Button::click_event_handler)&ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w);
    EditCamera_PushButton.SetText("Edit Camera");
    EditCamera_PushButton.OnClick( (Button::click_event_handler)&ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w);
    DeleteCamera_PushButton.SetText("Delete Camera");
    DeleteCamera_PushButton.OnClick( (Button::click_event_handler)&ImageAcquisitionSettingsInterface::__CameraListButtons_Click, w);
	
    CameraSelection_Control.SetSizer( CameraSelection_Sizer);
    CameraSelection_Control.AdjustToContents();
	
    CameraSelection_Sizer.Add(CameraList_TreeBox);

    CameraSelection_Sizer.Add(CameraListButtons_Sizer);

    CameraListButtons_Sizer.Add(AddCamera_PushButton);
    CameraListButtons_Sizer.Add(EditCamera_PushButton);
    CameraListButtons_Sizer.Add(DeleteCamera_PushButton);
	CameraListButtons_Sizer.SetSpacing( 4 );
	CameraListButtons_Sizer.AddStretch();

    ImageAcquisitionSettings_TabBox.AddPage( CameraSelection_Control, "Camera" );

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

  // ----------------------------------------------------------------------------


  // ----------------------------------------------------------------------------

} // pcl
