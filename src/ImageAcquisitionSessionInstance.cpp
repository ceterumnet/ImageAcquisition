// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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

