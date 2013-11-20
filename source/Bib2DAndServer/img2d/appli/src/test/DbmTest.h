#ifndef DBMTEST_H
#define DBMTEST_H

#include <cppunit/extensions/HelperMacros.h>
#include <DatabaseManager.h>

class dbmTest : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE( dbmTest );
    CPPUNIT_TEST(testOpenDB );
    CPPUNIT_TEST(testInsert);
    CPPUNIT_TEST(testListExam);
    CPPUNIT_TEST(testUpdateExam);
    CPPUNIT_TEST_SUITE_END();

public:
    void testOpenDBAux(DataBaseManager &dbm, bool reinit = false);
    void testOpenDB();
    void testInsert();
    void testListExam();
    void testUpdateExam();
};

#endif // TESTBD_H
