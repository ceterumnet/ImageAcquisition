#ifndef __ImageAcquisitionInstance_h
#define __ImageAcquisitionInstance_h

#include <pcl/ProcessImplementation.h>
#include <pcl/MetaParameter.h> // for pcl_enum
#include <pcl/Array.h>

namespace pcl
{

// ----------------------------------------------------------------------------
// ImageAcquisitionInstance
// ----------------------------------------------------------------------------

class ImageAcquisitionInstance : public ProcessImplementation
{
public:

   ImageAcquisitionInstance( const MetaProcess* );
   ImageAcquisitionInstance( const ImageAcquisitionInstance& );

   virtual void Assign( const ProcessImplementation& );

   virtual bool CanExecuteOn( const View&, pcl::String& whyNot ) const;
   virtual bool ExecuteOn( View& );

   virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/ );
   virtual bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow );
   virtual size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const;

private:

   String   mapId;      // defect map view identifier
   pcl_enum operation;  // convolution or morphological operation
   pcl_enum structure;  // kind of structural element

   friend class DefectMapProcess;
   friend class DefectMapInterface;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ImageAcquisitionInstance_h

