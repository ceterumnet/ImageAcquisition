#include "ExposeImageProcess.h"

namespace pcl
{

// ----------------------------------------------------------------------------

ExposeImageProcess* TheExposeImageProcess = 0;

// ----------------------------------------------------------------------------

#include "ExposeImageIcon.xpm"

// ----------------------------------------------------------------------------

ExposeImageProcess::ExposeImageProcess() : MetaProcess()
{
   TheExposeImageProcess = this;

   // Instantiate process parameters
   new EIExposureCount( this );
   new EICameraName( this );
   new EIFilterWheelName( this );
   new EISetTemperature( this );
   new EIFilter( this );
   new EIBinModeX( this );
   new EIBinModeY( this );
   new EISubFrameX1( this );
   new EISubFrameY1( this );
   new EISubFrameX2( this );
   new EISubFrameY2( this );
   new EIDelayBetweenExposures( this );
   new EIFileOutputPath( this );
   new EIFileOutputPattern( this );
//   new EIOnError( this );
}

// ----------------------------------------------------------------------------

IsoString ExposeImageProcess::Id() const
{
   return "ExposeImage";
}

// ----------------------------------------------------------------------------

IsoString ExposeImageProcess::Category() const
{
   return "ImageAcquisition,Preprocessing";
}

// ----------------------------------------------------------------------------

uint32 ExposeImageProcess::Version() const
{
   return 0x100;
}

// ----------------------------------------------------------------------------

String ExposeImageProcess::Description() const
{
   return

   "";
}

// ----------------------------------------------------------------------------

const char** ExposeImageProcess::IconImageXPM() const
{
   return ExposeImageIcon_XPM;
}

// ----------------------------------------------------------------------------

ProcessInterface* ExposeImageProcess::DefaultInterface() const
{
   return TheExposeImageInterface;
}

// -------------------------------------------------------------------------

ProcessImplementation* ExposeImageProcess::Create() const
{
   return new ExposeImageInstance( this );
}

// ----------------------------------------------------------------------------

ProcessImplementation* ExposeImageProcess::Clone( const ProcessImplementation& p ) const
{
   const ExposeImageInstance* instPtr = dynamic_cast<const ExposeImageInstance*>( &p );
   return (instPtr != 0) ? new ExposeImageInstance( *instPtr ) : 0;
}

// ----------------------------------------------------------------------------

} // pcl
