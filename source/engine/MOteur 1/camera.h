#ifndef _CAMERA
#define _CAMERA

#include <cstdio>
#include <cmath>

#include "vec3f.h"
#include"matrix.h"

#include <iostream>


// OpenGL platform species
#ifdef _WIN64

#elif _WIN32
#include <windows.h>
#include <GL/glu.h>

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


class Camera
{
    public:
        Camera();
        Camera(Vec3f eye, Vec3f target, Vec3f up);
        Camera(float eyeX, float eyeY, float eyeZ,
               float targetX, float targetY, float targetZ,
               float upX, float upY, float upZ);

        Vec3f getEye() const;
        Vec3f getTarget() const;
        Vec3f getUp() const;

        void setEye(Vec3f eye);
        void setEye(float x, float y, float z);
        void setTarget(Vec3f eye);
        void setTarget(float x, float y, float z);
        void setUp(Vec3f eye);
        void setUp(float x, float y, float z);
        void lookAt();

        void glSet();


        void Display();
    //private:
        void computeSide();

        Vec3f _eye, _target, _up, _side;
        Matrix4x4<GLfloat> c_matrix;
};

//class Camera
//{
//    private:
//        Vec3f _eye, _dir, _top;

//    public:
//        // initialize default camera
//        inline Camera(void) : _eye(0., 0., 0.), _dir(0., 0., -1.), _top(0., 1., 0.) { }
//        inline ~Camera(void) { }

//        // get the Cemara viewpoint
//        inline Vec3f getEye() const { return _eye; }
//        // get the camera viewing direction
//        inline Vec3f getDir() const { return _dir; }
//        // get upper direction of the camera frame
//        inline Vec3f getTop() const { return _top; }

//        inline Camera& operator=(Camera const &cam) { _eye = cam._eye; _dir = cam._dir; _top = cam._top; return *this; }

//        inline void reset(void) { _eye.set(0., 0., 0.); _dir.set(0., 0., -1.); _top.set(0., 1., 0.); }

//        inline void set(Vec3f const &eye, Vec3f const &dir, Vec3f const &top) { _eye = eye; _dir = dir; _top = top; }
//        inline void setDir(Vec3f const &dir) { _dir = dir; }
//        inline void setEye(Vec3f const &eye) { _eye = eye; }
//        inline void setTop(Vec3f const &top) { _top = top; }

//        // Send the Camera parameter to current matrix
//        void glSet(void);
//};

#endif
