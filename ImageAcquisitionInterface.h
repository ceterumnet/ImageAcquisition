
#ifndef __ImageAcquisitionInterface_h
#define __ImageAcquisitionInterface_h

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

#include "ImageAcquisitionInstance.h"

namespace pcl
{

// ----------------------------------------------------------------------------

class ImageAcquisitionInterface : public ProcessInterface
{
public:

   ImageAcquisitionInterface();
   virtual ~ImageAcquisitionInterface();

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

	ImageAcquisitionInstance instance;

   // -------------------------------------------------------------------------

   struct GUIData
   {
      GUIData( ImageAcquisitionInterface& );

      VerticalSizer  Global_Sizer;

      SectionBar        TargetImages_SectionBar;
      Control           TargetImages_Control;
      HorizontalSizer   TargetImages_Sizer;
         TreeBox           TargetImages_TreeBox;
         VerticalSizer     TargetButtons_Sizer;
            PushButton        AddFiles_PushButton;
            PushButton        SelectAll_PushButton;
            PushButton        InvertSelection_PushButton;
            PushButton        ToggleSelected_PushButton;
            PushButton        RemoveSelected_PushButton;
            PushButton        Clear_PushButton;
            CheckBox          FullPaths_CheckBox;

      SectionBar        OutputFiles_SectionBar;
      Control           OutputFiles_Control;
      VerticalSizer     OutputFiles_Sizer;
         HorizontalSizer   OutputDirectory_Sizer;
            Label             OutputDirectory_Label;
            Edit              OutputDirectory_Edit;
            ToolButton        OutputDirectory_ToolButton;
         HorizontalSizer   OutputChunks_Sizer;
            Label             OutputExtension_Label;
            Edit              OutputExtension_Edit;
            Label             OutputPrefix_Label;
            Edit              OutputPrefix_Edit;
            Label             OutputPostfix_Label;
            Edit              OutputPostfix_Edit;
         HorizontalSizer   OutputSampleFormat_Sizer;
            Label             OutputSampleFormat_Label;
            ComboBox          OutputSampleFormat_ComboBox;
         HorizontalSizer   OutputPedestal_Sizer;
            Label             OutputPedestal_Label;
            SpinBox           OutputPedestal_SpinBox;
         HorizontalSizer   OutputOptions_Sizer;
            CheckBox          OverwriteExistingFiles_CheckBox;
            Label             OnError_Label;
            ComboBox          OnError_ComboBox;

      SectionBar        Pedestal_SectionBar;
      Control           Pedestal_Control;
      VerticalSizer     Pedestal_Sizer;
         HorizontalSizer   PedestalMode_Sizer;
            Label             PedestalMode_Label;
            ComboBox          PedestalMode_ComboBox;
         HorizontalSizer   PedestalValue_Sizer;
            Label             PedestalValue_Label;
            SpinBox           PedestalValue_SpinBox;
         HorizontalSizer   PedestalKeyword_Sizer;
            Label             PedestalKeyword_Label;
            Edit              PedestalKeyword_Edit;

      SectionBar        Overscan_SectionBar;
      Control           Overscan_Control;
      VerticalSizer     Overscan_Sizer;
         HorizontalSizer   ImageRegion_Sizer;
            Label             ImageRegion_Label;
            NumericEdit          ImageRegionX0_NumericEdit;
            NumericEdit          ImageRegionY0_NumericEdit;
            NumericEdit          ImageRegionWidth_NumericEdit;
            NumericEdit          ImageRegionHeight_NumericEdit;
         HorizontalSizer   Overscan1_Sizer;
            CheckBox          Overscan1_CheckBox;
         HorizontalSizer   Overscan1Source_Sizer;
            Label             Overscan1Source_Label;
            NumericEdit          Overscan1SourceX0_NumericEdit;
            NumericEdit          Overscan1SourceY0_NumericEdit;
            NumericEdit          Overscan1SourceWidth_NumericEdit;
            NumericEdit          Overscan1SourceHeight_NumericEdit;
         HorizontalSizer   Overscan1Target_Sizer;
            Label             Overscan1Target_Label;
            NumericEdit          Overscan1TargetX0_NumericEdit;
            NumericEdit          Overscan1TargetY0_NumericEdit;
            NumericEdit          Overscan1TargetWidth_NumericEdit;
            NumericEdit          Overscan1TargetHeight_NumericEdit;
         HorizontalSizer   Overscan2_Sizer;
            CheckBox          Overscan2_CheckBox;
         HorizontalSizer   Overscan2Source_Sizer;
            Label             Overscan2Source_Label;
            NumericEdit          Overscan2SourceX0_NumericEdit;
            NumericEdit          Overscan2SourceY0_NumericEdit;
            NumericEdit          Overscan2SourceWidth_NumericEdit;
            NumericEdit          Overscan2SourceHeight_NumericEdit;
         HorizontalSizer   Overscan2Target_Sizer;
            Label             Overscan2Target_Label;
            NumericEdit          Overscan2TargetX0_NumericEdit;
            NumericEdit          Overscan2TargetY0_NumericEdit;
            NumericEdit          Overscan2TargetWidth_NumericEdit;
            NumericEdit          Overscan2TargetHeight_NumericEdit;
         HorizontalSizer   Overscan3_Sizer;
            CheckBox          Overscan3_CheckBox;
         HorizontalSizer   Overscan3Source_Sizer;
            Label             Overscan3Source_Label;
            NumericEdit          Overscan3SourceX0_NumericEdit;
            NumericEdit          Overscan3SourceY0_NumericEdit;
            NumericEdit          Overscan3SourceWidth_NumericEdit;
            NumericEdit          Overscan3SourceHeight_NumericEdit;
         HorizontalSizer   Overscan3Target_Sizer;
            Label             Overscan3Target_Label;
            NumericEdit          Overscan3TargetX0_NumericEdit;
            NumericEdit          Overscan3TargetY0_NumericEdit;
            NumericEdit          Overscan3TargetWidth_NumericEdit;
            NumericEdit          Overscan3TargetHeight_NumericEdit;
         HorizontalSizer   Overscan4_Sizer;
            CheckBox          Overscan4_CheckBox;
         HorizontalSizer   Overscan4Source_Sizer;
            Label             Overscan4Source_Label;
            NumericEdit          Overscan4SourceX0_NumericEdit;
            NumericEdit          Overscan4SourceY0_NumericEdit;
            NumericEdit          Overscan4SourceWidth_NumericEdit;
            NumericEdit          Overscan4SourceHeight_NumericEdit;
         HorizontalSizer   Overscan4Target_Sizer;
            Label             Overscan4Target_Label;
            NumericEdit          Overscan4TargetX0_NumericEdit;
            NumericEdit          Overscan4TargetY0_NumericEdit;
            NumericEdit          Overscan4TargetWidth_NumericEdit;
            NumericEdit          Overscan4TargetHeight_NumericEdit;

      SectionBar        MasterBias_SectionBar;
      Control           MasterBias_Control;
      VerticalSizer     MasterBias_Sizer;
         HorizontalSizer   MasterBiasPath_Sizer;
            Edit              MasterBiasPath_Edit;
            ToolButton        MasterBiasPath_ToolButton;
         HorizontalSizer   CalibrateMasterBias_Sizer;
            CheckBox          CalibrateMasterBias_CheckBox;

      SectionBar        MasterDark_SectionBar;
      Control           MasterDark_Control;
      VerticalSizer     MasterDark_Sizer;
         HorizontalSizer   MasterDarkPath_Sizer;
            Edit              MasterDarkPath_Edit;
            ToolButton        MasterDarkPath_ToolButton;
         HorizontalSizer   CalibrateMasterDark_Sizer;
            CheckBox          CalibrateMasterDark_CheckBox;
         HorizontalSizer   OptimizeDarks_Sizer;
            CheckBox          OptimizeDarks_CheckBox;
         HorizontalSizer   DarkOptimizationWindow_Sizer;
            Label             DarkOptimizationWindow_Label;
            SpinBox           DarkOptimizationWindow_SpinBox;
         HorizontalSizer   DarkCFADetectionMode_Sizer;
            Label             DarkCFADetectionMode_Label;
            ComboBox          DarkCFADetectionMode_ComboBox;

      SectionBar        MasterFlat_SectionBar;
      Control           MasterFlat_Control;
      VerticalSizer     MasterFlat_Sizer;
         HorizontalSizer   MasterFlatPath_Sizer;
            Edit              MasterFlatPath_Edit;
            ToolButton        MasterFlatPath_ToolButton;
         HorizontalSizer   CalibrateMasterFlat_Sizer;
            CheckBox          CalibrateMasterFlat_CheckBox;
   };

   GUIData* GUI;

   // Interface Updates

   void UpdateControls();
   void UpdateTargetImageItem( size_type );
   void UpdateTargetImagesList();
   void UpdateImageSelectionButtons();
   void UpdateOutputFilesControls();
   void UpdatePedestalControls();
   void UpdateMasterFrameControls();
   void UpdateOverscanControls();

   // Event Handlers

   void __TargetImages_CurrentNodeUpdated( TreeBox& sender, TreeBox::Node& current, TreeBox::Node& oldCurrent );
   void __TargetImages_NodeActivated( TreeBox& sender, TreeBox::Node& node, int col );
   void __TargetImages_NodeSelectionUpdated( TreeBox& sender );
   void __TargetImages_Click( Button& sender, bool checked );

   void __OutputFiles_EditCompleted( Edit& sender );
   void __OutputFiles_Click( Button& sender, bool checked );
   void __OutputFiles_ItemSelected( ComboBox& sender, int itemIndex );
   void __OutputFiles_SpinValueUpdated( SpinBox& sender, int value );

   void __Pedestal_SpinValueUpdated( SpinBox& sender, int value );
   void __Pedestal_ItemSelected( ComboBox& sender, int itemIndex );
   void __Pedestal_EditCompleted( Edit& sender );

   void __MasterFrame_EditCompleted( Edit& sender );
   void __MasterFrame_Click( Button& sender, bool checked );
   void __MasterFrame_SpinValueUpdated( SpinBox& sender, int value );
   void __MasterFrame_ItemSelected( ComboBox& sender, int itemIndex );

   void __Overscan_ValueUpdated( NumericEdit& sender, double value );
   void __Overscan_Click( Button& sender, bool checked );

   void __CheckSection( SectionBar& sender, bool checked );
   void __ToggleSection( SectionBar& sender, Control& section, bool start );

   friend struct GUIData;
};

// ----------------------------------------------------------------------------

PCL_BEGIN_LOCAL
extern ImageAcquisitionInterface* TheImageAcquisitionInterface;
PCL_END_LOCAL

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionInterface_h

// ****************************************************************************
// EOF ImageAcquisitionInterface.h - Released 2010/12/14 09:34:27 UTC
