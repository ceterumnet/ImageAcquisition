// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
