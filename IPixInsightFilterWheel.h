#ifndef __IPixFilterWheel_h
#define __IPixFilterWheel_h
#include <pcl/String.h>
#include <pcl/Vector.h>

namespace pcl
{
	class IPixFilterWheel
	{
	public:
		virtual String Description() = 0;
		virtual bool Connected() = 0;
		virtual int SetConnected(bool) = 0;
		virtual short Position() = 0;
		virtual int SetPosition(uint8) = 0;
	};
}

#endif
