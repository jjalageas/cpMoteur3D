#include <QtGui/QApplication>
#include <debug.h>
#include <iostream>
#include "mainwindow.h"

#ifdef UNIT_TESTS
//#include <cppunit/ui/qt/TestRunner.h>
#include <qxcppunit/testrunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#endif

/**
\mainpage Tools sample project

\section aim_section   What is the aim of this project ?
This project aims to test and determine what is the best solution
to organize a project and use standard developpement tools such as unit tests
and auto documentation generation.
\section Section2
You can type other content here... :-)
*/


using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    #ifndef UNIT_TESTS
//try {
        MainWindow w;
        w.show();
        int res = a.exec();
        eassert("toto" == "tata");
        return res;
//    } catch (AssertException &ae) {
//        cerr << ae.what() << endl;
//    }
    return EXIT_FAILURE;
    #else
        #ifdef NDEBUG
            cout << "This program has been built in realease mode "
                    "so the assertions will not be covered by the unit tests." << endl;
        #endif
        #ifdef GRAPHICAL_UNIT_TESTS
            //CppUnit::QtTestRunner runner; // widget mode
            QxCppUnit::TestRunner runner; // qml mode

            runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
            runner.run();
            return EXIT_SUCCESS;
        #else
            // Console tests (for Jenkins)

             // Create the event manager and test controller
            CPPUNIT_NS::TestResult controller;

            // Add a listener that collects test result
            CPPUNIT_NS::TestResultCollector result;
            controller.addListener(&result);

            // Add a listener that print dots as test run.
            CPPUNIT_NS::BriefTestProgressListener progress;
            controller.addListener(&progress);

            // Add the top suite to the test runner
            CPPUNIT_NS::TestRunner runner;
            runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
            runner.run( controller );

            // Print test in a compiler compatible format.
            CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
            outputter.write();

            // Uncomment this for XML output
            std::ofstream file("cppunit-report.xml");
            CPPUNIT_NS::XmlOutputter xml( &result, file );
            xml.write();
            file.close();
            return EXIT_SUCCESS;
       #endif // GRAPHICAL_UNIT_TESTS
    #endif // UNIT_TESTS
}
