#ifndef FILTER2D_H
#define FILTER2D_H

#include "Filterv2.h"
#include "Examen.h"
#include <iostream>

class Filter2D : public FilterV2
{
public:
    explicit Filter2D(std::string name);
    virtual void apply(ImageMask2d &img) = 0;// modifies image and mask
    void apply(Examen &exam, SliceType type); // apply the filter to every slice
};

#endif // FILTER2D_H
