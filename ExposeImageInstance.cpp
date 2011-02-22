#include "ExposeImageInstance.h"

namespace pcl
{

	ExposeImageInstance::ExposeImageInstance( const MetaProcess* m) :
ProcessImplementation( m ),
exposureDuration( 1000 ),
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

void* ExposeImageInstance::LockParameter( const MetaParameter* p, size_type tableRow )
{
	if( p == TheExposureDurationParameter )
		return &exposureDuration;
	if( p == TheExposureCountParameter )
		return &exposureCount;
	if( p == TheCameraNameParameter )
		return cameraName.c_str();
	if( p == TheDelayBetweenExposuresParameter )
		return &delayBetweenExposures;
	if( p == TheBinModeXParameter )
		return &binModeX;
	if( p == TheBinModeYParameter )
		return &binModeY;
	if( p == TheFileOutputPathParameter )
		return fileOutputPath.c_str();
	if( p == TheFileOutputPatternParameter )
		return fileOutputPattern.c_str();
	if( p == TheFilterParameter )
		return filter.c_str();
	if( p == TheFilterWheelNameParameter )
		return filterWheelName.c_str();
	if( p == TheSetTemperatureParameter )
		return &setTemperature;
	if( p == TheSubFrameX1Parameter )
		return &subFrameX1;
	if( p == TheSubFrameY1Parameter )
		return &subFrameY1;
	if( p == TheSubFrameX2Parameter )
		return &subFrameX2;
	if( p == TheSubFrameY2Parameter )
		return &subFrameY2;
	return NULL;
}
//
//
bool ExposeImageInstance::AllocateParameter( size_type sizeOrLength, const MetaParameter* p, size_type tableRow )
{
	if( p == TheExposureDurationParameter ) {}
	if( p == TheExposureCountParameter ) {}
	if( p == TheCameraNameParameter ) {}
	{
		cameraName.Clear();
		if( sizeOrLength > 0 )
			cameraName.Reserve( sizeOrLength );	
	}
	if( p == TheDelayBetweenExposuresParameter ) {}
	if( p == TheBinModeXParameter ) {}
	if( p == TheBinModeYParameter ) {}
	if( p == TheFileOutputPathParameter )
	{
		fileOutputPath.Clear();
		if( sizeOrLength > 0 )
			fileOutputPath.Reserve( sizeOrLength );
	}
	if( p == TheFileOutputPatternParameter )
	{
		fileOutputPattern.Clear();
		if( sizeOrLength > 0 )
			fileOutputPattern.Reserve( sizeOrLength );
	}
	if( p == TheFilterParameter )
	{
		filter.Clear();
		if( sizeOrLength > 0 )
			filter.Reserve( sizeOrLength );
	}
	if( p == TheFilterWheelNameParameter )
	{
		filterWheelName.Clear();
		if( sizeOrLength > 0 )
			filterWheelName.Reserve( sizeOrLength );
	}
	if( p == TheSetTemperatureParameter ) {}
	if( p == TheSubFrameX1Parameter ) {}
	if( p == TheSubFrameY1Parameter ) {}
	if( p == TheSubFrameX2Parameter ) {}
	if( p == TheSubFrameY2Parameter ) {}
	else
		return false;
	return true;
}

size_type ExposeImageInstance::ParameterLength( const MetaParameter* p, size_type tableRow ) const
{
	if( p == TheCameraNameParameter )
		return cameraName.Length();
	if( p == TheFileOutputPathParameter )
		return fileOutputPath.Length();
	if( p == TheFileOutputPatternParameter )
		return fileOutputPattern.Length();
	if( p == TheFilterParameter )
		return filter.Length();
	if( p == TheFilterWheelNameParameter )
		return filterWheelName.Length();
	return 0;
}


}
