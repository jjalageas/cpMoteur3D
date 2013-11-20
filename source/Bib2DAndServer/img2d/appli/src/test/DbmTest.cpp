#include <cppunit/config/SourcePrefix.h>
#include <DbmTest.h>
#include <DatabaseManager.h>
#include <cstdio>
#include "debug.h"

CPPUNIT_TEST_SUITE_REGISTRATION( dbmTest);

void dbmTest::testOpenDBAux(DataBaseManager &dbm, bool reinit)
{
    QString databasePath = "./img3d.sqlite";
    if (reinit)
        remove(databasePath.toAscii());
    dbm.openDB(databasePath);
}

void dbmTest::testOpenDB()
{
    DataBaseManager dbm;
    testOpenDBAux(dbm, true);

    CPPUNIT_ASSERT_EQUAL ( dbm.isOpen() , true);
    dbm.closeDB();
    CPPUNIT_ASSERT_EQUAL ( dbm.isOpen() , false);
}

void dbmTest::testInsert()
{
    DataBaseManager dbm;
    testOpenDBAux(dbm);

    bool ret=dbm.insertDoctor("toto", "toto", "toto", "toto", 100);
    CPPUNIT_ASSERT_EQUAL(ret,true);
    ret=dbm.insertDoctor("titi", "titi", "titi", "titi", 200);
    CPPUNIT_ASSERT_EQUAL(ret,true);
    ret=dbm.insertDoctor("toto", "aa", "aa", "aa", 50);
    CPPUNIT_ASSERT_EQUAL(ret,false);
    Patient patient;
    patient.age = 12;
    patient.firstname="robert";
    patient.lastname="robert";
    patient.sex='m';
    QDateTime date;
    ret=dbm.insertExam("patient1", 50, date.currentDateTime(),"toto", patient);
    CPPUNIT_ASSERT_EQUAL(ret, true);
    patient.age = 72;
    patient.firstname="raymonde";
    patient.lastname="raymonde";
    patient.sex='f';
    ret=dbm.insertExam("patient2", 120, date.currentDateTime(),"titi", patient);
    CPPUNIT_ASSERT_EQUAL(ret, true);
    ret=dbm.insertExam("patient3",130, date.currentDateTime(), "toto", patient);
    CPPUNIT_ASSERT_EQUAL(ret, false);
    dbm.closeDB();
}

void dbmTest::testListExam()
{
    DataBaseManager dbm;
    testOpenDBAux(dbm);

    Patient patient;
    patient.age = 72;
    patient.firstname="raymonde";
    patient.lastname="raymonde";
    patient.sex='f';
    QDateTime date;
    dbm.insertExam("patient4",20, date.currentDateTime(), "toto", patient);
    std::vector<ExamFile*> lExamFile;
    bool ret=dbm.listExamDoctor("toto",&lExamFile);
    CPPUNIT_ASSERT_EQUAL(ret, true);
    size_t i =2;
    CPPUNIT_ASSERT_EQUAL(lExamFile.size(), i);
    ExamFile *exam = lExamFile[0];
    CPPUNIT_ASSERT_EQUAL(exam->name==QString("patient1"), true);
    exam = lExamFile[1];
    CPPUNIT_ASSERT_EQUAL(exam->name==QString("patient4"), true);
    dbm.closeDB();
}

void dbmTest::testUpdateExam()
{
    DataBaseManager dbm;
    testOpenDBAux(dbm);

    bool ret = dbm.updateExamName(1, "patient12");
    CPPUNIT_ASSERT_EQUAL(ret, true);
    std::vector<ExamFile*> lExamFile;
    eassert(dbm.listExamDoctor("toto", &lExamFile) == true);
    ExamFile *exam = lExamFile[0];
    CPPUNIT_ASSERT_EQUAL(exam->name==QString("patient12"), true);
    dbm.closeDB();
}

