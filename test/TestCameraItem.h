#ifndef TestCameraItem_h
#define TestCameraItem_h

#include <iostream>
#include <string>

// Note 1

#include <cppunit/Test.h>
#include <cppunit/TestSuite.h>
#include <cppunit/TestCaller.h>
#include <cppunit/TestRunner.h>
#include <cppunit/ui/text/TestRunner.h>
#include "../CameraItem.h"

class CameraItemTest : public CppUnit::TestFixture
{
private:
    pcl::CameraItem *ci1;
public:
    void setUp()
    {
        ci1 = new pcl::CameraItem();
    }

    void tearDown()
    {
        delete ci1;
    }
};
#endif
