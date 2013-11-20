#ifndef GLWIDGET_H
#define GLWIDGET_H

#include "../View/primitiveGl.h"

class QPaintEvent;
class QWidget;

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent = 0);
    ~GLWidget();
    void setParameters(int v_width, int v_height, int v_depth, int vox_w, int vox_h, int vox_d, string name);
    void setListPoints(MiList<Point3D_Color_t<float> *> * pointsList);

    QSize sizeHint() const;
    int xRotation() const { return xRot; }
    int yRotation() const { return yRot; }
    int zRotation() const { return zRot; }
    GLvoid drawingRepere();

public slots:
    void setXRotation(int angle);
    void setYRotation(int angle);
    void setZRotation(int angle);
    void setTranslation( int tx, int ty );

    //activate visualisation
    void showRepere(bool b){REPERE=b;update();}
    void showVolume(bool b){ VOLUME=b;update();}
    void showSkeleton(bool b){ SKELETON=b;update();}
    void showTexture(bool b){TEXTURE=b;update();}
    void showLastNode(bool b){LASTNODE=b;update();}

protected:
    void initializeGL();
    void paintEvent(QPaintEvent *event);
    void resizeGL(int width, int height);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void showEvent(QShowEvent *event);
    void wheelEvent(QWheelEvent *);
    virtual void keyPressEvent( QKeyEvent *event);

private slots:
    void animate();

private:
    GLuint makeObject();

    void drawInstructions(QPainter *painter);
    void normalizeAngle(int *angle);
    void setupViewport(int width, int height);
    inline void centerNScale()
    {
        glScaled( vox_width, vox_height, vox_depth );
        glTranslated( -(x1 + x2)/2.0,
                      -(y1 + y2)/2.0,
                      -(z1 + z2)/2.0 );
    }
    void myPick(const QPoint & posMouse);
    void processHits (GLint hits, GLuint buffer[]);

    GLuint object;
    int xRot;
    int yRot;
    int zRot;
    float scale;
    double xTrans,yTrans;
    //liste des coordonnées pour le ctrl z
    QList<QPoint> reverseTrans;

    //primitive de dessin
    PrimitiveGL* Primitive;
    MiList<Point3D_Color_t<float> *> * _pointsList;

    QPoint lastPos;
    QColor trolltechGreen;
    QColor trolltechPurple;
    QTimer animationTimer;
    int vol_width ;
    int  vol_height;
    int vol_depth ;
    double vox_width, vox_height, vox_depth, vol_size;

    GLdouble x1;
    GLdouble y1;
    GLdouble x2 ;
    GLdouble y2;
    GLdouble x3;
    GLdouble y3;
    GLdouble x4 ;
    GLdouble y4 ;
    GLdouble z1,z2,z3,z4;

    bool REPERE,
    TEXTURE,
    VOLUME,
    SKELETON,
    LASTNODE,
    LABEL,
    SIZE,
    SLICE,
    QUAD;

    bool* VolBool;

    double n1;
    double n2;
    double n3;
};

#endif
