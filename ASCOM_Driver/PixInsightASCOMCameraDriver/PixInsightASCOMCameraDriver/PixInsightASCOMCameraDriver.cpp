// This is the main DLL file.

#include "stdafx.h"

#include "PixInsightASCOMCameraDriver.h"

namespace pcl
{

	PixInsightASCOMCameraDriver::PixInsightASCOMCameraDriver() 
	{


	}


	IPixInsightCamera* PixInsightASCOMCameraDriver::Initialize() const
	{
		return new PixInsightASCOMCameraDriver();
	}


}

