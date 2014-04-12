// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __ExposeImageInstance_h
#define __ExposeImageInstance_h

#include <pcl/ProcessImplementation.h>
#include <pcl/Console.h>
#include "ImageAcquisitionSettingsInterface.h"
#include "ExposeImageParameters.h"
#include <pcl/Mutex.h>
#include <pcl/FileFormat.h>
#include <pcl/FileFormatInstance.h>
namespace pcl
{

class FileFormatInstance;

class ExposeImageThread;



class ExposeImageInstance : public ProcessImplementation
{
public:

   ExposeImageInstance( const MetaProcess* );
   ExposeImageInstance( const ExposeImageInstance& );

   virtual void Assign( const ProcessImplementation& );

   virtual bool CanExecuteOn( const View&, String& whyNot ) const;
   virtual bool IsHistoryUpdater( const View& v ) const;

   virtual bool CanExecuteGlobal( String& whyNot ) const;
   virtual bool ExecuteGlobal();
   bool ExposeImages();
   bool ExposeImagesWithCCD();
   bool ExposeImagesWithDSLR();
   virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/ );
   virtual bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow );
   virtual size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const;
   void SerializeParameters( ByteArray &bArray );
private:
	//do I need to use a safer type?
	double exposureDuration; //seconds
	int16 exposureCount;
	String cameraName;
	String filterWheelName;
	double setTemperature;
	String filter;
	int8 binModeX;
	int8 binModeY;
	int16 subFrameX1;
	int16 subFrameY1;
	int16 subFrameX2;
	int16 subFrameY2;
	float delayBetweenExposures;
	String fileOutputPath;
	String fileOutputPattern;
	pcl_enum onError;
	ExposeImageThread *exposeThread;

   // Expose an Image
	//Image* ExposeImage( ... const ExposeImageThread& );
	//void WriteExposedImage( const ExposeImageThread* );
	//void WriteExposedImage( const ExposeImageThread* );
   
   friend class ExposeImageThread;
   friend class ExposeImageInterface;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ExposeImageInstance_h

// ****************************************************************************
// EOF ExposeImageInstance.h - Released 2010/12/14 09:34:27 UTC
