#ifndef VOLUME_VIEWER_H
#define VOLUME_VIEWER_H

#include <QtGui>

#include <GL/glew.h>
#include <QGLWidget>
#include <QtOpenGL>

#include <GL/glu.h>
#include <GL/glut.h>


#include "Struct.h"
//#include "Image2d.hpp"
#include "Image3d.hpp"

//#include <FormManager.h>
//#include <RessourceManager.h>
//#include <InterfaceManager.h>

class InterfaceManager;

#define BUFSIZE 512
#define BUFFER_OFFSET(a) ((char*)NULL + (a))

class VolumeViewer : public QGLWidget
{
       Q_OBJECT

public:

       VolumeViewer(QWidget *parent = 0);
       ~VolumeViewer();

       void clear();
       void enabledPicking(bool flag);
       void setBoundingBox(float width, float height, float depth);

       // VOLUME
       void setVolume(Triplet_t<float *, char *, int> data);
       void setVolumeMesh(MiList<Triangle_t> & triangles);

       // SKELETON
       void setSkeleton(MiList<MiList<Segment> > &branches);
       void setSkeletonVolume(Triplet_t<float *, char *, int> &data);

       // TEXTURES
       void setVolumeTexture(Image2d<int> *texture,
                             Point3D_t<float> minP, Point3D_t<float> maxP);
       void setSkeletonTexture(Image2d<int> *texture,
                               MiList<Point3D_t<float> > &coord);

       // TEXTE
       void setText (MiList<Pair_t<string, Point3D_t<float> > > &text);

public slots:

       // interface manager
       void zoomDefault();
       void zoomIn();
       void zoomOut();
       void centerScene(float, float);
       void rotateScene(float, float);
       void scaleScene(double);

       // Volume control viewer
       void viewBoudingBox(bool);
       void viewTextureVolume(bool);
       void viewTextureSkeleton(bool);
       void volumeViewMode(int);
       void skeletonViewMode(int);

signals:

       void pickBranch(int);
       void clickBranch(int);
       void doubleClickBranch(int);

       void centerSceneChanged(float, float);
       void rotateSceneChanged(float, float);
       void scaleSceneChanged(double);

protected:

       void initializeGL();
       void paintGL();
       void resizeGL(int width, int height);

       void mousePressEvent(QMouseEvent *event);
       void mouseReleaseEvent(QMouseEvent *event);
       void mouseMoveEvent(QMouseEvent *event);
       void mouseDoubleClickEvent(QMouseEvent *event);
       void wheelEvent(QWheelEvent *event);
       void keyPressEvent(QKeyEvent *);
       void keyReleaseEvent(QKeyEvent *);

private:

       void setupActions();
       static void normalizeAngle(int &angle);
       void setRotation(int *rot, int angle);
       void setVBO(Triplet_t<float*,char*,int> &data, GLuint *buffer,
                   int *VBOSize, int *indiceSize);
       void setTexture(Image2d<int> *texture, GLuint *idTexture);
       int picking(int x, int y);

       void drawAxes();
       void drawBoundingBox();
       void drawVolume();
       void drawLines(MiList<Segment> &sList);
       void drawSkeletonWire(bool picking = false);
       void drawSkeleton();
       void drawVolumeTexture();
       void drawSkeletonTexture();
       void drawText();

       InterfaceManager *_interfaceManager;

       int _xRot, _yRot;
       double _scale;
       float _scaleDefault;
       float _xTrans, _yTrans;
       QPoint _lastPos;
       QPoint _clickPos;
       bool _picking;
       int _lastPickHits;
       int _key;

       // BOUNDING BOX
       bool _boundingBoxViewFlag;
       MiList<Point3D_t<float> > _boundingBoxCoord; // Size = 2

       // VOLUME
       uint _volumeModeView;
       GLuint _volumeVBO;
       int _volumeVBOSize, _volumeIndiceSize;
       MiList<Triangle_t> _volumeMesh;

       // SKELETON
       uint _skeletonModeView;
       MiList<MiList<Segment> > _skeletonWire;
       GLuint _skeletonVolVBO;
       int _skeletonVolVBOSize, _skeletonIndiceSize;

       // VOLUME TEXTURE
       GLuint _textureVol;
       MiList<Point3D_t<float> >_textureVolCoord; // Size = 2
       bool _textureVolViewFlag;

       // SKELETON TEXTURE
       GLuint _textureSkel;
       MiList<Point3D_t<float> > _textureSkelCoord; // Size = 4
       bool _textureSkelViewFlag;

       // TEXTE
       MiList<Pair_t<string, Point3D_t<float> > > _text;
};

#endif
