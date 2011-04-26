// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
