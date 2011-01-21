
#ifndef __ExposeImageInterface_h
#define __ExposeImageInterface_h

#include <pcl/ProcessInterface.h>

#include <pcl/Sizer.h>
#include <pcl/SectionBar.h>
#include <pcl/ToolButton.h>
#include <pcl/PushButton.h>
#include <pcl/NumericControl.h>
#include <pcl/TreeBox.h>
#include <pcl/SpinBox.h>
#include <pcl/ComboBox.h>
#include <pcl/CheckBox.h>
#include <pcl/TextBox.h>
#include <pcl/SpinBox.h>

#include "ExposeImageInstance.h"

namespace pcl
{

  class CameraConnectionThread;
  // ----------------------------------------------------------------------------

  class ExposeImageInterface : public ProcessInterface
  {
  public:

    ExposeImageInterface();
    virtual ~ExposeImageInterface();

    virtual IsoString Id() const;
    virtual uint32 Version() const;
    virtual const char** IconImageXPM() const;

    InterfaceFeatures Features() const;

    virtual void ApplyInstance() const;
    virtual void ResetInstance();

    virtual bool Launch( const MetaProcess&, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ );

    virtual ProcessImplementation* NewProcess() const;

    virtual bool ValidateProcess( const ProcessImplementation&, pcl::String& whyNot ) const;
    virtual bool RequiresInstanceValidation() const;

    virtual bool ImportProcess( const ProcessImplementation& );

    virtual void SaveSettings() const;

    // -------------------------------------------------------------------------
		
  private:
		
    ExposeImageInstance instance;
		
    // -------------------------------------------------------------------------
    
	
    struct GUIData
    {
      GUIData( ExposeImageInterface& );

      VerticalSizer  Global_Sizer;
		SectionBar        Camera_SectionBar;
			Control           Camera_Control;
			VerticalSizer	  CameraControl_Sizer;
			HorizontalSizer   Camera_Sizer;
				Label			  Camera_Label;
				Edit			  ActiveCamera_Edit;
				ToolButton		  ChooseCamera_ToolButton;
				PushButton		  CameraConnection_PushButton;
			HorizontalSizer   Temperature_Sizer;
				Label			  Temperature_Label;
				Label			  CurrentTemperatureReading_Label;
				PushButton		  SetTemperature_PushButton;
			HorizontalSizer   FilterWheel_Sizer;
				Label			  FilterWheel_Label;
				Edit			  FilterWheel_Edit;
				ToolButton		  FilterWheel_ToolButton;
				PushButton		  FilterWheelConnection_PushButton;

		SectionBar        Exposure_SectionBar;
			Control ExposureSection_Control;
			VerticalSizer	ExposureSection_Sizer;
			HorizontalSizer Binning_Sizer;
				Label		  BinMode_Label;
				ComboBox	  BinMode_ComboBox;
			HorizontalSizer Filter_Sizer;
				Label		  Filter_Label;
				ComboBox	  Filter_ComboBox;
			HorizontalSizer NumberOfExposures_Sizer;
				Label		  NumberOfExposures_Label;
				SpinBox		  NumberOfExposures_SpinBox;
			HorizontalSizer ExposureDuration_Sizer;
				//Label		   ExposureDuration_Label;
				NumericControl ExposureDuration_NumericControl;
			HorizontalSizer SubFrame_Sizer;
				Label		  SubFrame_Label;
				Label		  X1_Label;
				Edit		  X1_Edit;
				Label		  Y1_Label;
				Edit		  Y1_Edit;
				Label		  X2_Label;
				Edit		  X2_Edit;
				Label		  Y2_Label;
				Edit		  Y2_Edit;
				ToolButton	  SelectSubFrame_ToolButton;
			HorizontalSizer Delay_Sizer;
				Label		  DelayBetweenExposures_Label;
				NumericEdit	  DelayBetweenExposures_NumericEdit;
		
		SectionBar        FileOutput_SectionBar;
			Control FileOutputSection_Control;
			VerticalSizer	FileOutputSection_Sizer;
			HorizontalSizer FileOutputPath_Sizer;
				Label		  FileOutputPath_Label;
				Edit		  FileOutputPath_Edit;
				ToolButton	  FileOutputPath_ToolButton;
			HorizontalSizer FileOutputPattern_Sizer;
				Label		  FileOutputPattern_Label;
				Edit		  FileOutputPattern_Edit;
				ToolButton	  FileOutputPattern_ToolButton;

    };

    GUIData* GUI;
    bool cameraConnected;
    // Interface Updates

    void UpdateControls();

    //void UpdateCameraList( size_type );
    void UpdateCameraList( );
    void __ToggleSection( SectionBar& sender, Control& section, bool start );
    void __CameraConnectionButton_Click( Button& sender, bool checked );

    friend struct GUIData;
    friend class CameraConnectionThread;
  };

  // ----------------------------------------------------------------------------

  PCL_BEGIN_LOCAL
    extern ExposeImageInterface* TheExposeImageInterface;
  PCL_END_LOCAL

    // ----------------------------------------------------------------------------

    } // pcl

#endif   // __ExposeImageInterface_h

// ****************************************************************************
// EOF ExposeImageInterface.h - Released 2010/12/14 09:34:27 UTC
