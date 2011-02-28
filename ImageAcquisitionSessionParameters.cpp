#include "ImageAcquisitionSessionParameters.h"

namespace pcl
{
    IASSerializedProcesses *TheIASSerializedProcessesParameter = 0;
    IASSerializedProcessName *TheIASSerializedProcessNameParameter = 0;

    IASSerializedProcesses::IASSerializedProcesses( MetaProcess *P ) : MetaTable( P )
    {
        TheIASSerializedProcessesParameter = this;
    }

    IsoString IASSerializedProcesses::Id( ) const
    {
        return "serializedProcesses";
    }

    IASSerializedProcessName::IASSerializedProcessName( MetaTable *T ) : MetaString( T )
    {
        TheIASSerializedProcessNameParameter = this;
    }

    IsoString IASSerializedProcessName::Id() const
    {
        return "serializedProcessName";
    }

    IASSerializedProcessData::IASSerializedProcessData( MetaTable *T ) : MetaBlock( T )
    {
        TheIASSerializedProcessDataParameter = this;
    }

    IsoString IASSerializedProcessData::Id() const
    {
        return "serializedProcessData";
    }

}
