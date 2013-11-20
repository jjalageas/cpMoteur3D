#ifndef MATRIX_H
#define MATRIX_H
#include <cmath>

#include "vec3f.h"

template<typename __lreal>
class Matrix4x4
{
public:
    inline operator __lreal const * const ()const
    { return m;}
    
    inline void setTranslate(__lreal x, __lreal y, __lreal z);
    inline void setScale    (__lreal x, __lreal y, __lreal z);
    inline void setRotate   (__lreal angle, __lreal x, __lreal y, __lreal z);
    
    inline void setPerspective(__lreal fovy, __lreal aspect, __lreal zNear, __lreal zFar);
    inline void lookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up);
    
    inline void addTranslate(__lreal x, __lreal y, __lreal z);
    inline void addScale    (__lreal x, __lreal y, __lreal z);
    inline void addRotate   (__lreal angle, __lreal x, __lreal y, __lreal z);
    
    inline Matrix4x4<__lreal> & operator *= (Matrix4x4<__lreal> const & _m);
    inline Matrix4x4<__lreal> operator*( Matrix4x4<__lreal> const & _m ) const;
    
    inline Matrix4x4<__lreal> inverse();
    
    static inline Vec3f unProject(double objX, double objY, double objZ,
                                  const Matrix4x4<__lreal>& model,
                                  const Matrix4x4<__lreal>& proj, int view[4]);
    
    /* Data */
public:
    __lreal m[16];
};


template< typename __lreal >
inline Matrix4x4<__lreal>
Matrix4x4<__lreal> ::operator*( Matrix4x4<__lreal> const & _m ) const
{
    Matrix4x4<__lreal> tmp;
    
    tmp.m[0] = m[0]*_m.m[0] + m[4]*_m.m[1] + m[8]*_m.m[2]  + m[12]*_m.m[3];
    tmp.m[1] = m[0]*_m.m[4] + m[4]*_m.m[5] + m[8]*_m.m[6]  + m[12]*_m.m[7];
    tmp.m[2] = m[0]*_m.m[8] + m[4]*_m.m[9] + m[8]*_m.m[10] + m[12]*_m.m[11];
    tmp.m[3] = m[0]*_m.m[12]+ m[4]*_m.m[13]+ m[8]*_m.m[14] + m[12]*_m.m[15];
    
    tmp.m[4] = m[1]*_m.m[0] + m[5]*_m.m[1] + m[9]*_m.m[2]  + m[13]*_m.m[3];
    tmp.m[5] = m[1]*_m.m[4] + m[5]*_m.m[5] + m[9]*_m.m[6]  + m[13]*_m.m[7];
    tmp.m[6] = m[1]*_m.m[8] + m[5]*_m.m[9] + m[9]*_m.m[10] + m[13]*_m.m[11];
    tmp.m[7] = m[1]*_m.m[12]+ m[5]*_m.m[13]+ m[9]*_m.m[14] + m[13]*_m.m[15];
    
    tmp.m[8] = m[2]*_m.m[0] + m[6]*_m.m[1] + m[10]*_m.m[2] + m[14]*_m.m[3];
    tmp.m[9] = m[2]*_m.m[4] + m[6]*_m.m[5] + m[10]*_m.m[6] + m[14]*_m.m[7];
    tmp.m[10] = m[2]*_m.m[8] + m[6]*_m.m[9] + m[10]*_m.m[10]+ m[14]*_m.m[11];
    tmp.m[11] = m[2]*_m.m[12]+ m[6]*_m.m[13]+ m[10]*_m.m[14]+ m[14]*_m.m[15];
    
    tmp.m[12] = m[3]*_m.m[0] + m[7]*_m.m[1] + m[11]*_m.m[2] + m[15]*_m.m[3];
    tmp.m[13] = m[3]*_m.m[4] + m[7]*_m.m[5] + m[11]*_m.m[6] + m[15]*_m.m[7];
    tmp.m[14] = m[3]*_m.m[8] + m[7]*_m.m[9] + m[11]*_m.m[10]+ m[15]*_m.m[11];
    tmp.m[15] = m[3]*_m.m[12]+ m[7]*_m.m[13]+ m[11]*_m.m[14]+ m[15]*_m.m[15];
    
    return tmp;
}


template<typename __lreal>
inline Matrix4x4<__lreal>
Matrix4x4<__lreal>::inverse()
{
    Matrix4x4<__lreal> result;
    
    __lreal t0  = m[10]*m[15] - m[11]*m[14];
    __lreal t1  = m[9]*m[15]  - m[11]*m[13];
    __lreal t2  = m[9]*m[14]  - m[10]*m[13];
    __lreal t3  = m[8]*m[15]  - m[11]*m[12];
    __lreal t4  = m[8]*m[14]  - m[10]*m[12];
    __lreal t5  = m[8]*m[13]  - m[9]*m[12];
    __lreal t6  = m[2]*m[7]   - m[3]*m[6];
    __lreal t7  = m[1]*m[7]   - m[3]*m[5];
    __lreal t8  = m[1]*m[6]   - m[2]*m[5];
    __lreal t9  = m[0]*m[7]   - m[3]*m[4];
    __lreal t10 = m[0]*m[6]   - m[2]*m[4];
    __lreal t11 = m[0]*m[5]   - m[1]*m[4];
    
    __lreal det = t0*t11 - t1*t10 + t2*t9 + t3*t8 - t4*t7 + t5*t6;
    
    if ( fabs( det ) < 1e-12 ) return Matrix4x4<__lreal>();
    
    __lreal idet = 1.0 / det;
    
    result.m[0]  =  m[5]*t0  - m[6]*t1   + m[7]*t2;
    result.m[4]  = -m[4]*t0  + m[6]*t3   - m[7]*t4;
    result.m[8]  =  m[4]*t1  - m[5]*t3   + m[7]*t5;
    result.m[12] = -m[4]*t2  + m[5]*t4   - m[6]*t5;
    
    result.m[1]  = -m[1]*t0  + m[2]*t1   - m[3]*t2;
    result.m[5]  =  m[0]*t0  - m[2]*t3   + m[3]*t4;
    result.m[9]  = -m[0]*t1  + m[1]*t3   - m[3]*t5;
    result.m[13] =  m[0]*t2  - m[1]*t4   + m[2]*t5;
    
    result.m[2]  =  m[13]*t6 - m[14]*t7  + m[15]*t8;
    result.m[6]  = -m[12]*t6 + m[14]*t9  - m[15]*t10;
    result.m[10] =  m[12]*t7 - m[13]*t9  + m[15]*t11;
    result.m[14] = -m[12]*t8 + m[13]*t10 - m[14]*t11;
    
    result.m[3]  = -m[9]*t6  + m[10]*t7  - m[11]*t8;
    result.m[7]  =  m[8]*t6  - m[10]*t9  + m[11]*t10;
    result.m[11] = -m[8]*t7  + m[9]*t9   - m[11]*t11;
    result.m[15] =  m[8]*t8  - m[9]*t10  + m[10]*t11;
    
    for ( int i = 0; i < 16; ++i ) result.m[i] *= idet;
    
    return result;
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::setTranslate(__lreal x, __lreal y, __lreal z)
{
    m[ 0] = __lreal(1); m[ 4] = __lreal(0); m[ 8] = __lreal(0); m[12] = __lreal(x);
    m[ 1] = __lreal(0); m[ 5] = __lreal(1); m[ 9] = __lreal(0); m[13] = __lreal(y);
    m[ 2] = __lreal(0); m[ 6] = __lreal(0); m[10] = __lreal(1); m[14] = __lreal(z);
    m[ 3] = __lreal(0); m[ 7] = __lreal(0); m[11] = __lreal(0); m[15] = __lreal(1);
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::setScale(__lreal x, __lreal y, __lreal z)
{
    m[ 0] = __lreal(x); m[ 4] = __lreal(0); m[ 8] = __lreal(0); m[12] = __lreal(0);
    m[ 1] = __lreal(0); m[ 5] = __lreal(y); m[ 9] = __lreal(0); m[13] = __lreal(0);
    m[ 2] = __lreal(0); m[ 6] = __lreal(0); m[10] = __lreal(z); m[14] = __lreal(0);
    m[ 3] = __lreal(0); m[ 7] = __lreal(0); m[11] = __lreal(0); m[15] = __lreal(1);
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::setRotate(__lreal angle, __lreal x, __lreal y, __lreal z)
{
    __lreal c = std::cos(angle*__lreal(M_PI)/__lreal(180));
    __lreal s = std::sin(angle*__lreal(M_PI)/__lreal(180));
    
    m[ 0] = x*x*(__lreal(1)-c)+c  ; m[ 4] = x*y*(__lreal(1)-c)-z*s; m[ 8] = x*z*(__lreal(1)-c)+y*s; m[12] = __lreal(0);
    m[ 1] = y*x*(__lreal(1)-c)+z*s; m[ 5] = y*y*(__lreal(1)-c)+c  ; m[ 9] = y*z*(__lreal(1)-c)-x*s; m[13] = __lreal(0);
    m[ 2] = z*x*(__lreal(1)-c)-y*s; m[ 6] = z*y*(__lreal(1)-c)+x*s; m[10] = z*z*(__lreal(1)-c)+c  ; m[14] = __lreal(0);
    m[ 3] = __lreal(0)            ; m[ 7] = __lreal(0)            ; m[11] = __lreal(0)            ; m[15] = __lreal(1);
    
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::setPerspective(__lreal fovy, __lreal aspect, __lreal zNear, __lreal zFar)
{
    __lreal f = __real(1)/std::tan(fovy*__lreal(M_PI)/__lreal(360));
    
    m[ 0] = f/aspect  ; m[ 4] = __lreal(0); m[ 8] = __lreal(0)               ; m[12] = __lreal(0);
    m[ 1] = __lreal(0); m[ 5] = f         ; m[ 9] = __lreal(0)               ; m[13] = __lreal(0);
    m[ 2] = __lreal(0); m[ 6] = __lreal(0); m[10] = (zFar+zNear)/(zNear-zFar); m[14] = __lreal(2)*zFar*zNear/(zNear-zFar);
    m[ 3] = __lreal(0); m[ 7] = __lreal(0); m[11] = __lreal(-1)              ; m[15] = __lreal(1);
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::lookAt(const Vec3f &eye, const Vec3f &center, const Vec3f &up)
{
    Vec3f forward = (center - eye).normal();
    Vec3f side = ProduitVectoriel(forward, up).normal();
    Vec3f upVector = ProduitVectoriel(side, forward);
    
    m[ 0] = side.getX() ; m[ 4] = side.getY(); m[ 8] = side.getZ(); m[12] = ProduitScalaire(side, eye);
    m[ 1] = upVector.getX(); m[ 5] = upVector.getY(); m[ 9] = upVector.getZ(); m[13] = -ProduitScalaire(upVector, eye);
    m[ 2] = forward.getX(); m[ 6] = forward.getY(); m[10] = forward.getZ(); m[14] = ProduitScalaire(forward, eye);
    m[ 3] = 0.0; m[ 7] = 0.0; m[11] = 0.0; m[15] = 1.0;
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::addTranslate(__lreal x, __lreal y, __lreal z)
{
    Matrix4x4<__lreal> tmp;
    tmp.setTranslate(x,y,z);
    *this*=tmp;
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::addScale(__lreal x, __lreal y, __lreal z)
{
    Matrix4x4<__lreal> tmp;
    tmp.setScale(x,y,z);
    *this*=tmp;
}


template<typename __lreal>
inline void
Matrix4x4<__lreal>::addRotate(__lreal angle, __lreal x, __lreal y, __lreal z)
{
    Matrix4x4<__lreal> tmp;
    tmp.setRotate(angle,x,y,z);
    *this*=tmp;
}


template<typename __lreal>
inline Matrix4x4<__lreal> &
Matrix4x4<__lreal>::operator *= (Matrix4x4<__lreal> const & _m)
{
    Matrix4x4<__lreal> tmp = *this;
    m[ 0] = tmp[ 0]*_m[ 0]+tmp[ 4]*_m[ 1]+tmp[ 8]*_m[ 2]+tmp[12]*_m[ 3];
    m[ 1] = tmp[ 1]*_m[ 0]+tmp[ 5]*_m[ 1]+tmp[ 9]*_m[ 2]+tmp[13]*_m[ 3];
    m[ 2] = tmp[ 2]*_m[ 0]+tmp[ 6]*_m[ 1]+tmp[10]*_m[ 2]+tmp[14]*_m[ 3];
    m[ 3] = tmp[ 3]*_m[ 0]+tmp[ 7]*_m[ 1]+tmp[11]*_m[ 2]+tmp[15]*_m[ 3];
    
    m[ 4] = tmp[ 0]*_m[ 4]+tmp[ 4]*_m[ 5]+tmp[ 8]*_m[ 6]+tmp[12]*_m[ 7];
    m[ 5] = tmp[ 1]*_m[ 4]+tmp[ 5]*_m[ 5]+tmp[ 9]*_m[ 6]+tmp[13]*_m[ 7];
    m[ 6] = tmp[ 2]*_m[ 4]+tmp[ 6]*_m[ 5]+tmp[10]*_m[ 6]+tmp[14]*_m[ 7];
    m[ 7] = tmp[ 3]*_m[ 4]+tmp[ 7]*_m[ 5]+tmp[11]*_m[ 6]+tmp[15]*_m[ 7];
    
    m[ 8] = tmp[ 0]*_m[ 8]+tmp[ 4]*_m[ 9]+tmp[ 8]*_m[10]+tmp[12]*_m[11];
    m[ 9] = tmp[ 1]*_m[ 8]+tmp[ 5]*_m[ 9]+tmp[ 9]*_m[10]+tmp[13]*_m[11];
    m[10] = tmp[ 2]*_m[ 8]+tmp[ 6]*_m[ 9]+tmp[10]*_m[10]+tmp[14]*_m[11];
    m[11] = tmp[ 3]*_m[ 8]+tmp[ 7]*_m[ 9]+tmp[11]*_m[10]+tmp[15]*_m[11];
    
    m[12] = tmp[ 0]*_m[12]+tmp[ 4]*_m[13]+tmp[ 8]*_m[14]+tmp[12]*_m[15];
    m[13] = tmp[ 1]*_m[12]+tmp[ 5]*_m[13]+tmp[ 9]*_m[14]+tmp[13]*_m[15];
    m[14] = tmp[ 2]*_m[12]+tmp[ 6]*_m[13]+tmp[10]*_m[14]+tmp[14]*_m[15];
    m[15] = tmp[ 3]*_m[12]+tmp[ 7]*_m[13]+tmp[11]*_m[14]+tmp[15]*_m[15];
    
    return *this;
}


template< typename __lreal >
inline Vec3f
Matrix4x4<__lreal>::unProject(double objX, double objY, double objZ,
                              const Matrix4x4<__lreal>& model,
                              const Matrix4x4<__lreal>& proj, int view[4])
{
    __lreal *vec4NDC = new __lreal[4];
    
    vec4NDC[0] = 2*(objX-view[0])/view[2] -1;
    vec4NDC[1] = 2*(objY-view[1])/view[3] -1;
    vec4NDC[2] = 2*objZ-1;
    vec4NDC[3] = 1;
    
    
    Matrix4x4<__lreal> tmpM(proj * model);
    Matrix4x4<__lreal> tmpMInv =  tmpM.inverse();
    __lreal *v = new __lreal[4];
    
    v[0] = tmpMInv.m[0]*vec4NDC[0] + tmpMInv.m[4]*vec4NDC[1] + tmpMInv.m[8]*vec4NDC[2] + tmpMInv.m[12]*vec4NDC[3];
    v[1] = tmpMInv.m[1]*vec4NDC[0] + tmpMInv.m[5]*vec4NDC[1] + tmpMInv.m[9]*vec4NDC[2] + tmpMInv.m[13]*vec4NDC[3];
    v[2] = tmpMInv.m[2]*vec4NDC[0] + tmpMInv.m[6]*vec4NDC[1] + tmpMInv.m[10]*vec4NDC[2]+ tmpMInv.m[14]*vec4NDC[3];
    v[3] = tmpMInv.m[3]*vec4NDC[0] + tmpMInv.m[7]*vec4NDC[1] + tmpMInv.m[11]*vec4NDC[2]+ tmpMInv.m[15]*vec4NDC[3];
    
    return Vec3f(v[0]/v[3], v[1]/v[3], v[2]/v[3]);
}
#endif // MATRIX_H
