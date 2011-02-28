/*
 * ImageAcquisitionSessionInstance.cpp
 *
 *  Created on: Feb 28, 2011
 *      Author: draphael
 */

#include "ImageAcquisitionSessionInstance.h"

namespace pcl
{

    ImageAcquisitionSessionInstance::ImageAcquisitionSessionInstance( const MetaProcess* m) :
    ProcessImplementation( m )
  {
  }

    ImageAcquisitionSessionInstance::ImageAcquisitionSessionInstance( const ImageAcquisitionSessionInstance& x ) :
    ProcessImplementation( x )
  {
    Assign( x );
  }

  void ImageAcquisitionSessionInstance::Assign( const ProcessImplementation& p )
  {
    const ImageAcquisitionSessionInstance* x = dynamic_cast<const ImageAcquisitionSessionInstance*>( &p );
  }

  bool ImageAcquisitionSessionInstance::IsHistoryUpdater( const View& view ) const
  {
    return false;
  }

  bool ImageAcquisitionSessionInstance::CanExecuteOn( const View& view, String& whyNot ) const
  {
    whyNot = "ImageAcquisitionSessionInstance can only be executed in the global context.";
    return false;
  }

  bool ImageAcquisitionSessionInstance::CanExecuteGlobal(String &whyNot) const
  {
    return true;
  }

  bool ImageAcquisitionSessionInstance::ExecuteGlobal()
  {
    return false;
  }

  void* ImageAcquisitionSessionInstance::LockParameter( const MetaParameter* p, size_type tableRow )
  {
      return 0;
  }


  bool ImageAcquisitionSessionInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
  {
      return true;
  }

  size_type ImageAcquisitionSessionInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
  {
    return 0;
  }
}

