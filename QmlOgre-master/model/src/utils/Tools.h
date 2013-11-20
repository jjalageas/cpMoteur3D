#ifndef TOOLS_H
#define TOOLS_H

#include <Image.hpp>
#include <ImageMask2d.h>
#include <Examen.h>

namespace Tools
{
    template <typename T>
    bool fpEquals(T val1, T val2, T precision);

    float FromHU(ImageMask2d* image, int val);
    int ToHU(ImageMask2d* image, float val);

    Angle CartesianToSpherique(float n1, float n2, float n3);

    int lastSliceId(Examen& e, SliceType type);

    template <typename T>
    int lastSliceId(const Image3d<T>& img, SliceType type);
}

#endif // TOOLS_H
