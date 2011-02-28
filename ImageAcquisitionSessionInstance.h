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
