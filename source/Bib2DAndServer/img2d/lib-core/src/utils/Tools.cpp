#include "Tools.h"
#include <cmath>


template <typename T>
bool Tools::fpEquals(T val1, T val2, T precision) {
    return (std::abs(val1 - val2) < precision);
}

Angle Tools::CartesianToSpherique(float n1, float n2, float n3)
{
    double p = sqrt(n1 * n1 + n2 * n2 + n3 * n3);

    Angle res;
    res.rho = acos(n3 / p);
    double theta = 0.0;
    double epsilon = 0.000001;

    if (fpEquals((double) n1, 0., epsilon)) {
        if (! fpEquals((double)n2, 0., epsilon))
            theta = M_PI / 2.; //1.57079633; //raccourcis de arcos(0/)
    }
    else {
        theta = acos(n1 / sqrt(n1 * n1 + n2 * n2));
        if (n2 < 0)
            theta = 2 * M_PI - theta;
    }
    res.theta = theta;
    return res;
}


int Tools::lastSliceId(Examen& e, SliceType type)
{
    return lastSliceId(e.getImageRef(), type);
}

template <typename T>
int Tools::lastSliceId(const Image3d<T>& img, SliceType type)
{
    switch(type) {
        case CORONAL:
            return img.getDepth();
        case FRONTAL:
            return img.getHeight();
        case SAGITAL:
            return img.getWidth();
    }
    eassert(false);
    return 0;
}
