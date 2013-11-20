#include <iostream>
#include <ParserBmi3dTest.h>
#include <Examen.h>

using namespace std;

int
main(int argc, char*argv[])
{
    std::string file_in;
    std::string file_out;
    ParserMi3DBinary parser_bmi3d;
Examen* examAfter= parser_bmi3d.loadFile(file_out);


//définit nos images de coupes
//ImageMask2d* Coronal=examAfter->getImageMask2d();
//ImageMask2d* Frontal=examAfter->getImageMask2d();
//ImageMask2d* Sagitale=examAfter->getImageMask2d();

//définit les faces du cube
//ImageMask2d* CoronalFront=examAfter->getImageMask2d();
//ImageMask2d* FrontalFront=examAfter->getImageMask2d();
//ImageMask2d* SagitaleFront=examAfter->getImageMask2d();
//ImageMask2d* CoronalBack=examAfter->getImageMask2d();
//ImageMask2d* FrontalBack=examAfter->getImageMask2d();
//ImageMask2d* SagitaleBack=examAfter->getImageMask2d();


//récupère le mask 3D (nuage de point)
Skeleton* skel=examAfter->getSkeleton();


//récupère le mask 3D (nuage de point)
Mask3d* mask=examAfter->getMask();


}
