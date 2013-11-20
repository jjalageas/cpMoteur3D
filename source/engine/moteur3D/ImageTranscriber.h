#ifndef IMAGETRANSCRIBER_H
#define IMAGETRANSCRIBER_H

#include "../Model/Examen.h"
#include "../Model/Mask.h"
#include "../Model/Struct.h"

class ImageTranscriber
{
public :
    static MiList<ImageData<float> *> *AllImages(Examen *exam, int type);

    static MiList<Point3D_Data_t<float, int> *> *ToVolume(Examen *examen);

    static MiList< Point3D_Color_t<float> *> *FromVolume(Examen *examen);
    static MiList< Point3D_Color_t<float> *> *FromVolumeToImage2D(Examen *examen, int slide, int value);
    static Triplet_t<float*,char*,int> ToVBO (MiList< Point3D_Color_t<float> *> *points);

};

#endif // IMAGETRANSCRIBER_H
