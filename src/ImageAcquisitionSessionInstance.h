// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __ImageAcquisitionSessionInstance_h
#define __ImageAcquisitionSessionInstance_h
#include <pcl/MetaProcess.h>
#include <pcl/ProcessImplementation.h>
namespace pcl
{

    class ImageAcquisitionSessionInstance : public ProcessImplementation
    {
    public:

        ImageAcquisitionSessionInstance( const MetaProcess* );
        ImageAcquisitionSessionInstance( const ImageAcquisitionSessionInstance& );

        virtual void Assign( const ProcessImplementation& );

        virtual bool CanExecuteOn( const View&, String& whyNot ) const;
        virtual bool IsHistoryUpdater( const View& v ) const;

        virtual bool CanExecuteGlobal( String& whyNot ) const;
        virtual bool ExecuteGlobal();

        virtual void* LockParameter( const MetaParameter*, size_type /*tableRow*/);
        virtual bool AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow );
        virtual size_type ParameterLength( const MetaParameter* p, size_type tableRow ) const;
    private:
    };

}
;

#endif
