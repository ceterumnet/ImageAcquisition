// PixInsightASCOMCameraDriver.h

#pragma once

#include "IPixInsightCamera.h"

namespace pcl {

	class PixInsightASCOMCameraDriver : public IPixInsightCamera
	{
	public:
		PixInsightASCOMCameraDriver();
		
		IPixInsightCamera* PixInsightASCOMCameraDriver::Initialize() const;
		
	private:
		
		// TODO: Add your methods for this class here.
	};
}
