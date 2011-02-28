#ifndef __ImageAcquisitionSessionParameters_h
#define __ImageAcquisitionSessionParameters_h
#include <pcl/MetaParameter.h>
namespace pcl
{
    class IASSerializedProcesses: public MetaTable
    {
    public:
        IASSerializedProcesses( MetaProcess* );
        virtual IsoString Id() const;
    };

    extern IASSerializedProcesses* TheIASSerializedProcessesParameter;

    class IASSerializedProcessName : public MetaString
    {
    public:
        IASSerializedProcessName ( MetaTable* );
        virtual IsoString Id() const;
    };
    extern IASSerializedProcessName* TheIASSerializedProcessNameParameter ;

    class IASSerializedProcessData: public MetaBlock
    {
    public:
        IASSerializedProcessData ( MetaTable* );
        virtual IsoString Id() const;
    };
    extern IASSerializedProcessData* TheIASSerializedProcessDataParameter ;


}

#endif
