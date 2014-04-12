// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
   new EIExposureDuration( this );
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
   return "Provides camera and filter wheel control for acquiring images.";
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
