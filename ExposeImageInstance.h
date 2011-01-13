#ifndef __ExposeImageInstance_h
#define __ExposeImageInstance_h

#include <pcl/ProcessImplementation.h>

#include "ExposeImageParameters.h"

namespace pcl
{

// ----------------------------------------------------------------------------

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
   virtual size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const;

   /*
   
   struct SubFrame
   {
	pcl_bool enabled;
	Rect subFrameRect;
	SubFrame() : enabled( false ), subFrameRect( 0 );
   }
	... tbd
   */
  
   
private:

	//do I need to use a safer type?
	int16 exposureDuration; //milliseconds
	int16 exposureCount;
	int16 filterIndex; // starting at 0
	//This might need to be more dynamic...tbd
	pcl_enum binningMode; // 1x1, 2x2, 3x3, 4x4
	pcl_enum imageType; // light | dark | bias | flat

   // Output files
   String          outputDirectory;
   String          outputExtension;
   String          outputPrefix;
   String          outputPostfix;
   pcl_enum        outputSampleFormat;
   pcl_enum        onError;

   // -------------------------------------------------------------------------


   // Expose an Image
	//Image* ExposeImage( ... const ExposeImageThread& );
	//void WriteExposedImage( const ExposeImageThread* );
	//void WriteExposedImage( const ExposeImageThread* );
   
   //friend class ExposeImageThread;
   friend class ExposeImageInterface;
};

// ----------------------------------------------------------------------------

} // pcl

#endif   // __ExposeImageInstance_h

// ****************************************************************************
// EOF ExposeImageInstance.h - Released 2010/12/14 09:34:27 UTC
