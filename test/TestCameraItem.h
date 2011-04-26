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
#include "../parsers.h"

class CameraItemTest : public CppUnit::TestFixture
{
private:
    pcl::CameraItem *ci1;
    OutputData d;

public:
    void setUp()
    {
        ci1 = new pcl::CameraItem();
        d.YYYY = "2011";
        d.MM = "12";
        d.DD = "31";
    }

    void tearDown()
    {
        delete ci1;
    }

    void testParser()
    {
        pcl::String format("<YYYY>-<MM>-<DD>-M106");
        pcl::String actual = GenerateOutputFileName(format, d);
        pcl::String expected("2011-12-31-M106");
        CPPUNIT_ASSERT_EQUAL(expected, actual);
    }
};
#endif
