#ifndef IMAGE2DTEST_H
#define IMAGE2DTEST_H

#include "Image.hpp"
#include <cppunit/extensions/HelperMacros.h>
#include "debug.h"
#include <iostream>

class Image2dTest : public CppUnit::TestFixture
{
    public:
        CPPUNIT_TEST_SUITE(Image2dTest);
        CPPUNIT_TEST(setGetter);
        CPPUNIT_TEST_SUITE_END();

    void setGetter() {
        Image<float> *img2d = new Image<float>(50, 50);
        img2d->set(10., 5, 10);
        CPPUNIT_ASSERT(img2d->get(5, 10) == 10.); // Oo comparing floats with ==
        // A voir et terminer
    }
};

#endif // IMAGE2DTEST_H
