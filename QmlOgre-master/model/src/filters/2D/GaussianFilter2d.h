#ifndef GAUSSIANFILTER2D_H
#define GAUSSIANFILTER2D_H

#include "Filter2d.h"

class GaussianFilter2D : public Filter2D
{
public:
    GaussianFilter2D();
    void apply(ImageMask2d &img);
};

#endif // GAUSSIANFILTER2D_H
