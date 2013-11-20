#include "VolumeViewer.h"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE  0x809D
#endif

/* -------------------------------------------------------------------------------------------------
     CONSTRUCT & DESTRUCT
   -------------------------------------------------------------------------------------------------*/

VolumeViewer::VolumeViewer(QWidget *parent) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
       //RessourceManager::GetInstance()->addRessource("VolumeViewer");

       _interfaceManager = (InterfaceManager *)parent;

       _key = 0;
       _volumeVBOSize = _skeletonVolVBOSize = 0;
       _volumeIndiceSize = _skeletonIndiceSize = 0;
       _textureVolCoord.empty();
       _textureSkelCoord.empty();

       clear();

       setMinimumWidth(450);
       setAutoFillBackground(false);
       setMouseTracking(true);
       setFocusPolicy(Qt::StrongFocus);

       setupActions();
       initializeGL();
}

VolumeViewer::~VolumeViewer()
{
       //RessourceManager::GetInstance()->deleteRessource("VolumeViewer");
       clear();
}

/* -------------------------------------------------------------------------------------------------
     PUBLIC METHODS
   -------------------------------------------------------------------------------------------------*/

void VolumeViewer::clear()
{
       _xRot = _yRot = 0;
       _xTrans = _yTrans = 0.0f;
       _scale = 1.0;
       _picking = false;
       _lastPickHits = -1;

       // BOUNDING BOX
       _boundingBoxViewFlag = false;
       _boundingBoxCoord.empty();

       // VOLUME
       _volumeModeView = 1;
       _volumeMesh.empty();
       if (_volumeVBOSize > 0) glDeleteBuffers(1, &_volumeVBO);
       _volumeVBOSize = _volumeIndiceSize = 0;

       // SKELETON
       _skeletonModeView = 1;
       _skeletonWire.empty();
       if (_skeletonVolVBOSize > 0) glDeleteBuffers(1, &_skeletonVolVBO);
       _skeletonVolVBOSize = _skeletonIndiceSize = 0;

       // VOLUME TEXTURE
       if (_textureVolCoord.size() > 0) glDeleteTextures(1, &_textureVol);
       _textureVolCoord.empty();
       _textureVolViewFlag = false;

       // SKELETON TEXTURE
       if (_textureSkelCoord.size() > 0) glDeleteTextures(1, &_textureSkel);
       _textureSkelCoord.empty();
       _textureSkelViewFlag = false;

       // TEXTE
       _text.empty();
}

void VolumeViewer::enabledPicking(bool flag)
{
       _picking = flag;
}

void VolumeViewer::setBoundingBox(float width, float height, float depth)
{
       Point3D_t<float> p (- width / 2, - height / 2, - depth / 2);
       _boundingBoxCoord.add(p);
       _boundingBoxCoord.add(Point3D_t<float>(-p.x, -p.y, -p.z));

       _scaleDefault = (width > height) ? width : height;
       _scaleDefault = (_scaleDefault > depth) ? _scaleDefault : depth;
       _scaleDefault = 1 / _scaleDefault;

       zoomDefault();
}

// VOLUME

void VolumeViewer::setVolume (Triplet_t<float*,char*,int> data)
{
       setVBO (data, &_volumeVBO, &_volumeVBOSize, &_volumeIndiceSize);
       updateGL();
}

void VolumeViewer::setVolumeMesh (MiList<Triangle_t> & triangles)
{
       _volumeMesh.empty();
       for (int i=0 ; i < triangles.size() ; i++)
       {
              _volumeMesh.add(triangles.get(i));
       }
       updateGL();
}

// SKELETON

void VolumeViewer::setSkeleton (MiList<MiList<Segment> > &branches)
{
       _skeletonWire.empty();
       int size = branches.size();
       for (int i=0 ; i < size ; i++)
              _skeletonWire.add(branches.get(i));

       updateGL();
}

void VolumeViewer::setSkeletonVolume(Triplet_t<float *, char *, int> &data)
{
       setVBO (data, &_skeletonVolVBO, &_skeletonVolVBOSize, &_skeletonIndiceSize);
       updateGL();
}

// TEXTURES

void VolumeViewer::setVolumeTexture (Image2d<int> *texture,
                                     Point3D_t<float> minP, Point3D_t<float> maxP)
{
       if (_textureVolCoord.size() != 0) glDeleteTextures(1, &_textureVol);
       _textureVolCoord.empty();

       if (texture != NULL)
       {
              setTexture (texture, &_textureVol);
              _textureVolCoord.add(minP);
              _textureVolCoord.add(maxP);
       }

       updateGL();
}

void VolumeViewer::setSkeletonTexture(Image2d<int> *texture,
                                      MiList<Point3D_t<float> > &coord)
{
       if (_textureSkelCoord.size() != 0) glDeleteTextures(1, &_textureSkel);
       _textureSkelCoord.empty();

       if ( (texture != NULL) && (coord.size() == 4) )
       {
              setTexture (texture, &_textureSkel);
              for (int i=0 ; i < 4 ; i++)
                     _textureSkelCoord.add(coord.get(i));
       }
       updateGL();
}

// TEXTE

void VolumeViewer::setText(MiList<Pair_t<string, Point3D_t<float> > > &text)
{
       _text.empty();

       if (text.size() > 0)
       {
              _text = text;
       }
}

/* -------------------------------------------------------------------------------------------------
     PUBLIC SLOTS
   -------------------------------------------------------------------------------------------------*/

void VolumeViewer::zoomDefault() {
       _scale = _scaleDefault;
       updateGL();
}

void VolumeViewer::zoomIn() {
       _scale *= 1.25;
       updateGL();
}

void VolumeViewer::zoomOut() {
       _scale *= 0.8;
       updateGL();
}

void VolumeViewer::centerScene(float centerX, float centerY)
{
       if ( (centerX != _xTrans) || (centerY != _yTrans) )
       {
              _xTrans = centerX;
              _yTrans = centerY;
              updateGL();
       }
}

void VolumeViewer::rotateScene(float xr, float yr)
{
       _xRot = xr; _yRot = yr;
       updateGL();
}

void VolumeViewer::scaleScene(double zoom)
{
       _scale = zoom;
       updateGL();
}

void VolumeViewer::viewBoudingBox(bool flag) {
       _boundingBoxViewFlag = flag;
       updateGL();
}

void VolumeViewer::viewTextureVolume(bool flag) {
       _textureVolViewFlag = flag;
       updateGL();
}

void VolumeViewer::viewTextureSkeleton(bool flag) {
       _textureSkelViewFlag = flag;
       updateGL();
}

void VolumeViewer::volumeViewMode(int mode) {
       _volumeModeView = mode;
       updateGL();
}

void VolumeViewer::skeletonViewMode(int mode) {
       _skeletonModeView = mode;
       updateGL();
}

/* -------------------------------------------------------------------------------------------------
     PROTECTED METHODS
   -------------------------------------------------------------------------------------------------*/

void VolumeViewer::initializeGL()
{
       glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
       glClearDepth(1.0);
       glLineWidth(1.6);

       //VBO
       glewInit();

       glEnable(GL_DEPTH_TEST);
       glDepthFunc(GL_LEQUAL);
       glEnable(GL_COLOR_MATERIAL);
       glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
       glShadeModel(GL_FLAT);

       float lightDiffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
       float lightAmbient[] = {0.2f, 0.2f, 0.2f, 1.0f};
       float lightPosition[] = {10.0f, 1.0f, 20.0f, 1.0f};
       float lightSpecular[] = {0.5f, 0.5f, 0.5f, 1.0f};

       glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmbient);
       glLightfv(GL_LIGHT0, GL_DIFFUSE, lightDiffuse);
       glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpecular);
       glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

       int MatSpec [4] = {1,1,1,1};
       glMaterialiv(GL_FRONT_AND_BACK,GL_SPECULAR,MatSpec);
       glMateriali(GL_FRONT_AND_BACK,GL_SHININESS,100);

       //glEnable(GL_LIGHTING); // Active l'éclairage
       //glEnable(GL_LIGHT0);
       glEnable(GL_NORMALIZE);
}

void VolumeViewer::paintGL()
{
       glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glMatrixMode (GL_MODELVIEW);
       glLoadIdentity ();

       // Draw repère

       //float dx = -0.5f - width/4000;
       //float dy = -0.405f  - height/9000;
//       float dx = -0.5f;
//       float dy = -0.5f;
//       glTranslatef (dx, dy, -7.0f);
//       glRotatef  (_xRot / 16.0, 1.0, 0.0, 0.0);
//       glRotatef (_yRot / 16.0, 0.0, 1.0, 0.0);

       //drawAxes();

       //drawText();

       // Prepare scene

       glLoadIdentity ();

       glTranslatef (_xTrans/2, _yTrans/2, -10.0f );
       glRotatef  (_xRot / 16.0, 1.0, 0.0, 0.0);
       glRotatef (_yRot / 16.0, 0.0, 1.0, 0.0);
       glScalef (_scale, _scale, _scale);

       // Draw scene

       drawBoundingBox();
glFlush();
       drawVolumeTexture();
glFlush();
       drawSkeletonTexture();
glFlush();
       drawVolume();
glFlush();
       drawSkeleton();

       glFlush();
}

void VolumeViewer::resizeGL(int width, int height)
{
       glViewport(0, 0, width, height);
       glMatrixMode(GL_PROJECTION);
       glLoadIdentity();
       QSize size = this->size();
       gluPerspective(10.0f, (GLdouble)size.width()/(GLdouble)size.height(), 0.01f, 10000.0f);
       glMatrixMode(GL_MODELVIEW);
}

void VolumeViewer::mousePressEvent(QMouseEvent *event)
{
       _lastPos = event->pos();
       _clickPos = event->pos();
}

void VolumeViewer::mouseReleaseEvent(QMouseEvent *event)
{
       if ( (event->pos() == _clickPos) && _picking)
       {
              emit clickBranch(picking(event->x(), event->y()));
       }
}

void VolumeViewer::mouseMoveEvent(QMouseEvent *event)
{
       int dx = event->x() - _lastPos.x();
       int dy = event->y() - _lastPos.y();

       // left button
       if ( (event->buttons() == Qt::LeftButton) && (_key == Qt::Key_Control) )
       {
              setRotation(&_xRot, _xRot + 8 * dy);
              setRotation(&_yRot, _yRot + 8 * dx);
              emit rotateSceneChanged(_xRot, _yRot);
       }
       // right button
       else if ( (event->buttons() == Qt::RightButton) && (_key == Qt::Key_Control) )
       {
              _xTrans += dx * _scale;
              _yTrans -= dy * _scale;
              emit centerSceneChanged(_xTrans, _yTrans);
       }
       // no button & picking
       else if ( (event->button() == Qt::NoButton) && _picking)
       {
              emit pickBranch(picking(event->x(), event->y()));
       }

       _lastPos = event->pos();
       updateGL();
}

void VolumeViewer::mouseDoubleClickEvent(QMouseEvent *event)
{
       int pick = picking(event->x(), event->y());
       if (pick != _lastPickHits)
       {
              _lastPickHits = pick;
              emit doubleClickBranch(_lastPickHits);
       }
}

void VolumeViewer::wheelEvent(QWheelEvent *event)
{
       // Zoom
       if (_key == Qt::Key_Control)
       {
              if (event->delta() > 0)
                     _scale *= 1.1; //zoom in
              else
                     _scale *= 0.9; //zoom out
              updateGL();
              emit scaleSceneChanged(_scale);
       }
       // Change slices
       else if (_textureVolViewFlag)
       {
              QSpinBox *sliceQSB = _interfaceManager->getSliceQSB();
               if (event->delta() > 0)
                      sliceQSB->stepUp();
               else
                      sliceQSB->stepDown();
       }
}

void VolumeViewer::keyPressEvent(QKeyEvent *event)
{
       _key = event->key();
       event->accept();
}

void VolumeViewer::keyReleaseEvent(QKeyEvent *event)
{
       _key = 0;
       event->accept();
}

/* -------------------------------------------------------------------------------------------------
     PRIVATE METHODS
   -------------------------------------------------------------------------------------------------*/

void VolumeViewer::setupActions()
{
       // Interface manager
       connect (_interfaceManager, SIGNAL(zoomIn()), this, SLOT(zoomIn()));
       connect (_interfaceManager, SIGNAL(zoomOut()), this, SLOT(zoomOut()));
       connect (_interfaceManager, SIGNAL(zoomDefault()), this, SLOT(zoomDefault()));

       connect (_interfaceManager, SIGNAL(viewBoundingBox(bool)), this, SLOT(viewBoudingBox(bool)));
       connect (_interfaceManager, SIGNAL(centerScene3DChanged(float,float)), this,
                SLOT(centerScene(float,float)));

       // Volume control viewer
       VolumeControlViewer *VCV = _interfaceManager->getVolumeControlViewer();
       connect (VCV, SIGNAL(viewVolumeType(int)), this, SLOT(volumeViewMode(int)));
       connect (VCV, SIGNAL(viewSkeletonType(int)), this, SLOT(skeletonViewMode(int)));
       connect (VCV, SIGNAL(textureVolumeEnabled(bool)), this, SLOT(viewTextureVolume(bool)));
       connect (VCV, SIGNAL(textureSSEnabled(bool)), this, SLOT(viewTextureSkeleton(bool)));
}

void VolumeViewer::normalizeAngle(int &angle)
{
       while (angle < 0)
              angle += 360 * 16;
       while (angle > 360 * 16)
              angle -= 360 * 16;
}

void VolumeViewer::setRotation(int *rot, int angle)
{
       normalizeAngle(angle);
       if (angle != *rot)
       {
              *rot = angle;
       }
}

void VolumeViewer::setVBO (Triplet_t<float*,char*,int> &data,
                           GLuint *buffer, int *VBOSize, int *indicesSize)
{
       // Supprime la mémoire si déjà allouée
      // if (*VBOSize > 0) glDeleteBuffers(1, buffer);
       *VBOSize = 0;
       *indicesSize = 0;

       if (data.third > 0)
       {
              // Tailles pour les VBO
              int size = data.third;
              int indiceSize = 3 * size * sizeof(float);
              int colorSize = 3 * size * sizeof(char);

              // Créer un nouvel buffer object
              glGenBuffers (1, buffer);

              // Sélection du buffer object
              glBindBuffer (GL_ARRAY_BUFFER, *buffer);

              // Allocation de l'espace mémoire
              glBufferData (GL_ARRAY_BUFFER , indiceSize + colorSize, 0, GL_DYNAMIC_DRAW);

              // Copie des données sur la mémoire serveur
              glBufferSubData (GL_ARRAY_BUFFER, 0, indiceSize, data.first);
              glBufferSubData (GL_ARRAY_BUFFER, indiceSize, colorSize, data.second);

              *VBOSize = size;
              *indicesSize = indiceSize;
       }
}

void VolumeViewer::setTexture(Image2d<int> *texture, GLuint *idTexture)
{
       int width = texture->getWidth();
       int height = texture->getHeight();
       int size = width * height;
       GLubyte *imageTexture = new GLubyte[size * 4];

       int j=0;
       for (int i=0 ; i < size ; i++)
       {
              int data = texture->getData(i);
              imageTexture[j] = (GLubyte)data; j++;
              imageTexture[j] = (GLubyte)data; j++;
              imageTexture[j] = (GLubyte)data; j++;
              imageTexture[j] = (GLubyte)255; j++;
       }
       // Créer un nouvel buffer object
       glGenTextures(1, idTexture);

       // Sélection du buffer object
       glBindTexture(GL_TEXTURE_2D, *idTexture);

       // Allocation de l'espace mémoire + copie de l'image
       glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
                     GL_UNSIGNED_BYTE, imageTexture);

       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
       glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

       delete []imageTexture;
}

int VolumeViewer::picking (int x, int y)
{
       GLuint selectBuf[BUFSIZE];
       GLint viewport[4];

       glGetIntegerv(GL_VIEWPORT, viewport);

       glSelectBuffer(BUFSIZE, selectBuf);
       (void) glRenderMode(GL_SELECT);

       glInitNames();
       glPushName(0);

       glMatrixMode(GL_PROJECTION);
       glPushMatrix();
       glLoadIdentity();

       gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);
       gluPerspective (10.0f, (GLdouble)size().width()/(GLdouble)size().height(), 0.01f, 10000.0f);

       drawSkeletonWire(true);

//       glLoadName(666666);
//       drawVolumeTexture();

//       glLoadName(777777);
//       drawSkeletonTexture();

       glPopMatrix ();
       glPopName();
       glFlush();

       GLint hits = glRenderMode(GL_RENDER);

       int res = -1;
       if (hits > 0)
       {
              GLuint *ptr = (GLuint *) selectBuf;
              ptr+=3;
              res = (int)*ptr;
       }

       return res;
}

/* -------------------------------------------------------------------------------------------------
     DRAW METHODS
   -------------------------------------------------------------------------------------------------*/

void VolumeViewer::drawAxes()
{
       float longueur = 0.1;
       float diamCylindre = 1.0 / 30.0;
       float diamCone = diamCylindre * 3;
       int radius = 50;
       GLUquadric* quad = gluNewQuadric();

       // Axe X
       glColor3d(1.0,0.0,0.0);
       glPushMatrix();
       glRotatef(90.,0.0,1.0,0.0);
       gluCylinder(quad, longueur*diamCylindre, longueur*diamCylindre, 0.8*longueur, radius, radius);
       glTranslatef(0.0,0.0,0.8*longueur);
       gluCylinder(quad, longueur*diamCone, 0.0, 0.2*longueur, radius, radius);
       glPopMatrix();
       // Axe Y
       glColor3d(0.0,1.0,0.0);
       glPushMatrix();
       glRotatef(-90.,1.0,0.0,0.0);
       gluCylinder(quad, longueur*diamCylindre, longueur*diamCylindre, 0.8*longueur, radius, radius);
       glTranslatef(0.0,0.0,0.8*longueur);
       gluCylinder(quad, longueur*diamCone, 0.0, 0.2*longueur, radius, radius);
       glPopMatrix();
       // Axe Z
       glColor3d(0.0,0.0,1.0);
       glPushMatrix();
       gluCylinder(quad, longueur*diamCylindre, longueur*diamCylindre, 0.8*longueur, radius, radius);
       glTranslatef(0.0,0.0,0.8*longueur);
       gluCylinder(quad, longueur*diamCone, 0.0, 0.2*longueur, radius, radius);
       glPopMatrix();
}

void VolumeViewer::drawBoundingBox()
{
       if (_boundingBoxViewFlag && _boundingBoxCoord.size() == 2)
       {
              glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
              glColor3f(255, 255, 255);
              glBegin(GL_QUADS);

              Point3D_t<float> &min = _boundingBoxCoord.getRef(0);
              Point3D_t<float> &max = _boundingBoxCoord.getRef(1);

              /* front face */
              glVertex3f (min.x, min.y, min.z);
              glVertex3f (max.x, min.y, min.z);
              glVertex3f (max.x, max.y, min.z);
              glVertex3f (min.x, max.y, min.z);
              /* back face */
              glVertex3f (min.x, min.y, max.z);
              glVertex3f (max.x, min.y, max.z);
              glVertex3f (max.x, max.y, max.z);
              glVertex3f (min.x, max.y, max.z);
              /* left face */
              glVertex3f (min.x, min.y, min.z);
              glVertex3f (min.x, min.y, max.z);
              glVertex3f (min.x, max.y, max.z);
              glVertex3f (min.x, max.y, min.z);
              /* right face */
              glVertex3f (max.x, min.y, min.z);
              glVertex3f (max.x, min.y, max.z);
              glVertex3f (max.x, max.y, max.z);
              glVertex3f (max.x, max.y, min.z);

              glEnd();
              glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
       }
}

void VolumeViewer::drawVolume()
{
       switch (_volumeModeView)
       {
       case 0 : // None
              break;
       case 1 : // All points
       case 2 : // Surface Point
              if ( (_volumeVBOSize > 0) && (_volumeIndiceSize > 0) )
              {

                     glBindBuffer(GL_ARRAY_BUFFER, _volumeVBO);

                     glVertexPointer (3, GL_FLOAT, 0, BUFFER_OFFSET(0));
                     glColorPointer (3, GL_UNSIGNED_BYTE, 0, BUFFER_OFFSET(_volumeIndiceSize));

                     glEnableClientState (GL_VERTEX_ARRAY);
                     glEnableClientState (GL_COLOR_ARRAY);

                     glDrawArrays(GL_POINTS, 0, _volumeVBOSize);

                     glDisableClientState (GL_COLOR_ARRAY);
                     glDisableClientState (GL_VERTEX_ARRAY);
              }
              break;
       case 3 :
              {
                     int size = _volumeMesh.size();
                     if (size > 0)
                     {
                            glColor4ub (255, 50, 50, 170);
                            glBegin(GL_TRIANGLES);

                            for (int i=0 ; i < size ; i++)
                            {
                                   Triangle_t &t = _volumeMesh.getRef(i);

                                   glNormal3f (t.normal.x, t.normal.y, t.normal.z);
                                   glVertex3f (t.first.x, t.first.y, t.first.z);
                                   glVertex3f (t.second.x, t.second.y, t.second.z);
                                   glVertex3f (t.third.x, t.third.y, t.third.z);
                            }
                            glEnd();
                     }
              }
              break;
       }
}

void VolumeViewer::drawLines(MiList<Segment> &sList)
{
       int size = sList.size();
       glBegin(GL_LINES);
       for (int i=0 ; i < size ; i++)
       {
              Segment &s = sList.getRef(i);
              glColor4ub(s.color.Red(), s.color.Green(), s.color.Blue(), s.color.Alpha());

              glVertex3f (s.src.x, s.src.y, s.src.z);
              glVertex3f (s.trg.x, s.trg.y, s.trg.z);
       }
       glEnd();

}

void VolumeViewer::drawSkeletonWire(bool picking)
{
       int branchesSize = _skeletonWire.size();
       if (branchesSize > 0)
       {
              // branches
              for (int i=0 ; i < branchesSize ; i++)
              {
                     if (picking)
                            glLoadName(i);
                     drawLines(_skeletonWire.getRef(i));
              }
       }
}

void VolumeViewer::drawSkeleton()
{
       // Skeleton wire
       if ( (_skeletonModeView == 1) || (_skeletonModeView == 3) )
       {
              drawSkeletonWire();
       }
       // Skeleton volume
       if ( (_skeletonModeView == 2) || (_skeletonModeView == 3) )
       {
              if ( (_skeletonVolVBOSize > 0) && (_skeletonIndiceSize > 0) )
              {
                     glBindBuffer(GL_ARRAY_BUFFER, _skeletonVolVBO);

                     glVertexPointer (3, GL_FLOAT, 0, BUFFER_OFFSET(0));
                     glColorPointer (3, GL_UNSIGNED_BYTE, 0, BUFFER_OFFSET(_skeletonIndiceSize));

                     glEnableClientState (GL_VERTEX_ARRAY);
                     glEnableClientState (GL_COLOR_ARRAY);

                     glDrawArrays(GL_POINTS, 0, _skeletonVolVBOSize);

                     glDisableClientState (GL_COLOR_ARRAY);
                     glDisableClientState (GL_VERTEX_ARRAY);
              }
       }
}

void VolumeViewer::drawVolumeTexture()
{
       if (_textureVolViewFlag
           && (_textureVolCoord.size() == 2) )
       {
              glColor3f(1, 1, 1);
              glEnable(GL_TEXTURE_2D);
              glBindTexture(GL_TEXTURE_2D, _textureVol);

              Point3D_t<float> &min = _textureVolCoord.getRef(0);
              Point3D_t<float> &max = _textureVolCoord.getRef(1);

              glBegin (GL_QUADS);

              glTexCoord2i (0,0);
              glVertex3i (min.x, min.y, min.z);

              glTexCoord2i (1,0);
              glVertex3i (max.x, min.y, min.z);

              glTexCoord2i (1,1);
              glVertex3i (max.x, min.y, max.z);

              glTexCoord2i (0,1);
              glVertex3i (min.x, min.y, max.z);

              glEnd();

              glDisable(GL_TEXTURE_2D);
       }
}

void VolumeViewer::drawSkeletonTexture()
{
       if (_textureSkelViewFlag
           && (_textureSkelCoord.size() == 4) )
       {
              glColor3f(1, 1, 1);
              glEnable (GL_TEXTURE_2D);
              glBindTexture (GL_TEXTURE_2D, _textureSkel);

              glBegin(GL_QUADS);

              Point3D_t<float> &p = _textureSkelCoord.getRef(0);
              glTexCoord2i (0,0);
              glVertex3i (p.x, p.y, p.z);

              p = _textureSkelCoord.getRef(1);
              glTexCoord2i(1,0);
              glVertex3i (p.x, p.y, p.z);

              p = _textureSkelCoord.getRef(2);
              glTexCoord2i (1,1);
              glVertex3i (p.x, p.y, p.z);

              p = _textureSkelCoord.getRef(3);
              glTexCoord2i (0,1);
              glVertex3i (p.x, p.y, p.z);

              glEnd();

              glDisable (GL_TEXTURE_2D);
       }
}

void VolumeViewer::drawText()
{
       if ( _text.size() > 0)
       {
              QFont font;
              font.setStyleHint(QFont::SansSerif);
              font.setPixelSize(10);

              glColor4ub(255, 255, 0, 255);
              int textSize = _text.size();
              for (int i=0 ; i < textSize ; i++)
              {
                     //cout << _text.getRef(i).first << endl;
              }
       }
}
