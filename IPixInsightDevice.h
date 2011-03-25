#ifndef __IPixInsightDevice_h
#define __IPixInsightDevice_h
#include <pcl/String.h>
#include <pcl/Vector.h>


namespace pcl
{
    class IPixInsightDevice
    {
    public:
        virtual bool Connected() = 0;
        virtual int SetConnected(bool) = 0;
        virtual String Description() = 0;
    };
}

#endif
