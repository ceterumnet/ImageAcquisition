// ImageAcquisition Copyright (C) 2011  David Raphael
// This program comes with ABSOLUTELY NO WARRANTY.
// This is free software, and you are welcome to redistribute it
// under certain conditions; 
//
// This work is licensed under the Creative Commons Attribution-NonCommercial-ShareAlike 3.0 Unported License. 
// To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-sa/3.0/ or send a letter to 
// Creative Commons, 444 Castro Street, Suite 900, Mountain View, California, 94041, USA.


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
