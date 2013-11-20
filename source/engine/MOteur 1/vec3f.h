#ifndef _Vec3f
#define _Vec3f

#include <stdio.h>

// OpenGL platform species
#ifdef _WIN64

#elif _WIN32
#include <windows.h>

#elif __APPLE__
#include <GL/glew.h>
#include<GLUT/glut.h>
#include<GL/glu.h>
#include <OpenGL/gl.h>
#include <GL/glext.h>

#else //Linux
#include <GL/glew.h>
#include<GL/glut.h>
#include<GL/glu.h>
#include <GL/gl.h>
#include <GL/glext.h>

#endif

#include <math.h>

class Vec3f
{
public:
    GLfloat v[3];

public:
    inline ~Vec3f(void) {}
    Vec3f(void) { v[0] = v[1] = v[2] = 0.; }
    Vec3f(GLfloat _x, GLfloat _y, GLfloat _z) { v[0] = _x; v[1] = _y; v[2] = _z; }
    
    inline void setX(GLfloat const _x) { v[0] = _x;}
    inline void setY(GLfloat const _y) { v[1] = _y;}
    inline void setZ(GLfloat const _z) { v[2] = _z;}
    inline void set(GLfloat const _x, GLfloat const _y, GLfloat const _z) { v[0] = _x; v[1] = _y; v[2] = _z; }

    inline double getX() { return v[0]; }
    inline double getY() { return v[1]; }
    inline double getZ() { return v[2]; }

    inline void addX(GLfloat const _x) { v[0] += _x;}
    inline void addY(GLfloat const _y) { v[1] += _y;}
    inline void addZ(GLfloat const _z) { v[2] += _z;}

    inline void scaleX(GLfloat const _x) { v[0] *= _x;}
    inline void scaleY(GLfloat const _y) { v[1] *= _y;}
    inline void scaleZ(GLfloat const _z) { v[2] += _z;}

    inline GLfloat getNorm() const { return sqrtf(v[0]*v[0]+v[1]*v[1]+v[2]*v[2]);}

    inline Vec3f& operator=(Vec3f const &_v3f) { v[0] = _v3f[0]; v[1] = _v3f[1]; v[2] = _v3f[2]; return *this; }
    inline Vec3f& operator+=(Vec3f const &_v3f) { v[0] += _v3f[0]; v[1] += _v3f[1]; v[2] += _v3f[2]; return *this; }
    inline Vec3f& operator-=(Vec3f const &_v3f) { v[0] -= _v3f[0]; v[1] -= _v3f[1]; v[2] -= _v3f[2]; return *this; }
    inline Vec3f operator+(Vec3f const &_v3f) const { return Vec3f(v[0] + _v3f[0], v[1] + _v3f[1], v[2] + _v3f[2]); }
    inline Vec3f operator-(Vec3f const &_v3f) const { return Vec3f(v[0] - _v3f[0], v[1] - _v3f[1], v[2] - _v3f[2]); }
    inline Vec3f operator*(GLfloat const &_GLfloat) const { return Vec3f(v[0] * _GLfloat, v[1] * _GLfloat, v[2] * _GLfloat); }
    inline Vec3f operator/(GLfloat const &_GLfloat) const { return Vec3f(v[0] / _GLfloat, v[1] / _GLfloat, v[2] / _GLfloat); }
    inline Vec3f& operator/=(GLfloat const &_GLfloat) { v[0] /= _GLfloat; v[1] /= _GLfloat; v[2] /= _GLfloat; return *this; }
    inline bool operator==(Vec3f const &_v3f) { return _v3f[0] == v[0] && _v3f[1] == v[1] && _v3f[2] == v[2]; }

    inline operator GLfloat const * const ()const { return v;}

    inline static double computeDistance(Vec3f p1, Vec3f p2)
    {
        return sqrt(pow(p2[0] - p1[0], 2) + pow(p2[1] - p1[1], 2) + pow(p2[2] - p1[2], 2));
    }
    Vec3f RotationMatrix(Vec3f _angle);
    Vec3f MultMatrix(GLfloat par_pd_matrix[4][4]);

    inline float length() const
    {
        return (float)sqrt( v[0]*v[0] + v[1]*v[1] + v[2]*v[2] );
    }

    inline Vec3f normal() const
    {
        const float len = length();
        const float tmp = ( len != (float)0 ) ? ( (float)1 / len ) : (float)0;
        return Vec3f( v[0] * tmp, v[1] * tmp, v[2] * tmp );
    }

};


inline Vec3f
ProduitVectoriel(Vec3f const &_u, Vec3f const &_v) //Cross
{
    Vec3f loc_r_normal;
    loc_r_normal.setX(_u[1] * _v[2] - _v[1] * _u[2]);
    loc_r_normal.setY(_v[0] * _u[2] - _u[0] * _v[2]);
    loc_r_normal.setZ(_u[0] * _v[1] - _v[0] * _u[1]);
    return loc_r_normal;
}


inline double
ProduitScalaire(Vec3f const &_u, Vec3f const &_v) //dot
{
    return _u[0]*_v[0] + _u[1]*_v[1] + _u[2]*_v[2];
}


inline GLfloat
mod(GLfloat _value, GLfloat _modulo)
{
    GLfloat loc_d_res = _value;
    if (_value >= _modulo)
    {
        loc_d_res -= _modulo;
    }
    else if (_value <= -_modulo)
    {
        loc_d_res += _modulo;
    }
    else
    {
        ; //nothing to do
    }
    return loc_d_res;
}



#endif

