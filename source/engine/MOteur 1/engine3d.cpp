#include "engine3d.h"


Engine3D::Engine3D(QWidget *parent)
: QGLWidget(parent),_mouseMode(TRACKBALL)
{
    _width=0;
    _height=0;
    setFocusPolicy(Qt::StrongFocus);
}


void
Engine3D::setData(Mesh * Meshs, View2DContainer* All2DViews,
                  int widthBoundingBox,int heightBoundingBox,int depthBoundingBox)
{
    _width=widthBoundingBox;
    _height=heightBoundingBox;
    _scene->setData(Meshs,All2DViews,widthBoundingBox,heightBoundingBox,depthBoundingBox);
}


void
Engine3D::setData(Mesh * Meshs)
{
    _scene->setData(Meshs);
}


void
Engine3D::keyPressEvent(QKeyEvent *keyEvent)
{
    switch(keyEvent->key())
    {
        case Qt::Key_Escape:
            close();
            break;
        case Qt::Key_M:
            break;
    }
    updateGL();
}


void
Engine3D::mousePressEvent(QMouseEvent *event)
{
    if(_mouseMode == TRACKBALL)
        _scene->setLastXY(event->x(), event->y());
    //    else if(_mouseMode == PICKING)
    //        _scene->picking30(event->x(), event->y());
    updateGL();
}


void
Engine3D::mouseMoveEvent(QMouseEvent *event)
{
    if(_mouseMode == TRACKBALL)
        _scene->mouseMotion((GLint)event->x(), (GLint)event->y());
    updateGL();
}


void
Engine3D::wheelEvent(QWheelEvent *event)
{
    if (event->delta() > 0)
        _scene->zoomOut();
    else
        _scene->zoomIn();
    updateGL();
}


void
Engine3D::initializeGL()
{
    //_scene = new SceneOGL33(_Meshs, _width, _height);
    _scene = new SceneOGL14(300, 300,300);
    /*if (atof((char*)glGetString(GL_VERSION)) >= 3.0)
     _scene = new SceneOGL33(_Meshs, _width, _height);
     else
     _scene = new SceneOGL14(_Meshs, _width, _height);*/
    _scene->init();
}


void
Engine3D::resize(int width,int height)
{
    this->setFixedWidth(width);
    this->setFixedHeight(height);    
}


void
Engine3D::resizeGL(int width, int height)
{
    _scene->reshape(width, height);
    updateGL();
}


void
Engine3D::paintGL()
{
    _scene->display();
}
