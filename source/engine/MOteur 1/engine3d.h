#ifndef ENGINE3D_H
#define ENGINE3D_H



#include "scene.h"

//MODEL
#include <Image3D1C.hpp>
#include <Mesh.hpp>
#include <View2DContainer.hpp>


//QT
#include <QtGui>
#include <QKeyEvent>
#include <QGLWidget>

class  Engine3D : public QGLWidget
{
    Q_OBJECT
    public:
        enum MouseMode { TRACKBALL = 0, PICKING };
        Engine3D(QWidget *parent = 0);

        void resize(int width,int height);

        //Dans le cas ou on a qu'un mesh tout seul
        void setData(Mesh * Meshs);
        //dans le cas ou on part d'un type 3D
        void setData(Mesh * Meshs, View2DContainer* All2DViews,
                     int widthBoundingBox,int heightBoundingBox,int depthBoundingBox);

        void initializeGL() ;
        void resizeGL(int width, int height) ;
        void paintGL() ;

        void keyPressEvent(QKeyEvent *keyEvent);
        void mouseMoveEvent(QMouseEvent *event);
        void mousePressEvent(QMouseEvent *event);
        void wheelEvent(QWheelEvent *event);

        inline Scene *getScene() { return this->_scene; }

        inline MouseMode getMouseMode() { return _mouseMode; }
        inline void setMouseMode(MouseMode mode) { _mouseMode = mode; }

    private:
        Scene *_scene;
        Mesh *_Meshs;
        MouseMode _mouseMode;
        int _width, _height;
};




#endif // ENGINE3D_H
