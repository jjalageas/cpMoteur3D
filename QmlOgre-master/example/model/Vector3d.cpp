#include "Vector3d.h"
// http://www.terathon.com/code/Vector3d.html


Vector3d::Vector3d() {

}

Vector3d::Vector3d(float r, float s, float t)
{
    x = r;
    y = s;
    z = t;
}



Vector3d& Vector3d::Set(float r, float s, float t)
{
    x = r;
    y = s;
    z = t;
    return (*this);
}

Vector3d Vector3d::operator %(const Vector3d& v) const
        {
            return (Vector3d(y * v.z - z * v.y, z * v.x - x * v.z,
                    x * v.y - y * v.x));
        }

Vector3d& Vector3d::operator /=(float t)
      {
          float f = 1.0F / t;
          x *= f;
          y *= f;
          z *= f;
          return (*this);
      }

Vector3d Vector3d::cross(const Vector3d& v1, const Vector3d& v2)
{
    return (v1 % v2);
}

Vector3d& Vector3d::normalize(void)
{
    return (*this /= sqrtf(x * x + y * y + z * z));
}


