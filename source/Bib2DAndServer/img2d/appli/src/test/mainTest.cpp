#include <QtGui/QApplication>

#include <iostream>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/BriefTestProgressListener.h>
#include <cppunit/CompilerOutputter.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/TestResult.h>
#include <cppunit/TestResultCollector.h>
#include <cppunit/TestRunner.h>
#include <cppunit/XmlOutputter.h>
#ifdef GRAPHICAL_UNIT_TESTS
    #include <qxcppunit/testrunner.h> // not available on every system.
// You may replace it with the graphical test runner proposed by your distribution.
#endif // GRAPHICAL_UNIT_TESTS

using namespace std;

int
main(int argc, char*argv[])
{
    QApplication app(argc, argv);
    #ifndef UNIT_TESTS
        #error "MaintTest compiled without the UNIT_TESTS macro defined. (debug.h needs it!)"
    #endif //UNIT_TESTS
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
        runner.run(controller);

        // Print test in a compiler compatible format.
        CPPUNIT_NS::CompilerOutputter outputter(&result, CPPUNIT_NS::stdCOut());
        outputter.write();

        // XML output
        // Uncomment this for XML output
        std::ofstream file("cppunit-report.xml");
        CPPUNIT_NS::XmlOutputter xml( &result, file );
        xml.write();
        file.close();
        return EXIT_SUCCESS;
    #endif // GRAPHICAL_UNIT_TESTS
}
