#ifndef Vector3d_H
#define Vector3d_H

#include <math.h>

class Vector3d
{

public:
    Vector3d();
    Vector3d(float r, float s, float t);
    Vector3d& Set(float r, float s, float t);
    Vector3d cross(const Vector3d& v1, const Vector3d& v2);
    Vector3d& normalize(void);

    Vector3d operator %(const Vector3d& v) const;
    Vector3d& operator /=(float t);


    float   x;
    float   y;
    float   z;
};

#endif // Vector3d_H
