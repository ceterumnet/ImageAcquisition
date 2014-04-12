// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


#include "ExposeImageParameters.h"


namespace pcl
{
	EIExposureDuration* TheExposureDurationParameter = 0;
    EIExposureCount* TheExposureCountParameter = 0;
    EICameraName* TheCameraNameParameter = 0;
    EIFilterWheelName* TheFilterWheelNameParameter = 0;
    EISetTemperature* TheSetTemperatureParameter = 0;
    EIFilter* TheFilterParameter = 0;
    EIBinModeX* TheBinModeXParameter = 0;
    EIBinModeY* TheBinModeYParameter = 0;
    EISubFrameX1* TheSubFrameX1Parameter = 0;
    EISubFrameY1* TheSubFrameY1Parameter = 0;
    EISubFrameX2* TheSubFrameX2Parameter = 0;
    EISubFrameY2* TheSubFrameY2Parameter = 0;
    EIDelayBetweenExposures* TheDelayBetweenExposuresParameter = 0;
    EIFileOutputPath* TheFileOutputPathParameter = 0;
    EIFileOutputPattern* TheFileOutputPatternParameter = 0;
	//EIOnError* TheEIOnErrorParameter = 0;

	EIExposureDuration::EIExposureDuration( MetaProcess* P) : MetaDouble( P )
	{
	    TheExposureDurationParameter = this;
	}

	IsoString EIExposureDuration::Id() const
	{
	    return "exposureDuration";
	}

	double EIExposureDuration::DefaultValue() const
    {
        return 1000;
    }

	EIExposureCount::EIExposureCount( MetaProcess* P) : MetaInt16( P )
	{
		TheExposureCountParameter = this;
	}

	IsoString EIExposureCount::Id() const
	{
		return "exposureCount";
	}

	double EIExposureCount::DefaultValue() const
	{
		return 1;
	}

	EICameraName::EICameraName( MetaProcess* P) : MetaString( P )
	{
	    TheCameraNameParameter = this;
	}

	IsoString EICameraName::Id() const
	{
	    return "cameraName";
	}

	EIFilterWheelName::EIFilterWheelName( MetaProcess *P ) : MetaString( P )
	{
	    TheFilterWheelNameParameter = this;
	}

	IsoString EIFilterWheelName::Id() const
	{
	    return "filterWheelName";
	}

    EIFilter::EIFilter( MetaProcess *P ) : MetaString( P )
    {
        TheFilterParameter = this;
    }

    IsoString EIFilter::Id() const
    {
        return "filter";
    }

	EISetTemperature::EISetTemperature( MetaProcess* P ) : MetaDouble( P )
	{
	    TheSetTemperatureParameter = this;
	}

	IsoString EISetTemperature::Id() const
	{
	    return "setTemperature";
	}

	double EISetTemperature::DefaultValue() const
	{
	    return -15;
	}

	EIBinModeX::EIBinModeX( MetaProcess *P ) : MetaInt8( P )
	{
	    TheBinModeXParameter = this;
	}

	IsoString EIBinModeX::Id() const
	{
	    return "binModeX";
	}

	int8 EIBinModeX::DefaultValue()
	{
	    return 1;
	}

    EIBinModeY::EIBinModeY( MetaProcess *P ) : MetaInt8( P )
    {
        TheBinModeYParameter = this;
    }

    IsoString EIBinModeY::Id() const
    {
        return "binModeY";
    }

    int8 EIBinModeY::DefaultValue()
    {
        return 1;
    }

    EISubFrameX1::EISubFrameX1( MetaProcess *P ) : MetaInt16( P )
    {
        TheSubFrameX1Parameter = this;
    }

    IsoString EISubFrameX1::Id() const
    {
        return "subFrameX1";
    }

    int16 EISubFrameX1::DefaultValue()
    {
        return 0;
    }


    EISubFrameY1::EISubFrameY1( MetaProcess *P ) : MetaInt16( P )
    {
        TheSubFrameY1Parameter = this;
    }

    IsoString EISubFrameY1::Id() const
    {
        return "subFrameY1";
    }

    int16 EISubFrameY1::DefaultValue()
    {
        return 0;
    }


    EISubFrameX2::EISubFrameX2( MetaProcess *P ) : MetaInt16( P )
    {
        TheSubFrameX2Parameter = this;
    }

    IsoString EISubFrameX2::Id() const
    {
        return "subFrameX2";
    }

    int16 EISubFrameX2::DefaultValue()
    {
        return 0;
    }


    EISubFrameY2::EISubFrameY2( MetaProcess *P ) : MetaInt16( P )
    {
        TheSubFrameY2Parameter = this;
    }

    IsoString EISubFrameY2::Id() const
    {
        return "subFrameY2";
    }

    int16 EISubFrameY2::DefaultValue()
    {
        return 0;
    }

    EIDelayBetweenExposures::EIDelayBetweenExposures( MetaProcess *P ) : MetaFloat( P )
    {
        TheDelayBetweenExposuresParameter = this;
    }

    IsoString EIDelayBetweenExposures::Id() const
    {
        return "delayBetweenExposures";
    }

    float EIDelayBetweenExposures::DefaultValue()
    {
        return 1;
    }

    EIFileOutputPath::EIFileOutputPath( MetaProcess *P ) : MetaString( P )
    {
        TheFileOutputPathParameter = this;
    }

    IsoString EIFileOutputPath::Id() const
    {
        return "fileOutputPath";
    }

    EIFileOutputPattern::EIFileOutputPattern( MetaProcess *P ) : MetaString( P )
    {
        TheFileOutputPatternParameter = this;
    }

    IsoString EIFileOutputPattern::Id() const
    {
        return "fileOutputPattern";
    }

	//EIOnError::EIOnError( MetaProcess* P) : MetaEnumeration( P )
	//{
	//	TheEIOnErrorParameter = this;
	//}

	//IsoString EIOnError::Id() const
	//{
	//	return "onError";
	//}

	//size_type EIOnError::NumberOfElements() const
	//{
	//	return NumberOfErrorPolicies;
	//}

	//IsoString EIOnError::ElementId( size_type i ) const
	//{
	//	switch ( i )
	//	{
	//	default:
	//	case Continue: return "Continue";
	//	case Abort:    return "Abort";
	//	case AskUser:  return "AskUser";
	//	}
	//}

	//int EIOnError::ElementValue( size_type i ) const
	//{
	//	return int( i );
	//}

	//size_type EIOnError::DefaultValueIndex() const
	//{
	//	return size_type( Default );
	//}



}
