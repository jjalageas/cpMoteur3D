#ifndef PARSER_BMI3D_TEST_H
#define PARSER_BMI3D_TEST_H

#include <ParserMi3DBinary.h>

#include <cppunit/extensions/HelperMacros.h>

class Examen;


class ParserBmi3dTest
        : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(ParserBmi3dTest);
    CPPUNIT_TEST(save);
    CPPUNIT_TEST(load);
    CPPUNIT_TEST_SUITE_END();


private:
    Examen* examBefore;
    Examen* examAfter;
    std::string file_in;
    std::string file_out;
    ParserMi3DBinary parser_bmi3d;


public:
    // Call before tests
    void setUp();
    // Call after tests
    void tearDown();
    // Tests
    void save();
    void load();
};

#endif // PARSER_BMI3D_TEST_H
