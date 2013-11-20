#include <ParserBmi3dTest.h>
#include <Examen.h>
#include <ParserDicom.h>


// this file is needed to have an auto registration of the test.
CPPUNIT_TEST_SUITE_REGISTRATION(ParserBmi3dTest);


void
ParserBmi3dTest::setUp()
{
    ParserDicom parser_dicom;
    examBefore = parser_dicom.loadFile(file_in);
    examAfter = NULL;
}

void
ParserBmi3dTest::tearDown()
{
    delete examBefore;
    delete examAfter;
}

void
ParserBmi3dTest::save()
{
    bool res = parser_bmi3d.saveFile(file_out, examBefore);
    CPPUNIT_ASSERT(res == true);
}

void
ParserBmi3dTest::load()
{
    examAfter = parser_bmi3d.loadFile(file_out);
    CPPUNIT_ASSERT(examAfter != NULL);
    CPPUNIT_ASSERT(examBefore->getImageRef().getWidth() == examAfter->getImageRef().getWidth());
    CPPUNIT_ASSERT(examBefore->getImageRef().getHeight() == examAfter->getImageRef().getHeight());
    CPPUNIT_ASSERT(examBefore->getImageRef().getDepth() == examAfter->getImageRef().getDepth());
    int errors = 0;
    for (int i=0; i<examBefore->getImageRef().getGlobalSize(); ++i) {
        if (examBefore->getImage()->getData()[i] != examAfter->getImage()->getData()[i]) {
            errors++;
        }
    }
    CPPUNIT_ASSERT(errors == 0);
}
