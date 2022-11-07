#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include "testCTP.h"
#include "CTP.h"
#include <string>
#include <iostream>

using namespace CppUnit;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION( TestCTP );

int main(int argc, char* argv[])
{
    CppUnit::TextUi::TestRunner runner;
    CppUnit::Test *test = CppUnit::TestFactoryRegistry::getRegistry().makeTest();
    runner.addTest( TestCTP::suite() );
    runner.run();
    return 0;
}



static CppUnit::Test *suite()
{
    CppUnit::TestSuite *suiteOfTests = new CppUnit::TestSuite( "TestCTP" );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetType", &TestCTP::testSetType ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetType", &TestCTP::testGetType ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetTR", &TestCTP::testSetTR ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetTR", &TestCTP::testGetTR ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetWindow", &TestCTP::testSetWindow ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetWindow", &TestCTP::testGetWindow ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetSeqNum", &TestCTP::testSetSeqNum ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetSeqNum", &TestCTP::testGetSeqNum ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetLength", &TestCTP::testSetLength ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetLength", &TestCTP::testGetLength ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetTimeStamp", &TestCTP::testSetTimeStamp ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetTimeStamp", &TestCTP::testGetTimeStamp ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetCRC1", &TestCTP::testSetCRC1 ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetCRC12", &TestCTP::testSetCRC12 ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetCRC1", &TestCTP::testGetCRC1 ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testSetPayload", &TestCTP::testSetPayload ) );
    suiteOfTests->addTest( new CppUnit::TestCaller<TestCTP>( "testGetPayload", &TestCTP::testGetPayload ) );
    return suiteOfTests;
}

void TestCTP::testSetType() {
    std::cout << std::endl << "Running Test #1" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setType("01");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetType(){
    std::cout << std::endl << "Running Test #2" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "01";
    unsigned char* BUFF = ctp1.getBufferPointer();
    BUFF[0] = '0';
    BUFF[1] = '1';
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", ctp1.getType() == one);
    if (ctp1.getType() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetTR(){
    std::cout << std::endl << "Running Test #3" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setTR("1");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetTR(){
    std::cout << std::endl << "Running Test #4" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "2";
    unsigned char* BUFF = ctp1.getBufferPointer();
    BUFF[2] = '2';
    CPPUNIT_ASSERT_MESSAGE("Test Failed  : ", ctp1.getTR() == one);
    if (ctp1.getTR() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetWindow(){
    std::cout << std::endl << "Running Test #5" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setWindow("01010");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetWindow(){
    std::cout << std::endl << "Running Test #6" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "69571";
    unsigned char* BUFF = ctp1.getBufferPointer();
    BUFF[3] = '6';
    BUFF[4] = '9';
    BUFF[5] = '5';
    BUFF[6] = '7';
    BUFF[7] = '1';
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", ctp1.getWindow() == one);
    if (ctp1.getWindow() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetSeqNum(){
    std::cout << std::endl << "Running Test #7" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setSeqNum("01010101");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetSeqNum(){
    std::cout << std::endl << "Running Test #8" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "69696969";
    unsigned char* BUFF = ctp1.getBufferPointer();
    for (int i = 8; i < 16; i++) {
        if (i % 2 == 0) {
            BUFF[i] = '6';
        } else {
            BUFF[i] = '9';
        }
    }
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", ctp1.getSeqNum() == one);
    if (ctp1.getSeqNum() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetLength(){
    std::cout << std::endl << "Running Test #9" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setLength("1234567812345678");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetLength(){
    std::cout << std::endl << "Running Test #10" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "5555555555555555";
    unsigned char* BUFF = ctp1.getBufferPointer();
    for (int i = 16; i < 32; i++) {
        BUFF[i] = '5';
    }
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", ctp1.getLength() == one);
    if (ctp1.getLength() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetTimeStamp(){
    std::cout << std::endl << "Running Test #11" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setTimeStamp("12345678123456781234567812345678");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetTimeStamp(){
    std::cout << std::endl << "Running Test #12" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "99999999999999999999999999999999";
    unsigned char* BUFF = ctp1.getBufferPointer();
    for (int i = 32; i < 64; i++) {
        BUFF[i] = '9';
    }
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", ctp1.getTimeStamp() == one);
    if (ctp1.getTimeStamp() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetCRC1(){
    std::cout << std::endl << "Running Test #13" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setCRC1("10101010100100010010001000100100");
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetCRC12(){
    std::cout << std::endl << "Running Test #14" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    ctp1.setType("10");
    ctp1.setTR("1");
    ctp1.setWindow("01010");
    ctp1.setSeqNum("01010101");
    ctp1.setLength("1010000001111101");
    ctp1.setCRC1();
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetCRC1(){
    std::cout << std::endl << "Running Test #15" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "99999999999999999999999999999999";
    unsigned char* BUFF = ctp1.getBufferPointer();
    for (int i = 64; i < 96; i++) {
        BUFF[i] = '9';
    }
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", ctp1.getCRC1() == one);
    if (ctp1.getCRC1() == one) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testSetPayload(){
    std::cout << std::endl << "Running Test #16" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1, ctp2;
    unsigned char* bfr2 = ctp2.getBufferPointer();
    char CHR[40] = "123456781234567812345678123456781234567";
    char* C = CHR;
    ctp1.setPayload(C);
    unsigned char* bfr1 = ctp1.getBufferPointer();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", bfr1 != bfr2);
    if (bfr1 != bfr2) {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}

void TestCTP::testGetPayload(){
    std::cout << std::endl << "Running Test #17" << std::endl;
    std::cout << " . . ." << std::endl;
    CTP ctp1;
    std::string one = "Payload";
    unsigned char* BUFF = ctp1.getBufferPointer();
    BUFF[96] = 'P';
    BUFF[97] = 'a';
    BUFF[98] = 'y';
    BUFF[99] = 'l';
    BUFF[100] = 'o';
    BUFF[101] = 'a';
    BUFF[102] = 'd';
    std::string msg = ctp1.getPayload();
    CPPUNIT_ASSERT_MESSAGE("Test Failed : ", msg[2] == 'y');
    if (msg[2] == 'y') {
      std::cout << "Test Passed!" << std::endl;
    } else {
      std::cout << "ERROR TEST FAILED" << std::endl;
    }
    std::cout << std::endl;
}
