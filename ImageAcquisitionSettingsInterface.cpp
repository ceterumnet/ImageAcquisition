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
	//UpdateControls();
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
    //UpdateControls();
    return true;
  }

  void ImageAcquisitionSettingsInterface::SaveSettings() const
  {
  }

  typedef IPixInsightCamera* (*MyFuncPtr)();

  void ImageAcquisitionSettingsInterface::__CameraListButtons_Click( Button& sender, bool checked )
  {
    if(sender == GUI->AddCamera_PushButton)
      {
	Console().WriteLn("add camera button pushed!");	
	// Not sure if this should be a new instance...or just reuse...I think reuse is better.
	//CameraDialog dlg = new CameraDialog;
	GUI->CamDlg.Execute();
#ifdef __PCL_WINDOWS
	HINSTANCE loadedLib = NULL;
	loadedLib = LoadLibrary("c:\\PCL64\\bin\\TestDriver-pxi.dll");
	MyFuncPtr InitializePtr = NULL;
	Console().WriteLn("about to reinterpret cast...");		
	InitializePtr = (MyFuncPtr) (// get the function pointer
				     GetProcAddress( loadedLib, "InitializeCamera" ) 
				     );
	if(InitializePtr == NULL) 
	  {
	    Console().WriteLn("Failed!");	
	  }
	else
	  {
	    Console().WriteLn("reinterpreted cast!");	
	    IPixInsightCamera *theCamera = NULL;
	    Console().WriteLn("a little more...");	
	    theCamera = static_cast<IPixInsightCamera *> (InitializePtr());
	    Console().WriteLn("we are getting somewhere!!!");	
	    String theString = theCamera->DoSomething();
	    Console().Write("we got some data: ");	
	    Console().WriteLn(theString);
	    delete theCamera;
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


  // ----------------------------------------------------------------------------


  // ----------------------------------------------------------------------------

} // pcl
