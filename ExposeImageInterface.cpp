
#include "ExposeImageInterface.h"
#include "ExposeImageProcess.h"

#include <pcl/Dialog.h>
#include <pcl/FileDialog.h>
#include <pcl/ViewList.h>
#include <pcl/GlobalSettings.h>
#include <pcl/ErrorHandler.h>

namespace pcl
{

	// ----------------------------------------------------------------------------

	ExposeImageInterface* TheExposeImageInterface = 0;

	// ----------------------------------------------------------------------------

#include "ExposeImageIcon.xpm"

	// ----------------------------------------------------------------------------

	ExposeImageInterface::ExposeImageInterface() :
	ProcessInterface(), instance( TheExposeImageProcess ), GUI( 0 )
	{
		TheExposeImageInterface = this;

		// The auto save geometry feature is of no good to interfaces that include
		// both auto-expanding controls (e.g. TreeBox) and collapsible sections
		// (e.g. SectionBar).
		// DisableAutoSaveGeometry();
	}

	ExposeImageInterface::~ExposeImageInterface()
	{
		if ( GUI != 0 )
			delete GUI, GUI = 0;
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

	bool ExposeImageInterface::Launch( const MetaProcess& P, const ProcessImplementation*, bool& dynamic, unsigned& /*flags*/ )
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
		//UpdateTargetImagesList();
		//UpdateImageSelectionButtons();
		//UpdateOutputFilesControls();
		//UpdatePedestalControls();
		//UpdateMasterFrameControls();
		//UpdateOverscanControls();
		UpdateCameraList();
		// TODO: add update control method calls...
	}

	//I don't know if this should be an update call or something else...
	void ExposeImageInterface::UpdateCameraList()
	{
		//GUI->Camera_ComboBox.SetToolTip("Select Your Camera Model");
	}

	void ExposeImageInterface::__ToggleSection( SectionBar& sender, Control& section, bool start )	
	{

	}

	// ----------------------------------------------------------------------------
	// ----------------------------------------------------------------------------


	// ----------------------------------------------------------------------------
	// ----------------------------------------------------------------------------

	ExposeImageInterface::GUIData::GUIData( ExposeImageInterface& w )
	{
		Camera_SectionBar.SetTitle( "Camera" );
		Camera_SectionBar.SetSection( Camera_Control );
		Camera_SectionBar.OnToggleSection( (SectionBar::section_event_handler)&ExposeImageInterface::__ToggleSection, w );

		//#ifndef __PCL_MACOSX
		//I guess this is a trick to get MACOSX spacing correct
		//TargetButtons_Sizer.SetSpacing( 4 );
		//#endif
		Camera_Label.SetText("Select Camera:");

		Camera_Sizer.Add(Camera_Label, 0);
		Camera_Sizer.Add(Camera_ComboBox, 0);
		Camera_Sizer.SetSpacing( 4 );

		Camera_Control.SetSizer( Camera_Sizer );
		Camera_Control.AdjustToContents();
		//

		Global_Sizer.SetMargin( 8 );
		Global_Sizer.SetSpacing( 6 );
		Global_Sizer.Add( Camera_SectionBar );
		Global_Sizer.Add( Camera_Control );

		w.SetSizer( Global_Sizer );

		w.SetFixedWidth();

		w.AdjustToContents();
	}

	// ----------------------------------------------------------------------------

} // pcl

// ****************************************************************************
// EOF ExposeImageInterface.cpp - Released 2010/12/14 09:34:27 UTC
