#ifndef GRAY_VALUE_TEST
#define GRAY_VALUE_TEST

#include <GrayValue.h>
#include <cppunit/extensions/HelperMacros.h>
#include "debug.h"
#include <iostream>


class GrayValueTest
        : public CppUnit::TestFixture
{
public:
    CPPUNIT_TEST_SUITE(GrayValueTest);
    CPPUNIT_TEST(identity);
    CPPUNIT_TEST(conversion);
    CPPUNIT_TEST(copyHU);
    CPPUNIT_TEST(copyEx);
    CPPUNIT_TEST(bounds);
    CPPUNIT_TEST_SUITE_END();

    // Tests

    void identity() {
        GrayTranslationFunction identity(1, 0);
        int val = 100;
        GrayValue *g = new HundsfieldValue(identity, val);
        CPPUNIT_ASSERT(g->getExamenValue() == val);
        CPPUNIT_ASSERT(g->getHundsfieldValue() == val);

        GrayValue *g2 = new ExamenGrayValue(identity, (float) val);
        CPPUNIT_ASSERT(g2->getExamenValue() == val);
        CPPUNIT_ASSERT(g2->getHundsfieldValue() == val);
    }

    void conversion() {
        int slope = 2;
        int intercept = 10;
        GrayTranslationFunction f(slope, intercept);
        int val = 100;
        GrayValue *g = new HundsfieldValue(f, val);
        //std::cout << "Un : " << val * slope + intercept << std::endl;
        //std::cout << "Deux : " << g->getExamenValue() << std::endl;
        CPPUNIT_ASSERT(g->getExamenValue() == (val - intercept) / slope);
        CPPUNIT_ASSERT(g->getHundsfieldValue() == val);

        GrayValue *g2 = new ExamenGrayValue(f, val);
        CPPUNIT_ASSERT(g2->getExamenValue() == val);
        CPPUNIT_ASSERT(g2->getHundsfieldValue() == val * slope + intercept);
    }

    void copyHU() {
        int slope = 2;
        int intercept = 10;
        int val = 100;
        GrayTranslationFunction f(slope, intercept);
        GrayValue *g = new HundsfieldValue(f, val);
        copyAux(slope, intercept, f, g);
    }

    void copyEx() {
        int slope = 2;
        int intercept = 10;
        int val = 100;
        GrayTranslationFunction f(slope, intercept);
        GrayValue *g = new ExamenGrayValue(f, val);
        copyAux(slope, intercept, f, g);
    }

    void bounds() {
        //GrayTranslationFunction *gtf = NULL;
        // slope musn't be 0
        CPPUNIT_SHOULD_THROW_ASSERT(new GrayTranslationFunction(0, 40));
    }


private:
    void copyAux(int slope, int intercept, GrayTranslationFunction f, GrayValue* g) {

        int tmp = (int) g->getExamenValue();
        GrayValue *g2 = g->copy();
        CPPUNIT_ASSERT((int)g->getExamenValue()  == tmp);
        CPPUNIT_ASSERT((int)g2->getExamenValue() == tmp);

        int diff = 10;
        GrayTranslationFunction f2(slope, intercept + diff);
        GrayValue *g3 = g->copy(f2);
        CPPUNIT_ASSERT((int)g->getExamenValue()  == tmp);
        CPPUNIT_ASSERT((int)g2->getExamenValue() == tmp);
        CPPUNIT_ASSERT((int)g3->getExamenValue() == tmp - diff/slope);
    }
};

#endif // GRAY_VALUE_TEST
