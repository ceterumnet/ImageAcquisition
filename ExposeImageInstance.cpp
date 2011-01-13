#include "ExposeImageInstance.h"

namespace pcl
{

	ExposeImageInstance::ExposeImageInstance( const MetaProcess* m) : 
ProcessImplementation( m ),
outputDirectory(0),
outputExtension(0),
outputPrefix(0),
outputPostfix(0)
{
	
}

ExposeImageInstance::ExposeImageInstance( const ExposeImageInstance& x ) :
ProcessImplementation( x )
{
   Assign( x );
}

void ExposeImageInstance::Assign( const ProcessImplementation& p )
{
	const ExposeImageInstance* x = dynamic_cast<const ExposeImageInstance*>( &p );
	if ( x != 0 )
	{
		outputDirectory = x->outputDirectory;
		outputExtension = x->outputExtension;
		outputPrefix    = x->outputPrefix;
		outputPostfix   = x->outputPostfix;
	}
}

bool ExposeImageInstance::IsHistoryUpdater( const View& view ) const
{
	return false;
}

bool ExposeImageInstance::CanExecuteOn( const View& view, String& whyNot ) const 
{
	whyNot = "ExposeImage can only be executed in the global context.";
	return false;
}

bool ExposeImageInstance::CanExecuteGlobal(String &whyNot) const
{
	return true;
}

bool ExposeImageInstance::ExecuteGlobal() 
{
	return false;
}

void* ExposeImageInstance::LockParameter( const MetaParameter*, size_type /*tableRow*/ )
{
	return 0;
}


bool ExposeImageInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
{
	if ( p == TheEIExposureCountParameter)
	{
		//we need to do something here...
	}
	else
		return false;

	return true;
}
size_type ExposeImageInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
{
	if ( p == TheEIExposureCountParameter )
		return exposureCount;
	return 0;
}


}