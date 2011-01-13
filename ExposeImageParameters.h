
#ifndef __ExposeImageParameters_h
#define __ExposeImageParameters_h

#include <pcl/MetaParameter.h>

namespace pcl
{

	PCL_BEGIN_LOCAL

		// ----------------------------------------------------------------------------

	class EIExposureCount : public MetaInt16
	{
	public:

		EIExposureCount ( MetaProcess* );

		virtual IsoString Id() const;
		virtual double DefaultValue() const;
	};

	extern EIExposureCount* TheEIExposureCountParameter;


	class EIOnError : public MetaEnumeration
	{
	public:

		enum { Continue,
			Abort,
			AskUser,
			NumberOfErrorPolicies,
			Default = Continue };

		EIOnError( MetaProcess* );

		virtual IsoString Id() const;
		virtual size_type NumberOfElements() const;
		virtual IsoString ElementId( size_type ) const;
		virtual int ElementValue( size_type ) const;
		virtual size_type DefaultValueIndex() const;
	};

	extern EIOnError* TheEIOnErrorParameter;

	// ----------------------------------------------------------------------------

	PCL_END_LOCAL

} // pcl

#endif   // __ExposeImageParameters_h
