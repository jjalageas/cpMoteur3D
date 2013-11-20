#include "glwidget.h"
#include <unistd.h>

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif


//************************************************************************
//************************************************************************
//Travail dans l'espace 3D
//************************************************************************
//************************************************************************

//--------------------------------------------------------------------
//CONSTRUCTOR DESTRUCTOR
//--------------------------------------------------------------------

GLWidget::GLWidget(QWidget *parent)
    : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    object = 0;
    xRot = 0;
    yRot = 0;
    zRot = 0;
    scale = 0.1f;
    xTrans=yTrans=0.0;
    trolltechGreen = QColor::fromCmykF(0.40, 0.0, 1.0, 0.0);
    trolltechPurple = QColor::fromCmykF(0.39, 0.39, 0.0, 0.0);

    animationTimer.setSingleShot(false);
    connect(&animationTimer, SIGNAL(timeout()), this, SLOT(animate()));
    animationTimer.start(10);

    setAutoFillBackground(false);
}

GLWidget::~GLWidget()
{
    makeCurrent();
    glDeleteLists(object, 1);
}
//--------------------------------------------------------------------
//MOUVEMENT
//--------------------------------------------------------------------

void GLWidget::setParameters(int v_width,int v_height,int v_depth,int vox_w,int vox_h,int vox_d, string name)
{
    vol_width = v_width;
    vol_height=v_height;
    vol_depth= v_depth;
    vox_width= vox_w;
    vox_height= vox_h;
    vox_depth=vox_d;
    vol_size=(vol_width*vol_height*vol_depth);

    x1 = x2 =vol_width ;
    y1 = y2 =vol_height;
    z1 = z2 =vol_depth ;

    z3 = z4 = y3 = y4 = x3 = x4 = 0 ;
    //Point3D_t<int> p1(vol_width/2,vol_depth/2,vol_height/2);
    Point3D_Color_t<float> p0(vol_width/2,vol_depth/2,vol_height/2,1,1,1);
    Primitive=new PrimitiveGL(p0, name);
}

void GLWidget::setListPoints(MiList<Point3D_Color_t<float> *> * pointsList)
{
    _pointsList = pointsList;
    Primitive->setLstPointFromVolume(_pointsList);
}

void GLWidget::setXRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != xRot)
        xRot = angle;
}
void GLWidget::setYRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != yRot)
        yRot = angle;
}
void GLWidget::setZRotation(int angle)
{
    normalizeAngle(&angle);
    if (angle != zRot)
        zRot = angle;
}
void GLWidget::setTranslation( int tx, int ty )
{
    xTrans += tx;
    yTrans += ty;
    //memorise le point pour le ctrl z
    QPoint reverse =QPoint(-tx, -ty);
    reverseTrans.append(reverse);
    updateGL();
}

void GLWidget::initializeGL()
{
    object = makeObject();
}

//--------------------------------------------------------------------
//EVENT
//--------------------------------------------------------------------

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastPos = event->pos();
    if(event->button() == Qt::LeftButton)
    {
        //rien
    }
    else
        event->ignore();
}
void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dx = event->x() - lastPos.x();
    int dy = event->y() - lastPos.y();

    if (event->buttons() & Qt::LeftButton)
    {
        setXRotation(xRot + 8 * dy);
        setYRotation(yRot + 8 * dx);
    }
    else if (event->buttons() & Qt::RightButton)
    {
        setTranslation( dx, dy );
    }
    lastPos = event->pos();
}
void GLWidget::wheelEvent(QWheelEvent *e)
{
    e->delta() > 0 ? scale += scale*0.1f : scale -= scale*0.1f;
    update();
}
void  GLWidget:: keyPressEvent( QKeyEvent *event)
{
    switch(event->key())
    {
        case Qt::Key_Z:
            if(reverseTrans.isEmpty()){
                QMessageBox::warning ( this, "Ctrl Z","vous n'avez pas encore effectué de translation !", QMessageBox::Ok, 0 );
            }
            else{
                while(!reverseTrans.isEmpty()){

                    QPoint a=reverseTrans.last();
                    reverseTrans.pop_back();
                    xTrans += a.x();
                    yTrans += a.y();
                }
            }
        break;
    }
    updateGL ();
}
//--------------------------------------------------------------------
//PAINT EVENT
//--------------------------------------------------------------------

void GLWidget::paintEvent(QPaintEvent *event)
{
    makeCurrent();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glClearColor( 0.0, 0.0, 0.0, 0.0 );

    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_MULTISAMPLE);

    static GLfloat lightPosition[4] = { 0.0, 0.0, 0.0, 0.0 };

    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    setupViewport(width(), height());

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glTranslated(xTrans, yTrans, -10.0);
    glRotated(xRot / 16.0, 1.0, 0.0, 0.0);
    glRotated(yRot / 16.0, 0.0, 1.0, 0.0);
    glRotated(zRot / 16.0, 0.0, 0.0, 1.0);

    glScalef(scale, scale, scale);

    //appelle la liste d objet

    //a chaque refresh on affiche le nouveau volume
    Primitive->draw_xyz_repere();
    Primitive->drawingVolume();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    drawInstructions(&painter);
    painter.end();
}


void GLWidget::setupViewport(int width, int height)
{
    //int side = qMax(width, height);
    //glViewport((width - side) / 2, (height - side) / 2, side, side);
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float ratio = ((double)width)/((double)height);
    glOrtho(-ratio*100/2.0, ratio*100/2.0, -100/2.0, 100/2.0, -100*2.0, 100*2.0);

    glMatrixMode(GL_MODELVIEW);
}



void GLWidget::myPick(const QPoint & posMouse)
{
    double x = posMouse.x();
    double y = posMouse.y();

    cout<<"position Pick "<< x<<", "<<y <<endl;
    int BUFSIZE=1024;
    GLuint selectBuf[BUFSIZE];
    GLint hits;
    GLint viewport[4];

    //On récupère le viewport courant
    glGetIntegerv (GL_VIEWPORT, viewport);

    glSelectBuffer (BUFSIZE, selectBuf);
    glRenderMode (GL_SELECT);

    //Initialisation de la pile des noms
    glInitNames();
    glPushName(0);
    glMatrixMode (GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    /*  create 1.0x1.0 pixel picking region near cursor location */
    gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y),
                   1.0, 1.0, viewport);

    //On doit avoir la même projection en mode sélection qu'en mode rendu :
    float ratio = ((double)vol_width)/((double)vol_height);
    glOrtho(-ratio*100/2.0, ratio*100/2.0,
            -100/2.0, 100/2.0,
            -100*2.,100*2.);

    //drawSquares(GL_SELECT);


    glMatrixMode (GL_PROJECTION);
    glPopMatrix ();

    //On s'assure que les ordres OpenGL sont exécutés
    glFlush();

    hits = glRenderMode (GL_RENDER);
    cout<<"on lance Prohits "<<endl;
    //On traite les sommets cliqués
    processHits(hits, selectBuf); //Fonction appelée ci-dessous
    cout<<" Prohits finit "<<endl;
    updateGL();
}

void GLWidget::processHits (GLint hits, GLuint buffer[])
{
    int numFaceSelected;
    cout<<"hits = "<< hits<<endl;
    if(hits > 0)
    {
        GLuint i, nb_names, name, *ptr;
        GLdouble z1, z2, zInter=0.0;


        cout<<"hits = "<< hits<<endl;
        ptr = (GLuint *) buffer;

        /*  Pour chaque hit (collision)  */
        for (i = 0; i < hits; i++)
        {
            nb_names = ptr[0];
            if (nb_names != 1)
            {
                QMessageBox::critical(this, "Erreur pile noms", "Erreur sur la pile des noms !\nLe programme va quitter.");
                exit(1);
            }

            z1 = (double) ptr[1]/0x7fffffff;
            z2 = (double) ptr[2]/0x7fffffff;

            name = ptr[3];
            ptr +=4;

            /* On ne garde que le nom de l'objet le plus proche (ici on garde le zmin le plus petit) */
            if(i==0 || z1<zInter)
            {
                numFaceSelected = name;
                zInter=z1;
            }
        }

    }
    else
        numFaceSelected = -1; //Nom de face inexistant
}

//-----------------------------------------------------------------
//settings
//-----------------------------------------------------------------

void GLWidget::resizeGL(int width, int height)
{
    setupViewport(width, height);
}

void GLWidget::showEvent(QShowEvent *event)
{
    Q_UNUSED(event);

}

QSize GLWidget::sizeHint() const
{
    return QSize(400, 400);
}

void GLWidget::normalizeAngle(int *angle)
{
    while (*angle < 0)
        *angle += 360 * 16;
    while (*angle > 360 * 16)
        *angle -= 360 * 16;
}

GLuint GLWidget::makeObject()
{
    GLuint list = glGenLists(1);
    glNewList(list, GL_COMPILE);

    glEnable(GL_NORMALIZE);

    glEndList();
    return list;
}

void GLWidget::animate()
{
    update();
}

void GLWidget::drawInstructions(QPainter *painter)
{
    QString text = tr("");
    QFontMetrics metrics = QFontMetrics(font());
    int border = qMax(4, metrics.leading());

    QRect rect = metrics.boundingRect(0, 0, width() - 2*border, int(height()*0.125),
                                      Qt::AlignCenter | Qt::TextWordWrap, text);
    painter->setRenderHint(QPainter::TextAntialiasing);
    painter->fillRect(QRect(0, 0, width(), rect.height() + 2*border),
                      QColor(0, 0, 0, 127));
    painter->setPen(Qt::white);
    painter->fillRect(QRect(0, 0, width(), rect.height() + 2*border),
                      QColor(0, 0, 0, 127));
    painter->drawText((width() - rect.width())/2, border,
                      rect.width(), rect.height(),
                      Qt::AlignCenter | Qt::TextWordWrap, text);
}
























































