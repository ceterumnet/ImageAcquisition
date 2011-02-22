#include "ExposeImageInterface.h"
#include "ExposeImageProcess.h"
#include "CameraDialog.h"

#include <pcl/Dialog.h>
#include <pcl/FileDialog.h>
#include <pcl/ViewList.h>
#include <pcl/GlobalSettings.h>
#include <pcl/ErrorHandler.h>
#include <pcl/Console.h>
#include <pcl/Thread.h>
#include <pcl/Timer.h>

namespace pcl
{

    ExposeImageInterface* TheExposeImageInterface = 0;

#include "ExposeImageIcon.xpm"

  ExposeImageInterface::ExposeImageInterface() :
    ProcessInterface(), instance( TheExposeImageProcess ), GUI( 0 )
  {
    TheExposeImageInterface = this;
    cameraConnected = false;
  }

  ExposeImageInterface::~ExposeImageInterface()
  {
    if ( GUI != 0 )
      delete GUI, GUI = 0;
    Console().WriteLn("Destroying ExposeImageInterface");
  }

  IsoString ExposeImageInterface::Id() const
  {
    return "ExposeImage";
  }

  uint32 ExposeImageInterface::Version() const
  {
    return 0x100;
  }

  const char** ExposeImageInterface::IconImageXPM() const
  {
    return ExposeImageIcon_XPM;
  }

  InterfaceFeatures ExposeImageInterface::Features() const
  {
    return InterfaceFeature::DefaultGlobal;
  }

  void ExposeImageInterface::ApplyInstance() const
  {
    instance.LaunchOnCurrentView();
  }

  void ExposeImageInterface::ResetInstance()
  {
    ExposeImageInstance defaultInstance( TheExposeImageProcess );
    ImportProcess( defaultInstance );
  }

  bool ExposeImageInterface::Launch( const MetaProcess& P, const ProcessImplementation*, bool& dynamic, unsigned& flags )
  {
    // ### Deferred initialization
    if ( GUI == 0 )
        {
            GUI = new GUIData( *this );
            SetWindowTitle( "ExposeImage" );
            UpdateControls();

            // Restore position only
            if ( !RestoreGeometry() )
                SetDefaultPosition();
            AdjustToContents();
        }

    dynamic = false;
    return &P == TheExposeImageProcess;
  }

  ProcessImplementation* ExposeImageInterface::NewProcess() const
  {
    return new ExposeImageInstance( instance );
  }

  bool ExposeImageInterface::ValidateProcess( const ProcessImplementation& p, pcl::String& whyNot ) const
  {
    const ExposeImageInstance* r = dynamic_cast<const ExposeImageInstance*>( &p );

    if ( r == 0 )
        {
            whyNot = "Not an ExposeImage instance.";
            return false;

        }

    whyNot.Clear();
    return true;
  }

  bool ExposeImageInterface::RequiresInstanceValidation() const
  {
    return true;
  }

  bool ExposeImageInterface::ImportProcess( const ProcessImplementation& p )
  {
    instance.Assign( p );
    UpdateControls();
    return true;
  }

  void ExposeImageInterface::SaveSettings() const
  {
    SaveGeometry();
  }

  // ----------------------------------------------------------------------------
  // ----------------------------------------------------------------------------

  void ExposeImageInterface::UpdateControls()
  {
    UpdateCameraControls();
    UpdateExposureControls();
	UpdateOutputControls();
  }

  //I don't know if this should be an update call or something else...
  void ExposeImageInterface::UpdateCameraControls()
  {
	  ImageAcquisitionSettingsInstance::CameraItem *cItem = TheImageAcquisitionSettingsInterface->GetPrimaryImager();

	  if(cItem)
		  GUI->ActiveCamera_Edit.SetText(cItem->cameraName);
		
  }

  void ExposeImageInterface::UpdateExposureControls()
  {
	  if( GUI->Exposure_SectionBar.IsEnabled() )
	  {
		  GUI->BinModeX_ComboBox.SetCurrentItem( TheImageAcquisitionSettingsInterface->activeCamera->BinX() - 1 );
		  GUI->BinModeY_ComboBox.SetCurrentItem( TheImageAcquisitionSettingsInterface->activeCamera->BinY() - 1 );
		  //GUI->Filter_ComboBox.SetCurrentItem( 0 );
		  GUI->NumberOfExposures_SpinBox.SetValue( instance.exposureCount );
		  GUI->ExposureDuration_NumericControl.SetValue( instance.exposureDuration );
		  GUI->X1_Edit.SetRange(0, TheImageAcquisitionSettingsInterface->activeCamera->NumX() );
		  GUI->Y1_Edit.SetRange(0, TheImageAcquisitionSettingsInterface->activeCamera->NumY() );
		  GUI->X2_Edit.SetRange(0, TheImageAcquisitionSettingsInterface->activeCamera->NumX() );
		  GUI->Y2_Edit.SetRange(0, TheImageAcquisitionSettingsInterface->activeCamera->NumY() );
		  GUI->X1_Edit.SetValue( instance.subFrameX1 );
		  GUI->Y1_Edit.SetValue( instance.subFrameY1 );
		  GUI->X2_Edit.SetValue( instance.subFrameX2 );
		  GUI->Y2_Edit.SetValue( instance.subFrameY2 );
		  GUI->DelayBetweenExposures_NumericEdit.SetValue( instance.delayBetweenExposures );
	  }
  }

  void ExposeImageInterface::__Exposure_NumericValueUpdated( NumericEdit& sender, double value )
  {
	  if ( sender == GUI->ExposureDuration_NumericControl )
		  instance.exposureDuration = value;
	  if ( sender == GUI->DelayBetweenExposures_NumericEdit )
		  instance.delayBetweenExposures = value;
	  if( sender == GUI->X1_Edit )
		  instance.subFrameX1 = value;
	  if( sender == GUI->Y1_Edit )
		  instance.subFrameY1 = value;
	  if( sender == GUI->X2_Edit )
		  instance.subFrameX2 = value;
	  if( sender == GUI->Y2_Edit )
		  instance.subFrameY2 = value;
  }

  void ExposeImageInterface::__Exposure_SpinValueUpdated( SpinBox& sender, int value )
  {
	  if ( sender == GUI->NumberOfExposures_SpinBox )
		  instance.exposureCount = value;
  }

  void ExposeImageInterface::__BinMode_ComboBoxItem_Highlighted( ComboBox& sender, int value )
  {
	  if ( sender == GUI->BinModeX_ComboBox )
		  instance.binModeX = value + 1;
	  if ( sender == GUI->BinModeY_ComboBox )
		  instance.binModeY = value + 1;
  }

  void ExposeImageInterface::__FileEdit_EditCompleted( Edit& sender )
  {
	  if( sender == GUI->FileOutputPath_Edit )
		  instance.fileOutputPath = GUI->FileOutputPath_Edit.Text();
	  if( sender == GUI->FileOutputPattern_Edit )
		  instance.fileOutputPattern = GUI->FileOutputPattern_Edit.Text();
  }

  void ExposeImageInterface::UpdateOutputControls()
  {
	  GUI->FileOutputPath_Edit.SetText( instance.fileOutputPath );
	  GUI->FileOutputPattern_Edit.SetText( instance.fileOutputPattern );
  }
  
  void ExposeImageInterface::__ToggleSection( SectionBar& sender, Control& section, bool start )	
  {

  }

  void ExposeImageInterface::__CameraConnectionButton_Click( Button& sender, bool checked )
  {
      if ( sender == GUI->CameraConnection_PushButton && TheImageAcquisitionSettingsInterface->activeCamera )
        {	//TODO:  This is a crappy way to check if the camera is connected...but it will do for now.
            if ( GUI->CameraConnection_PushButton.Text().Compare( "Connect Camera" ) == 0 )
            {
                TheImageAcquisitionSettingsInterface->activeCamera->SetConnected( true );
				
				UpdateControlsForCameraFeatures();
                EnableExposureButtons( true );
				UpdateControls();
            } else {
                TheImageAcquisitionSettingsInterface->activeCamera->SetConnected( false );
                EnableExposureButtons( false );
            }
        }
  }

  //set the dropdowns for the appropriate bin levels etc...
  void ExposeImageInterface::UpdateControlsForCameraFeatures()
  {
	  GUI->BinModeX_ComboBox.Clear();
	  for( size_type i = 1, n = TheImageAcquisitionSettingsInterface->activeCamera->MaxBinX(); i == n; ++i )
	  {
		  GUI->BinModeX_ComboBox.AddItem( String(i) );
	  }
	  
	  GUI->BinModeY_ComboBox.Clear(); 
	  for( size_type i = 1, n = TheImageAcquisitionSettingsInterface->activeCamera->MaxBinY(); i == n; ++i )
	  {
		  GUI->BinModeY_ComboBox.AddItem( String(i) );
	  }
  }

  void ExposeImageInterface::EnableExposureButtons( bool enable = true )
    {
        GUI->Exposure_SectionBar.Enable( enable );
        GUI->SetTemperature_PushButton.Enable( enable );
        GUI->CameraConnection_PushButton.SetText( "Connect Camera" );
        if ( enable )
            GUI->CameraConnection_PushButton.SetText( "Disconnect Camera" );
    }

  // ----------------------------------------------------------------------------
  // ----------------------------------------------------------------------------

  ExposeImageInterface::GUIData::GUIData( ExposeImageInterface& w )
  {
	pcl::Font fnt = w.Font();
	int labelWidth1 = fnt.Width( String( "Delay Between Exposures (seconds):" ) + 'T' );
	int labelWidth3 = fnt.Width( String( "Select Filter Wheel and some") + 'T' );
    //#ifndef __PCL_MACOSX
    //I guess this is a trick to get MACOSX spacing correct
    //TargetButtons_Sizer.SetSpacing( 4 );
    //#endif
	Camera_SectionBar.SetTitle( "Camera" );
    Camera_SectionBar.SetSection( Camera_Control );
    Camera_SectionBar.OnToggleSection( (SectionBar::section_event_handler)&ExposeImageInterface::__ToggleSection, w );
    
    Camera_Label.SetText("Selected Camera:");
	Camera_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	Camera_Label.SetFixedWidth(labelWidth1);
	ActiveCamera_Edit.SetReadOnly();
	ChooseCamera_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" )));
	ChooseCamera_ToolButton.OnClick((Button::click_event_handler)&ExposeImageInterface::__CameraConnectionButton_Click, w);
	CameraConnection_PushButton.SetText("Connect Camera");
	CameraConnection_PushButton.SetFixedWidth(labelWidth3);
	CameraConnection_PushButton.OnClick((Button::click_event_handler)&ExposeImageInterface::__CameraConnectionButton_Click, w);
	Camera_Sizer.Add(Camera_Label, 0);
    Camera_Sizer.Add(ActiveCamera_Edit, 0);
	Camera_Sizer.Add(ChooseCamera_ToolButton,0);
	Camera_Sizer.Add(CameraConnection_PushButton, 0);
    Camera_Sizer.SetSpacing( 4 );

	Temperature_Label.SetText("Camera Temp:");
	Temperature_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	Temperature_Label.SetFixedWidth(labelWidth1);
	CurrentTemperatureReading_Label.SetText("--C");
	SetTemperature_PushButton.SetText("Set Temperature");
	SetTemperature_PushButton.SetFixedWidth(labelWidth3);
	Temperature_Sizer.Add(Temperature_Label);
	Temperature_Sizer.Add(CurrentTemperatureReading_Label);
	Temperature_Sizer.Add(SetTemperature_PushButton);
	Temperature_Sizer.SetSpacing( 4 );

	FilterWheel_Label.SetText("Active Filter Wheel:");
	FilterWheel_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	FilterWheel_Label.SetFixedWidth(labelWidth1);
	FilterWheelConnection_PushButton.SetText("Select Filter Wheel");
	FilterWheelConnection_PushButton.SetFixedWidth(labelWidth3);
	FilterWheel_Edit.SetReadOnly();
	FilterWheel_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" )));
	FilterWheel_Sizer.Add(FilterWheel_Label);
	FilterWheel_Sizer.Add(FilterWheel_Edit);
	FilterWheel_Sizer.Add(FilterWheel_ToolButton);
	FilterWheel_Sizer.Add(FilterWheelConnection_PushButton);
	FilterWheel_Sizer.SetSpacing( 4 );

	CameraControl_Sizer.Add(Camera_Sizer);
	CameraControl_Sizer.Add(Temperature_Sizer);
	CameraControl_Sizer.Add(FilterWheel_Sizer);

    Camera_Control.SetSizer( CameraControl_Sizer );
    //Camera_Control.AdjustToContents();

	Exposure_SectionBar.SetTitle("Exposure");
	Exposure_SectionBar.SetSection(ExposureSection_Control);
	
	BinModeX_Label.SetText("Bin Mode X:");
	BinModeX_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	BinModeX_Label.SetFixedWidth(labelWidth1);
    BinModeY_Label.SetText("Bin Mode Y:");
    BinModeY_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
    BinModeY_Label.SetFixedWidth(labelWidth1);
	Binning_Sizer.Add(BinModeX_Label);
	Binning_Sizer.Add(BinModeX_ComboBox);
	Binning_Sizer.Add(BinModeY_Label);
	Binning_Sizer.Add(BinModeY_ComboBox);
	Binning_Sizer.SetSpacing( 4 );
	BinModeX_ComboBox.OnItemHighlighted( (ComboBox::item_event_handler)&ExposeImageInterface::__BinMode_ComboBoxItem_Highlighted, w);

	Filter_Label.SetText("Filter:");
	Filter_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	Filter_Label.SetFixedWidth(labelWidth1);
	Filter_Sizer.Add(Filter_Label);
	Filter_Sizer.Add(Filter_ComboBox);
	Filter_Sizer.SetSpacing( 4 );
	
	NumberOfExposures_Label.SetText("Number of Exposures:");
	NumberOfExposures_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	NumberOfExposures_Label.SetFixedWidth(labelWidth1);
	NumberOfExposures_Sizer.Add(NumberOfExposures_Label);
	NumberOfExposures_Sizer.Add(NumberOfExposures_SpinBox);
	NumberOfExposures_SpinBox.OnValueUpdated( (SpinBox::value_event_handler)&ExposeImageInterface::__Exposure_SpinValueUpdated, w );
	NumberOfExposures_Sizer.SetSpacing( 4 );

	ExposureDuration_NumericControl.label.SetText("Exposure Duration (seconds):");
	ExposureDuration_NumericControl.label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	ExposureDuration_NumericControl.label.SetFixedWidth(labelWidth1);
	ExposureDuration_NumericControl.SetRange(0.001, uint16_max);
	ExposureDuration_NumericControl.SetPrecision(3);
	ExposureDuration_NumericControl.OnValueUpdated( (NumericEdit::value_event_handler)&ExposeImageInterface::__Exposure_NumericValueUpdated, w );
	ExposureDuration_Sizer.Add(ExposureDuration_NumericControl);
	ExposureDuration_Sizer.SetSpacing( 4 );

	SubFrame_Label.SetText("Subframe:");
	SubFrame_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	SubFrame_Label.SetFixedWidth(labelWidth1);
	int labelWidth2 = fnt.Width( String( "x1:" ) + 'T' );
	X1_Label.SetText("x1:");
	X1_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	X1_Label.SetFixedWidth(labelWidth2);
	X1_Edit.SetMaxWidth( labelWidth2*2 );
	X1_Edit.OnValueUpdated( (NumericEdit::value_event_handler)&ExposeImageInterface::__Exposure_NumericValueUpdated, w );
	X1_Edit.SetInteger();
	
	Y1_Label.SetText("y1:");
	Y1_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	Y1_Label.SetFixedWidth(labelWidth2);
	Y1_Edit.SetFixedWidth( labelWidth2*2 );
	Y1_Edit.OnValueUpdated( (NumericEdit::value_event_handler)&ExposeImageInterface::__Exposure_NumericValueUpdated, w );
	Y1_Edit.SetInteger();	
	
	X2_Label.SetText("x2:");
	X2_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	X2_Label.SetFixedWidth(labelWidth2);
	X2_Edit.SetFixedWidth( labelWidth2*2 );
	X2_Edit.OnValueUpdated( (NumericEdit::value_event_handler)&ExposeImageInterface::__Exposure_NumericValueUpdated, w );
	X2_Edit.SetInteger();
	
	Y2_Label.SetText("y2:");
	Y2_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	Y2_Label.SetFixedWidth(labelWidth2);
	Y2_Edit.SetFixedWidth( labelWidth2*2 );
	Y2_Edit.OnValueUpdated( (NumericEdit::value_event_handler)&ExposeImageInterface::__Exposure_NumericValueUpdated, w );
	Y2_Edit.SetInteger();
	
	SelectSubFrame_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" )));
	
	SubFrame_Sizer.Add(SubFrame_Label);
	SubFrame_Sizer.Add(X1_Label);
	SubFrame_Sizer.Add(X1_Edit);
	SubFrame_Sizer.Add(Y1_Label);
	SubFrame_Sizer.Add(Y1_Edit);
	SubFrame_Sizer.Add(X2_Label);
	SubFrame_Sizer.Add(X2_Edit);
	SubFrame_Sizer.Add(Y2_Label);
	SubFrame_Sizer.Add(Y2_Edit);
	SubFrame_Sizer.Add(SelectSubFrame_ToolButton);
	SubFrame_Sizer.SetSpacing( 4 );

	DelayBetweenExposures_Label.SetText("Delay Between Exposures (seconds):");
	DelayBetweenExposures_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	DelayBetweenExposures_Label.SetFixedWidth(labelWidth1);
	Delay_Sizer.Add(DelayBetweenExposures_Label);
	Delay_Sizer.Add(DelayBetweenExposures_NumericEdit);
	Delay_Sizer.SetSpacing( 4 );
	DelayBetweenExposures_NumericEdit.SetInteger();
	DelayBetweenExposures_NumericEdit.SetRange(0, uint16_max);

	ExposureSection_Sizer.Add(Binning_Sizer);
	ExposureSection_Sizer.Add(Filter_Sizer);
	ExposureSection_Sizer.Add(NumberOfExposures_Sizer);
	ExposureSection_Sizer.Add(ExposureDuration_Sizer);
	ExposureSection_Sizer.Add(SubFrame_Sizer);
	ExposureSection_Sizer.Add(Delay_Sizer);

	ExposureSection_Control.SetSizer(ExposureSection_Sizer);
	ExposureSection_Control.AdjustToContents();
	
	FileOutput_SectionBar.SetTitle("Output");
	FileOutput_SectionBar.SetSection(FileOutputSection_Control);

	FileOutputPath_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" )));
	FileOutputPath_Label.SetText("File Output Path:");
	FileOutputPath_Label.SetFixedWidth(labelWidth1);
	FileOutputPath_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	FileOutputPath_Sizer.Add(FileOutputPath_Label);
	FileOutputPath_Sizer.Add(FileOutputPath_Edit);
	FileOutputPath_Sizer.Add(FileOutputPath_ToolButton);
	FileOutputPath_Sizer.SetSpacing( 4 );
	FileOutputPath_Edit.OnEditCompleted( (Edit::edit_event_handler)& ExposeImageInterface::__FileEdit_EditCompleted, w );


	FileOutputPattern_Label.SetText("File Output Pattern:");
	FileOutputPattern_Label.SetTextAlignment( TextAlign::Right|TextAlign::VertCenter );
	FileOutputPattern_Label.SetFixedWidth(labelWidth1);
	FileOutputPattern_ToolButton.SetIcon( Bitmap( String( ":/images/icons/select.png" )));
	FileOutputPattern_Sizer.Add(FileOutputPattern_Label);
	FileOutputPattern_Sizer.Add(FileOutputPattern_Edit);
	FileOutputPattern_Sizer.Add(FileOutputPattern_ToolButton);
	FileOutputPattern_Sizer.SetSpacing( 4 );
	FileOutputPattern_Edit.OnEditCompleted( (Edit::edit_event_handler)& ExposeImageInterface::__FileEdit_EditCompleted, w );

	FileOutputSection_Sizer.Add(FileOutputPath_Sizer);
	FileOutputSection_Sizer.Add(FileOutputPattern_Sizer);
	
	FileOutputSection_Control.SetSizer(FileOutputSection_Sizer);
	FileOutputSection_Control.AdjustToContents();


    Global_Sizer.SetMargin( 8 );
    Global_Sizer.SetSpacing( 6 );
    
	Global_Sizer.Add( Camera_SectionBar );
    Global_Sizer.Add( Camera_Control );
	Global_Sizer.Add( Exposure_SectionBar );
	Global_Sizer.Add( ExposureSection_Control );
    Global_Sizer.Add( FileOutput_SectionBar );
	Global_Sizer.Add( FileOutputSection_Control );

	//By default these should be disabled
	Exposure_SectionBar.Enable(false);
	SetTemperature_PushButton.Enable(false);

    w.SetSizer( Global_Sizer );

    w.SetFixedWidth();
	w.SetFixedHeight();
    w.AdjustToContents();
	
  }

  void ExposeImageInterface::UpdateTemperature()
  {
      GUI->Temperature_Label.SetText( String( TheImageAcquisitionSettingsInterface->activeCamera->CCDTemperature() ) );
  }
  // ----------------------------------------------------------------------------

  // So, in theory, this thread should be periodically udpating the data in the ExposeImage window like Temp, exposure progress...etc...
//  class CameraControlThread: public Thread
//    {
//    public:
//        CameraControlThread(IPixInsightCamera *_cam, int _pollingInterval = 5)
//        {
//            cam = _cam;
//            pollingInterval = _pollingInterval;
//            stayConnected = true;
//        }
//
//        virtual ~CameraControlThread()
//        {
//            Console().WriteLn( "Killed Camera Connection Thread" );
//        }
//
//        void DisconnectCamera()
//        {
//            stayConnected = false;
//        }
//
//        IPixInsightCamera::CameraStateEnum CameraState()
//        {
//            return cam->CameraState();
//        }
//
//        virtual void Run()
//        {
//            Console().WriteLn( "Started Camera Connection Thread" );
//            //Need a Mutex lock here possibly?
//            while(stayConnected)
//            {
//                Timer mainTimer;
//                mainTimer.SetInterval(pollingInterval);
//                mainTimer.Start();
//                Console().WriteLn( "CameraConnection Thread running..." );
//            }
//            Console().WriteLn( "CameraConnection Thread stopped..." );
//        }
//    private:
//        bool stayConnected;
//        IPixInsightCamera *cam;
//        int pollingInterval;
//    };

} // pcl

// ****************************************************************************
// EOF ExposeImageInterface.cpp - Released 2010/12/14 09:34:27 UTC
