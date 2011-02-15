#include "ExposeImageInstance.h"

namespace pcl
{

	ExposeImageInstance::ExposeImageInstance( const MetaProcess* m) :
ProcessImplementation( m ),
exposureDuration( 1 ),
exposureCount( 1 ),
cameraName( "cam_name" ),
setTemperature( -15 ),
filter( "NONE" ),
binModeX( 1 ),
binModeY( 1 ),
subFrameX1( 0 ),
subFrameY1( 0 ),
subFrameX2( 0 ),
subFrameY2( 0 ),
delayBetweenExposures( 1 )
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
	    exposureCount = x->exposureCount;
	    exposureDuration = x->exposureDuration;
	    cameraName = x->cameraName;
	    filterWheelName = x->filterWheelName;
	    setTemperature = x->setTemperature;
	    filter = x->filter;
	    binModeX = x->binModeX;
	    binModeY = x->binModeY;
	    subFrameX1 = x->subFrameX1;
	    subFrameY1 = x->subFrameY1;
	    subFrameX2 = x->subFrameX2;
	    subFrameY2 = x->subFrameY2;
	    delayBetweenExposures = x->delayBetweenExposures;
	    fileOutputPath = x->fileOutputPath;
	    fileOutputPattern = x->fileOutputPattern;
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
//	if( p == TheExposureDurationParameter )
//	    return NULL;
//	if( p == TheExposureCountParameter )

}
//
//
bool ExposeImageInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
{
	if ( p == TheExposureCountParameter)
	{
		//we need to do something here...
	}
	else
		return false;

	return true;
}
//
//size_type ExposeImageInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
//{
////	if ( p == TheExposureCountParameter )
////		return exposureCount;
//	return 0;
//}


}
