// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __ImageAcquisitionSettingsInterface_h
#define __ImageAcquisitionSettingsInterface_h

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
#include <pcl/TabBox.h>

#include "CameraDialog.h"
#include "ImageAcquisitionSettingsInstance.h"
#include "IPixInsightCamera.h"
#include "CameraItem.h"

namespace pcl
{

	// ----------------------------------------------------------------------------
	class ImageAcquisitionSettingsInterface : public ProcessInterface
	{
	public:

		ImageAcquisitionSettingsInterface();
		virtual ~ImageAcquisitionSettingsInterface();
		
		virtual IsoString Id() const;
		virtual uint32 Version() const;
		virtual const char** IconImageXPM() const;
		
		InterfaceFeatures Features() const;
		
		virtual void ApplyInstance() const;
		virtual void ResetInstance();
		
		virtual bool Launch( const MetaProcess&, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ );
		
		virtual ProcessImplementation* NewProcess() const;
		virtual MetaProcess* Process() const;
		virtual bool ValidateProcess( const ProcessImplementation&, pcl::String& whyNot ) const;
		virtual bool RequiresInstanceValidation() const;

		virtual bool ImportProcess( const ProcessImplementation& );
		void TestImage();
		// -------------------------------------------------------------------------
		
		CameraItem *GetPrimaryImager();
	private:
        ImageAcquisitionSettingsInstance instance;
		
		struct GUIData
		{
			GUIData( ImageAcquisitionSettingsInterface& );

			VerticalSizer  Global_Sizer;
			TabBox	ImageAcquisitionSettings_TabBox;
			    // Camera Tab
				Control CameraSelection_Control;
				HorizontalSizer CameraSelection_Sizer;
					TreeBox CameraList_TreeBox;
					VerticalSizer CameraListButtons_Sizer;
						PushButton AddCamera_PushButton;
						PushButton EditCamera_PushButton;
						PushButton DeleteCamera_PushButton;
						PushButton MakePrimary_PushButton;
						PushButton MakeGuider_PushButton;
				// Filter Wheel Tab
                Control FWSelection_Control;
                HorizontalSizer FWSelection_Sizer;
                    TreeBox FWList_TreeBox;
                    VerticalSizer FWListButtons_Sizer;
                        PushButton AddFW_PushButton;
                        PushButton DeleteFW_PushButton;
                        PushButton MakeFW_PushButton;
                // Load and Save settings
                HorizontalSizer LoadSaveSettings_Sizer;
                    PushButton SaveSettings_PushButton;
                    PushButton LoadSettings_PushButton;

			CameraDialog CamDlg;
		};

		GUIData* GUI;
		
		// Interface Updates

		void UpdateControls();
		void UpdateCameraList();
		void UpdateCameraItem(size_type);
		void AddCamera();

		void __ToggleSection( SectionBar& sender, Control& section, bool start );
		void __CameraListButtons_Click( Button& sender, bool checked );
		void __LoadSaveSettingsButtons_Click( Button& sender, bool checked );
		void __CameraList_CurrentNodeUpdated( TreeBox& sender, TreeBox::Node& current, TreeBox::Node& oldCurrent );
		void __CameraList_NodeActivated( TreeBox& sender, TreeBox::Node& node, int col );
		void __CameraList_NodeSelectionUpdated( TreeBox& sender );
		friend struct GUIData;
		friend class ExposeImageInterface;
		friend class ExposeImageInstance;
		friend class CameraSelectorDialog;

	};

	// ----------------------------------------------------------------------------

	PCL_BEGIN_LOCAL
		extern ImageAcquisitionSettingsInterface* TheImageAcquisitionSettingsInterface;
	PCL_END_LOCAL

		// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionSettingsInterface_h

// ****************************************************************************
// EOF ImageAcquisitionSettingsInterface.h - Released 2010/12/14 09:34:27 UTC
