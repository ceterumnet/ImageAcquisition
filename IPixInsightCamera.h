#ifndef __IPixInsightCamera_h
#define __IPixInsightCamera_h
#include <pcl/String.h>

namespace pcl
{
	class IPixInsightCamera
	{
	public:
		IPixInsightCamera *Initialize();
		virtual pcl::String Name() = 0;
	};
}

#endif
