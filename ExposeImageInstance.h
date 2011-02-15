#ifndef __ExposeImageInstance_h
#define __ExposeImageInstance_h

#include <pcl/ProcessImplementation.h>

#include "ExposeImageParameters.h"

namespace pcl
{

class FileFormatInstance;

class ExposeImageThread;
class ExposeImageThreadData;

typedef IndirectArray<ExposeImageThread>  thread_list;

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

   virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/ );
   virtual bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow );
   
private:
	//do I need to use a safer type?
	int16 exposureDuration; //milliseconds
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

	//int16 filterIndex; // starting at 0
	//This might need to be more dynamic...tbd
	//pcl_enum binningMode; // 1x1, 2x2, 3x3, 4x4
	//pcl_enum imageType; // light | dark | bias | flat

   // Output files
   //String          outputDirectory;
   //String          outputExtension;
   //String          outputPrefix;
   //String          outputPostfix;
   //pcl_enum        outputSampleFormat;

   // -------------------------------------------------------------------------


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
