#ifndef TEST_H
#define TEST_H

#include "CTP.h"
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>

class TestCTP : public CppUnit::TestFixture {

    CPPUNIT_TEST_SUITE(TestCTP);
    CPPUNIT_TEST(testSetType);
    CPPUNIT_TEST(testGetType);
    CPPUNIT_TEST(testSetTR);
    CPPUNIT_TEST(testGetTR);
    CPPUNIT_TEST(testSetWindow);
    CPPUNIT_TEST(testGetWindow);
    CPPUNIT_TEST(testSetSeqNum);
    CPPUNIT_TEST(testGetSeqNum);
    CPPUNIT_TEST(testSetLength);
    CPPUNIT_TEST(testGetLength);
    CPPUNIT_TEST(testSetTimeStamp);
    CPPUNIT_TEST(testGetTimeStamp);
    CPPUNIT_TEST(testSetCRC1);
    CPPUNIT_TEST(testSetCRC12);
    CPPUNIT_TEST(testGetCRC1);
    CPPUNIT_TEST(testSetPayload);
    CPPUNIT_TEST(testGetPayload);


    CPPUNIT_TEST_SUITE_END();

    public:

        void testSetType();
        void testGetType();
        void testSetTR();
        void testGetTR();
        void testSetWindow();
        void testGetWindow();
        void testSetSeqNum();
        void testGetSeqNum();
        void testSetLength();
        void testGetLength();
        void testSetTimeStamp();
        void testGetTimeStamp();
        void testSetCRC1();
        void testSetCRC12();
        void testGetCRC1();
        void testSetPayload();
        void testGetPayload();

};

#endif
