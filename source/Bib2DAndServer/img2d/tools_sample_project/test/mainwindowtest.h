#ifndef MAINWINDOWTEST_H
#define MAINWINDOWTEST_H

#include "mainwindow.h"
#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include "debug.h"


class MainWindowTest : public MainWindow, public CppUnit::TestFixture
{
public:
    MainWindowTest() :
        MainWindow(),
        CppUnit::TestFixture()
    {}

    CPPUNIT_TEST_SUITE(MainWindowTest);
    CPPUNIT_TEST(facto);
    CPPUNIT_TEST(factoAsserts);
    CPPUNIT_TEST(bug);
    CPPUNIT_TEST_SUITE_END();

    void facto() {
        CPPUNIT_ASSERT(this->factorielle(5) == 120);
        CPPUNIT_ASSERT(this->factorielle(4) == 24);
    }

    void factoAsserts() {
        CPPUNIT_SHOULD_THROW_ASSERT(this->factorielle(0));
        //CPPUNIT_SHOULD_THROW_ASSERT(this->factorielle(3)); : doesn't throw an assertion -> unit test fails. Yeah!!
    }

    void bug() {
        // facto(-1) throws an assertion! -> unit test fails. Yeah!!!!
        CPPUNIT_ASSERT(this->factorielle(-1) == 12);
    }
};

#endif // MAINWINDOWTEST_H
