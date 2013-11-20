#ifndef GRAY_VIEW_WINDOW_TEST
#define GRAY_VIEW_WINDOW_TEST

#include <GrayValue.h>
#include <GrayViewWindow.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cmath>
#include <debug.h>
#include <iostream>
using namespace std;

class GrayViewWindowTest
        : public CppUnit::TestFixture
{
public:
    GrayViewWindowTest() {
        _slope = 2;
        _intercept = 10;
    }

    CPPUNIT_TEST_SUITE(GrayViewWindowTest);
    CPPUNIT_TEST(base1);
    CPPUNIT_TEST(base2);
    CPPUNIT_TEST(stduse);
    CPPUNIT_TEST(mmbounds);
    CPPUNIT_TEST(lcbounds);
    CPPUNIT_TEST_SUITE_END();

    /*// Call before tests
    void setUp();
    // Call after tests
    void tearDown();
    // Tests*/

    void base1() {
        GrayTranslationFunction f(_slope, _intercept);
        GrayViewWindow* window = GrayViewWindow::createFromMinMax(f, -15, 15);
        CPPUNIT_ASSERT(window->getMin()->getHundsfieldValue() == -15);
        CPPUNIT_ASSERT(window->getMax()->getHundsfieldValue() == 15);
    }

    void base2() {
        GrayTranslationFunction f(_slope, _intercept);
        GrayViewWindow* window2 = GrayViewWindow::createFromLuminosityContrast(f, 5, 15);
        CPPUNIT_ASSERT(window2->getLuminosity()->getHundsfieldValue() == 5);
        CPPUNIT_ASSERT(nearlyEquals(window2->getContrast()->getHundsfieldValue(), 15));
    }

    void stduse() {
        GrayTranslationFunction f(_slope, _intercept);
        GrayViewWindow* window = GrayViewWindow::createFromMinMax(f, 3, 15);
        window->setContrast(1000);
        CPPUNIT_ASSERT(window->getMin()->getHundsfieldValue() < 3);
        cout << "window->getMin()->getHundsfieldValue()" << window->getMin()->getHundsfieldValue() << endl;
        CPPUNIT_ASSERT(window->getMax()->getHundsfieldValue() > 15);
        cout << "window->getMax()->getHundsfieldValue()" << window->getMax()->getHundsfieldValue() << endl;

        window->setMin(0);
        CPPUNIT_ASSERT(window->getContrast()->getHundsfieldValue() > 1000);
    }

    void mmbounds() {

        GrayTranslationFunction f(_slope, _intercept);
        GrayViewWindow* window = GrayViewWindow::createFromMinMax(f, 3, 15);
        window->setMax(HundsfieldValue::max());
        CPPUNIT_ASSERT(window->getMin()->getHundsfieldValue() == 3);
        CPPUNIT_ASSERT(window->getMax()->getHundsfieldValue() == HundsfieldValue::max());
        CPPUNIT_SHOULD_THROW_ASSERT(window->setMax(1000000));

        window->setMax(15);
        CPPUNIT_ASSERT(window->getMax()->getHundsfieldValue() == 15);

        window->setMin(HundsfieldValue::min());
        CPPUNIT_ASSERT(window->getMin()->getHundsfieldValue() == HundsfieldValue::min());
        CPPUNIT_ASSERT(window->getMax()->getHundsfieldValue() == 15);
    }

    void lcbounds() {
        GrayTranslationFunction f(_slope, _intercept);
        GrayViewWindow* window = GrayViewWindow::createFromLuminosityContrast(f, 3, 2*HundsfieldValue::max()-1);
        window->setLuminosity(HundsfieldValue::min());
        window->setContrast(0);

        //std::cout << "window->getLuminosity() : " << window->getLuminosity()->getHundsfieldValue() << std::endl;
        //std::cout << "window->getContrast() : " << window->getContrast()->getHundsfieldValue() << std::endl;

        //CPPUNIT_ASSERT(nearlyEquals(window->getLuminosity()->getHundsfieldValue(), HundsfieldValue::min(), 2));
        CPPUNIT_ASSERT(nearlyEquals(window->getMin()->getHundsfieldValue(), HundsfieldValue::min(), 3));
        CPPUNIT_ASSERT(nearlyEquals(window->getMax()->getHundsfieldValue(), HundsfieldValue::max(), 3));

        /*CPPUNIT_ASSERT(window->getContrast()->getHundsfieldValue() >= 1);
        CPPUNIT_ASSERT(window->getContrast()->getHundsfieldValue() <= 2);



        window = GrayViewWindow::createFromLuminosityContrast(f, 3, 15); // reset
        window->setContrast(2*HundsfieldValue::max());
        CPPUNIT_ASSERT(window->getContrast()->getHundsfieldValue() >= 2*HundsfieldValue::max() - 3);
        CPPUNIT_ASSERT(window->getContrast()->getHundsfieldValue() <= 2*HundsfieldValue::max() + 3);
        CPPUNIT_ASSERT(nearlyEquals(window->getLuminosity()->getHundsfieldValue(), 0));

        std::cout << "window->getMin() : " << window->getMin()->getHundsfieldValue() << std::endl;
        CPPUNIT_ASSERT(nearlyEquals(window->getMin()->getHundsfieldValue(), HundsfieldValue::min(), 3));
        CPPUNIT_ASSERT(nearlyEquals(window->getMax()->getHundsfieldValue(), HundsfieldValue::max(), 3));

        CPPUNIT_SHOULD_THROW_ASSERT(window->setContrast(1000000));
        CPPUNIT_SHOULD_THROW_ASSERT(window->setLuminosity(1000000));*/
    }

private:
    int _slope;
    int _intercept;

    bool nearlyEquals(int i1, int i2, unsigned int diff = 1) {
        return (std::abs(i1 - i2) <= diff);
    }
};

#endif // GRAY_VIEW_WINDOW_TEST
