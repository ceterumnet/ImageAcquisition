#ifndef __ExposeImageParameters_h
#define __ExposeImageParameters_h

#include <pcl/MetaParameter.h>

namespace pcl
{

	PCL_BEGIN_LOCAL

    class EIExposureDuration : public MetaInt16
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
        //virtual String DefaultValue();
    };

    class EIFileOutputPattern : public MetaString
    {
    public:
        EIFileOutputPattern( MetaProcess *);

        virtual IsoString Id() const;
        //virtual String DefaultValue();
    };

	//class EIOnError : public MetaEnumeration
	//{
	//public:

	//	enum { Continue,
	//		Abort,
	//		AskUser,
	//		NumberOfErrorPolicies,
	//		Default = Continue };

	//	EIOnError( MetaProcess* );

	//	virtual IsoString Id() const;
	//	virtual size_type NumberOfElements() const;
	//	virtual IsoString ElementId( size_type ) const;
	//	virtual int ElementValue( size_type ) const;
	//	virtual size_type DefaultValueIndex() const;
	//};
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
