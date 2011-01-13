
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

#include "ExposeImageInstance.h"

namespace pcl
{

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
			HorizontalSizer   Camera_Sizer;
				Label			  Camera_Label;
				ComboBox          Camera_ComboBox;

		};

		GUIData* GUI;

		// Interface Updates

		void UpdateControls();

		//void UpdateCameraList( size_type );
		void UpdateCameraList( );
		void ExposeImageInterface::__ToggleSection( SectionBar& sender, Control& section, bool start );
		friend struct GUIData;
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
