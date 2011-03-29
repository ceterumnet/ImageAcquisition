#ifndef __IPixFilterWheel_h
#define __IPixFilterWheel_h
#include <pcl/String.h>
#include <pcl/Vector.h>
#include "IPixInsightDevice.h"

namespace pcl
{
	class IPixInsightFilterWheel : public IPixInsightDevice
	{
	public:
		virtual short Position() = 0;
		virtual int SetPosition(uint8) = 0;
		virtual uint8 MaxPosition() = 0;
		virtual uint8 MinPosition() = 0;
	};
}

#endif
