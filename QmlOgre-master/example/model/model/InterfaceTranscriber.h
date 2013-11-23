#ifndef INTERFACE_TRANSCRIBER_H
#define INTERFACE_TRANSCRIBER_H

#include <Struct.hpp>
#include <GrayViewWindow.h>
//#include <uchar.h>

template<typename T> class Image;
class Examen;
class ImageMask2d;


class InterfaceTranscriber
{
public:
    // Image
  /*  static Image<int>* FromImage(ImageMask2d* image, bool showMask = false);
    static Image<int>* FromImage(ImageMask2d* image,
                                   GrayViewWindow& window,
                                   bool showImage, bool showMask);
    static Image<int>* FromImage(ImageMask2d* image, ImageMask2d* image2,
                                   GrayViewWindow& window);
    static Image<int>* FromImage(ImageMask2d* image, ImageMask2d* image2, ImageMask2d* image3,
                                   GrayViewWindow& window);
*/
    unsigned char* FromImage(Image<float>* image);

    // Volume
    static MiList<Point3D_Color_t<float>* >* FromVolume(Examen* examen, bool surface);
    static Triplet_t<float*,char*,int> FromVolumeVBO(Examen* examen, bool surface);
    static Triplet_t<float*,char*,int> ToVBO(MiList< Point3D_Color_t<float>* >* res);

    // Skeleton
    static MiList< MiList<Segment> >* FromSkeletonWire(Examen* examen);
    static MiList< MiList<Segment> >* FromSkeletonWire(Examen* examen,
                                                       MiList<int>* special);
    static MiList<Point3D_Color_t<float>* >* FromSkeletonVolume(Examen* examen);
    static MiList<Point3D_Color_t<float>* >* FromSkeletonVolume(Examen* examen,
                                                                MiList<int>* special);
};

#endif // INTERFACE_TRANSCRIBER_H
