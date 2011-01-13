#include "ExposeImageParameters.h"


namespace pcl
{
	EIExposureCount* TheEIExposureCountParameter = 0;
	EIOnError* TheEIOnErrorParameter = 0;

	EIExposureCount::EIExposureCount( MetaProcess* P) : MetaInt16( P )
	{
		TheEIExposureCountParameter = this;
	}

	IsoString EIExposureCount::Id() const
	{
		return "exposureCount";
	}

	double EIExposureCount::DefaultValue() const
	{
		return 1;
	}

	EIOnError::EIOnError( MetaProcess* P) : MetaEnumeration( P )
	{
		TheEIOnErrorParameter = this;
	}

	IsoString EIOnError::Id() const
	{
		return "onError";
	}

	size_type EIOnError::NumberOfElements() const
	{
		return NumberOfErrorPolicies;
	}

	IsoString EIOnError::ElementId( size_type i ) const
	{
		switch ( i )
		{
		default:
		case Continue: return "Continue";
		case Abort:    return "Abort";
		case AskUser:  return "AskUser";
		}
	}

	int EIOnError::ElementValue( size_type i ) const
	{
		return int( i );
	}

	size_type EIOnError::DefaultValueIndex() const
	{
		return size_type( Default );
	}

}