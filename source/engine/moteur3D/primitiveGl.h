#ifndef PRIMITIVEGL_H
#define PRIMITIVEGL_H

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <math.h>

#include "../Model/Examen.h"

//qt & gl
#include <GL/glew.h>
#include <QtGui>
#include <QtOpenGL>
#include <GL/glu.h>

#include <QGLWidget>
#include <QBrush>
#include <QFont>
#include <QImage>
#include <QPen>
#include <QTimer>

using namespace std;

class PrimitiveGL {

public:

    //PrimitiveGL(Point3D_t<int> p){p1.x=p.x;p1.y=p1.y;p1.z=p.z;}
    //added
    PrimitiveGL(Point3D_Color_t<float> p, string name)
    {
        p0.x=p.x;
        p0.y=p1.y;
        p0.z=p.z;

        p0.Red(p.Red());
        p0.Green(p.Green());
        p0.Blue(p.Blue());

        _name = name;
    }

    Point3D_Color_t<float>  RepereOpenGl2(Point3D_Color_t<float> A);

    //end
    ~PrimitiveGL(){;}

    //void setLstPointFromVolume(ImageSequence<char>*mask);
    bool setLstPointFromVolume(MiList<Point3D_Color_t<float> *> *list);
    void setLstPointFromNode(MiList<Node *> nodes);

    //Point3D_t<int> RepereOpenGl(Point3D_t<int> A);

    GLvoid copyScreen(const string &filename);
    GLvoid draw_xyz_repere();
    GLvoid drawLine(MiList<Point3D_t<int> >* Line);
    GLvoid drawingVolume();
    GLvoid drawLstNode();
    void drawScene(GLenum mode);
    void drawSceneTest(GLenum mode) ;

    //activate visualisation
    void showRepere(bool b){REPERE=b;}
    void showVolume(bool b){VOLUME=b;}
    void showSkeleton(bool b){ SKELETON=b;}
    void showTexture(bool b){TEXTURE=b;}
    void showLastNode(bool b){LASTNODE=b;}

private:

    QColor trolltechGreen;
    QColor trolltechPurple;
    //booleen de gestion d affichage
    bool REPERE,
    TEXTURE,
    VOLUME,
    SKELETON,
    LASTNODE,
    LABEL,
    SIZE,
    SLICE,
    QUAD;
    Point3D_t<int> p1;
    MiList<Point3D_t<int> >* _volume;
    //added
    Point3D_Color_t<float> p0;
    MiList<Point3D_Color_t<float> > * _vol;
    //end
    MiList<Point3D_t<int> >* _nodes;
    MiList<Point3D_t<int> >* _branches;

    //pour donner un nom au capture d'ecran
    string _name;
};


#endif
