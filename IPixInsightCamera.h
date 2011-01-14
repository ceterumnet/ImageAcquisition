#ifndef __IPixInsightCamera_h
#define __IPixInsightCamera_h

namespace pcl
{
	class IPixInsightCamera
	{
	public:
		IPixInsightCamera* Initialize() const;
		//IPixInsightCamera* ASCOMPixInsightCamera::Initialize() const
		//{
		//return new ASCOMEPixInsightCamera( this );
		//}
	};
}
		


#endif
