#include "TestCameraItem.h"
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestCaller.h>

int main( int argc, char **argv )
{
    //CppUnit::TestSuite suite;
    //CppUnit::TestResult result;
    //suite.addTest( new CppUnit::TestCaller<CameraItemTest>( "testParser", &CameraItemTest::testParser ) );

    CppUnit::TextUi::TestRunner runner;
    runner.addTest( new CppUnit::TestCaller<CameraItemTest>( "testParser", &CameraItemTest::testParser ) );

    runner.run();
    return 0;

    //    bool wasSuccessful = runner.run( "", false );
    //    return !wasSuccessful;
}
