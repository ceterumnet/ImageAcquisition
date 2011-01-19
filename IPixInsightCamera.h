#ifndef __IPixInsightCamera_h
#define __IPixInsightCamera_h
#include <pcl/Console.h>

namespace pcl
{
	class IPixInsightCamera
	{
	public:
		IPixInsightCamera *Initialize();
		virtual pcl::String  DoSomething() = 0;
	
	};
}
		


#endif
