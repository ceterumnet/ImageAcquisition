// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#include "ImageAcquisitionSessionParameters.h"

namespace pcl
{
    IASSerializedProcesses *TheIASSerializedProcessesParameter = 0;
    IASSerializedProcessName *TheIASSerializedProcessNameParameter = 0;
    IASSerializedProcessData *TheIASSerializedProcessDataParameter = 0;

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
