#include "camera.h"

Camera::Camera()
{
    _eye = Vec3f(0.0f, 0.0f, -3.0f);
    _target = Vec3f(0.0f, 0.0f, 0.0f);
    _up = Vec3f(0.0f, 1.0f, 0.0f);

    for(int i = 0; i < 16; i++)
        c_matrix.m[i] = 0.0f;
}


Camera::Camera(Vec3f eye, Vec3f target, Vec3f up)
:_eye(eye), _target(target), _up(up){ }


Camera::Camera(float eyeX, float eyeY, float eyeZ,
               float targetX, float targetY, float targetZ,
               float upX, float upY, float upZ)
{
    _eye.set(eyeX, eyeY, eyeZ);
    _target.set(targetX, targetY, targetZ);
    _up.set(upX, upY, upZ);
}


void
Camera::Display()
{
    std::cout << "---------------------------------"<< std::endl;
    std::cout << "         CAMERA            "<< std::endl;
    std::cout << "---------------------------------"<< std::endl;
    std::cout<<"EYE: "<<_eye[0]<<","<< _eye[1]<<","<< _eye[2]<<std::endl;
    std::cout<<"TARGET: "<<_target[0]<<","<< _target[1]<<","<< _target[2]<<","<<std::endl;
    std::cout<<"UP: "<<_up[0]<<","<< _up[1]<<","<< _up[2]<<std::endl;
}


void
Camera::lookAt()
{
    Matrix4x4<GLfloat> matCam;
    matCam.lookAt(_eye, _target, _up);
    for(int i = 0; i < 16; i++){
        c_matrix.m[i] = (GLfloat)matCam[i];
    }
}


void
Camera::computeSide(){}


Vec3f
Camera::getEye() const
{
    return _eye;
}


void
Camera::setEye(Vec3f eye)
{
    _eye = eye;
}


void
Camera::setEye(float x, float y, float z)
{
    _eye.set(x, y, z);
}


Vec3f
Camera::getTarget() const
{
    return _target;
}


void
Camera::setTarget(Vec3f target)
{
    _target = target;
}


void
Camera::setTarget(float x, float y, float z)
{
    _target.set(x, y, z);
}


Vec3f
Camera::getUp() const
{
    return _up;
}


void
Camera::setUp(Vec3f up)
{
    _up = up;
}

void
Camera::setUp(float x, float y, float z)
{
    _up.set(x, y, z);
}


void Camera::glSet(void)
{
    glLoadIdentity();
    gluLookAt(_eye[0], _eye[1], _eye[2],
              _target[0], _target[1], _target[2],
              _up[0], _up[1], _up[2]);
}


