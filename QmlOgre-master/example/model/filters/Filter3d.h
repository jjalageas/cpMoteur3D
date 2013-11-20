#ifndef FILTER3D_H
#define FILTER3D_H

#include "Filterv2.h"
#include <iostream>
#include <Examen.h>

class Filter3D : public FilterV2
{
public:
    explicit Filter3D(std::string name);
    virtual void apply(Examen &exam) = 0; // modifies image and mask
};

#endif // FILTER3D_H
