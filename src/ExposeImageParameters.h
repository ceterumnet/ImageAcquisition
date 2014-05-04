// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions;
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License.
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#ifndef __ExposeImageParameters_h
#define __ExposeImageParameters_h

#include <pcl/MetaParameter.h>

namespace pcl
{

    PCL_BEGIN_LOCAL

        class EIExposureDuration : public MetaDouble
    {
    public:
        EIExposureDuration ( MetaProcess* );

        virtual IsoString Id() const;
        virtual double DefaultValue() const;
    };

    class EIExposureCount : public MetaInt16
    {
    public:
        EIExposureCount ( MetaProcess* );

        virtual IsoString Id() const;
        virtual double DefaultValue() const;
    };

    class EICameraName : public MetaString
    {
    public:
        EICameraName( MetaProcess *);

        virtual IsoString Id() const;
    };

    class EISetTemperature : public MetaDouble
    {
    public:
        EISetTemperature( MetaProcess* );

        virtual IsoString Id() const;
        virtual double DefaultValue() const;
    };

    class EIFilterWheelName : public MetaString
    {
    public:
        EIFilterWheelName( MetaProcess* );

        virtual IsoString Id() const;
        //virtual String DefaultValue() const;
    };
    //    Not sure I I want this to be index based or string based...in case I rearrange my filters,
    //    I would like the scripts to be portable
    class EIFilter: public MetaString
    {
    public:
        EIFilter( MetaProcess * );

        virtual IsoString Id() const;
        //virtual String DefaultValue() const;
    };

    class EIBinModeX : public MetaInt8
    {
    public:
        EIBinModeX( MetaProcess *);

        virtual IsoString Id() const;
        virtual int8 DefaultValue();
    };

    class EIBinModeY : public MetaInt8
    {
    public:
        EIBinModeY( MetaProcess *);

        virtual IsoString Id() const;
        virtual int8 DefaultValue();
    };


    class EISubFrameX1 : public MetaInt16
    {
    public:
        EISubFrameX1( MetaProcess * );

        virtual IsoString Id() const;
        virtual int16 DefaultValue();
    };

    class EISubFrameY1 : public MetaInt16
    {
    public:
        EISubFrameY1( MetaProcess * );

        virtual IsoString Id() const;
        virtual int16 DefaultValue();
    };

    class EISubFrameX2 : public MetaInt16
    {
    public:
        EISubFrameX2( MetaProcess * );

        virtual IsoString Id() const;
        virtual int16 DefaultValue();
    };

    class EISubFrameY2 : public MetaInt16
    {
    public:
        EISubFrameY2( MetaProcess * );

        virtual IsoString Id() const;
        virtual int16 DefaultValue();
    };

    class EIDelayBetweenExposures : public MetaFloat
    {
    public:
        EIDelayBetweenExposures( MetaProcess *);

        virtual IsoString Id() const;
        virtual float DefaultValue();
    };

    class EIFileOutputPath : public MetaString
    {
    public:
        EIFileOutputPath( MetaProcess *);

        virtual IsoString Id() const;
    };

    class EIFileOutputPattern : public MetaString
    {
    public:
        EIFileOutputPattern( MetaProcess *);

        virtual IsoString Id() const;
    };

    extern EIExposureDuration* TheExposureDurationParameter;
    extern EIExposureCount* TheExposureCountParameter;
    extern EICameraName* TheCameraNameParameter;
    extern EIFilterWheelName* TheFilterWheelNameParameter;
    extern EISetTemperature* TheSetTemperatureParameter;
    extern EIFilter* TheFilterParameter;
    extern EIBinModeX* TheBinModeXParameter;
    extern EIBinModeY* TheBinModeYParameter;
    extern EISubFrameX1* TheSubFrameX1Parameter;
    extern EISubFrameY1* TheSubFrameY1Parameter;
    extern EISubFrameX2* TheSubFrameX2Parameter;
    extern EISubFrameY2* TheSubFrameY2Parameter;
    extern EIDelayBetweenExposures* TheDelayBetweenExposuresParameter;
    extern EIFileOutputPath* TheFileOutputPathParameter;
    extern EIFileOutputPattern* TheFileOutputPatternParameter;
    //    extern EIOnError* TheEIOnErrorParameter;

    // ----------------------------------------------------------------------------

    PCL_END_LOCAL

        } // pcl

#endif   // __ExposeImageParameters_h
