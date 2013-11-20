#include "scene.h"
//*******************************************************************************************
//*******************************************************************************************
//
//Interface(au sens programmation)
//
//*******************************************************************************************
//*******************************************************************************************

Scene::Scene(int width, int height, int depth)
: _width(width), _height(height), _zoom(300.0), _rotx(0.0), _roty(0.0),
_box(new BoundingBox(width,height,depth)), _renderMode(PLOT)
{
    _Meshs=NULL;
    _Objets2D=NULL;
    _resXVoxel=1;
    _resYVoxel=1;
    _resZVoxel=1;
    
    if(_box->getZMax()<0)
        _zoom=-300.0;
    
    //_box->Display();
}


void
Scene::setData(Mesh * Meshs){
    
    _Meshs=Meshs;
    // _box->Display();
    _box->setSizeFromMesh(Meshs);
    if(_box->getZMax()<0)
        _zoom=-300.0;
}



void Scene::setData(Mesh * Meshs, View2DContainer* All2DViews,int widthBoundingBox,int heightBoundingBox,int depthBoundingBox){
    
    _Meshs=Meshs;
    
    _Objets2D=All2DViews;

    if(_box!=NULL)
    _box->setSize(widthBoundingBox,heightBoundingBox,depthBoundingBox);
    else{
        _box=new BoundingBox(widthBoundingBox,heightBoundingBox,depthBoundingBox);
    }

    if(_box->getZMax()<0)
        _zoom=-300.0;
    
}

Scene::~Scene()
{
    
}

void Scene::reshape(int width, int height)
{
    if(height == 0)
        height = 1;
    glViewport(0, 0, width, height);
}

void Scene::mouseMotion(int x, int y)
{
    _rotx += (y - _lasty)*1.0f;
    _roty += (x - _lastx)*1.0f;
    _lastx = x;
    _lasty = y;
}



//*******************************************************************************************
//*******************************************************************************************
//
//OPENGL version 14
//
//*******************************************************************************************
//*******************************************************************************************


SceneOGL14::SceneOGL14( int width, int height,int depth)
: Scene( width, height, depth),
_cam(new Camera())
{
    _Meshs=NULL;
    _Objets2D=NULL;
    _textureVolViewFlag=0;
    
    _textureVolCoordF.empty();
    _textureVolCoordS.empty();
    _textureVolCoordT.empty();
}

SceneOGL14::~SceneOGL14() {
    // VOLUME TEXTURE
    if (_textureVolViewFlag==1){
        glDeleteTextures(1, &_textureVolF);
        glDeleteTextures(1, &_textureVolS);
        glDeleteTextures(1, &_textureVolT);
        
        _textureVolCoordT.empty();
        _textureVolCoordF.empty();
        _textureVolCoordS.empty();
        _textureVolViewFlag = false;
    }
}


//premiere fois
void SceneOGL14::setData(Mesh * Meshs, View2DContainer* All2DViews,int widthBoundingBox,int heightBoundingBox,int depthBoundingBox){
    _Meshs=Meshs;
    _Objets2D=All2DViews;
    _box->setSize(widthBoundingBox,heightBoundingBox,depthBoundingBox);
    
    display();
    
    
}

//update Image2D et Profils
void SceneOGL14::UpdateContainer(){
    display();
    
}



void SceneOGL14::display()
{
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // std::cout<<"SceneOGL14::display()_Meshs: "<<_Meshs<<std::endl;
    //std::cout<<"SceneOGL14::display(): cam="<<_cam <<std::endl;
    
    
    if(_Meshs != NULL){
        if(_Meshs->is3D()){
            _cam->setEye(Vec3f(_box->getXCenter(), _box->getYMax(), _box->getZMin() - _box->getZCenter()));
            _cam->setTarget(Vec3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter()));
            _cam->glSet();
        }
    }
    if(_Objets2D != NULL){
        _cam->setEye(Vec3f(_box->getXCenter(), _box->getYCenter(),  _box->getZCenter()-400));
        _cam->setTarget(Vec3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter()));
        _cam->glSet();
    }
    else{
        _cam->setEye(Vec3f(_box->getXCenter(), _box->getYMax(), _box->getZMin() - _box->getZCenter()));
        _cam->setTarget(Vec3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter()));
        _cam->glSet();
    }
    
    //std::cout<<"  display:: cam display: "<<std::endl;
    //_cam->Display();
    
    Matrix4x4<GLfloat> mat;
    //std::cout<<"   display:: Zoom: "<<_zoom<<std::endl;
    
    mat.setTranslate(location[0] + _box->getXCenter(),
                     location[1] + _box->getYCenter(),
                     location[2] + _box->getZCenter() + _zoom);
    
    //std::cout<<"    display:: Location matrix: "<<location[0]<<", "<<location[1] <<", "<<location[2]<<std::endl;
    
    //std::cout<<"   display::  Position: "<<location[0] + _box->getXCenter()<<", "
      //      <<location[1] + _box->getYCenter()<<", "<<location[2] + _box->getZCenter() + _zoom<<std::endl;
    
    glMultMatrixf(mat);
    glRotated(_rotx, 1., 0., 0.);
    glRotated(_roty, 0., 0., 1.);
    mat.setTranslate(-_box->getXCenter(),_box->getYCenter(), -_box->getZCenter());
    glMultMatrixf(mat);
    //std::cout<<"  display:: draw: "<<std::endl;
    
    draw();
}


void SceneOGL14::init()
{
    float value=0.95;
    glClearColor(value,value,value, 0.0);
    glEnable(GL_DEPTH_TEST);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glDisable(GL_BLEND);
    
    glShadeModel(GL_SMOOTH);
    glViewport(0, 0, _width, _height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, ((double)_width/(double)_height), 0.01, 10000.0);
    glMatrixMode(GL_MODELVIEW);
}

void SceneOGL14::updateIntensity() { }





//*****************************************************************************
//---------------------------------------
//                           Creation TEXTUREs
//---------------------------------------
//*****************************************************************************

//---------------------------------------
//Creation TEXTURE (source image 3D)
//---------------------------------------

void SceneOGL14::TranscribeDatasFromContainer(){
    
    //recuperation de la taille
    Triplet_t<int,int,int>* triplet=this->_box->getSizes();
    int width=triplet->first;
    int height=triplet->second;
    int depth=triplet->third;
    delete triplet;
    
    //recuperation des index images
    Point3D_t<int>*p=_Objets2D->getIndexImages();
    int indexT=p->x;
    int indexF=p->y;
    int indexS=p->z;
    delete p;
    
    //Calcul de MinP, MinA pour Transverse
    float xMaxT = (float)width / 2 * _resXVoxel;
    float yMaxT = - (float)(depth / 2 - indexT ) * _resZVoxel;
    float zMaxT = (float)height / 2 * _resYVoxel;
    Point3D_t<float> minT, maxT;
    minT = Point3D_t<float>(-xMaxT, -yMaxT, -zMaxT);
    maxT = Point3D_t<float>(xMaxT, yMaxT, zMaxT);
    
    
    
    //Calcul de MinP, MinA pour Frontale
    float xMaxF = (float)(width / 2 )* _resXVoxel;
    float yMaxF = - (float)(depth / 2 ) * _resZVoxel;
    float zMaxF = (float)(height / 2 - indexF)* _resYVoxel;
    Point3D_t<float> minF, maxF;
    minF = Point3D_t<float>(-xMaxF, -yMaxF, -zMaxF);
    maxF = Point3D_t<float>(xMaxF, yMaxF, zMaxF);
    
    
    //Calcul de MinP, MinA pour Sagitale
    float xMaxS = (float)(width / 2 - indexS)* _resXVoxel;
    float yMaxS = - (float)( depth/ 2 ) * _resZVoxel;
    float zMaxS = (float)(height / 2 )* _resYVoxel;
    Point3D_t<float> minS, maxS;
    minS = Point3D_t<float>(-xMaxS, -yMaxS, -zMaxS);
    maxS = Point3D_t<float>(xMaxS, yMaxS, zMaxS);
    
    
    //copie des images
    
    Image2D1C<float>* transverse=this->_Objets2D->getImageZ();
    Image2D1C<float>* frontal=this->_Objets2D->getImageY();
    Image2D1C<float>* sagital=this->_Objets2D->getImageX();
    
    
    //recherches des maxima
    transverse->updateExtrema();
    frontal->updateExtrema();
    sagital->updateExtrema();
    
    //calcul du contrast automatique
    Image2D1C<int> *textureTransverse = ModelTranscriber::FromImage(transverse,255);
    Image2D1C<int> *textureFrontal = ModelTranscriber::FromImage(frontal,255);;
    Image2D1C<int> *textureSagital = ModelTranscriber::FromImage(sagital,255) ;
    
    
    //envoie au moteur OpenGl
    SetDataTranscribedToTextures(textureTransverse,textureFrontal,textureSagital, minT, maxT,minF, maxF,minS, maxS);
    
    //nettoie
    
    delete textureTransverse;
    delete textureFrontal;
    delete textureSagital;
    
}

void SceneOGL14::SetDataTranscribedToTextures( Image2D1C<int> *textureT,Image2D1C<int> *textureF,Image2D1C<int> *textureS,
                                              Point3D_t<float> minT, Point3D_t<float> maxT, Point3D_t<float> minF, Point3D_t<float>  maxF, Point3D_t<float> minS, Point3D_t<float>  maxS)
{
    
    
    if (_textureVolCoordT.size() != 0){
        glDeleteTextures(1, &_textureVolT);
        glDeleteTextures(1, &_textureVolF);
        glDeleteTextures(1, &_textureVolS);
    }
    
    _textureVolCoordT.empty();
    _textureVolCoordF.empty();
    _textureVolCoordS.empty();
    
    if (textureT != NULL)
    {
        setTexture(textureT, &_textureVolT);
        _textureVolCoordT.add(minT);
        _textureVolCoordT.add(maxT);
    }
    
    if (textureF != NULL)
    {
        setTexture(textureF, &_textureVolF);
        _textureVolCoordF.add(minF);
        _textureVolCoordF.add(maxF);
    }
    
    if (textureS != NULL)
    {
        setTexture(textureS, &_textureVolS);
        _textureVolCoordS.add(minS);
        _textureVolCoordS.add(maxS);
    }
    
}

void SceneOGL14::setTexture(Image2D1C<int> *texture, GLuint *idTexture)
{
    int width = texture->getWidth();
    int height = texture->getHeight();
    int size = width * height;
    GLubyte *imageTexture = new GLubyte[size * 4];
    int j=0;
    for (int i=0 ; i < size ; i++)
    {
        int data = texture->get(i);
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)255; j++;
    }
    
    glGenTextures(1, idTexture);
    glBindTexture(GL_TEXTURE_2D, *idTexture);
    
    glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imageTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    delete []imageTexture;
}


//---------------------------------------
//Creation TEXTURE (source Mesh)
//---------------------------------------



void SceneOGL14::setTextureThz(Mesh *texture, GLuint *idTexture,int width ,int height)
{
    
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"TEXTURES"<<std::endl;
    std::cout<<"   width:"<<width<<"  height:"<<height<<std::endl;
    std::cout<<"   width:"<<width<<"  height:"<<height<<std::endl;
    std::cout<<"  size:"<< texture->getSize()<<"  width*height:"<<width*height <<std::endl;
    
    int size = texture->getSize();
    GLubyte *imageTexture = new GLubyte[width*height * 4];
    
    int min=100000;
    int max=0;
    
    //recherche du max et du min
    for (int i=0 ; i < size ; i++)
    {
        float data = texture->getAmplitude(i);
        if(max<data)
            max=data;
        if(min>data)
            min=data;
    }
    
    
    int indexSlice=0;
    int j=0;
    for (int i=0 ; i < width*height ; i++)
    {
        float data= (texture->getAmplitude(indexSlice)-min)*255/(max-min);
        //std::cout<<"data["<<i<<"]="<<data<<std::endl;
        imageTexture[j] = (GLubyte)data;j++;
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)255; j++;
        indexSlice++;
        
    }
    
    
    
    
    
    glGenTextures(1, idTexture);
    glBindTexture(GL_TEXTURE_2D, *idTexture);
    
    glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imageTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    delete []imageTexture;
}

void SceneOGL14::setTextureEquilibrium(Mesh *texture, GLuint *idTexture,int width ,int height)
{
    
    std::cout<<"------------------------"<<std::endl;
    std::cout<<"TEXTURES"<<std::endl;
    std::cout<<"   width:"<<width<<"  height:"<<height<<std::endl;
    std::cout<<"  size:"<< texture->getSize()<<"  width*height:"<<width*height <<std::endl;
    
    int size = width*height; //texture->getSize();
    GLubyte *imageTexture = new GLubyte[width*height * 4];
    
    int min=100000;
    int max=0;
    
    //recherche du max et du min
    for (int i=0 ; i < size ; i++)
    {
        float data = texture->getAmplitude(texture->getEquilibrium(i));
        if(max<data)
            max=data;
        if(min>data)
            min=data;
    }
    
    std::cout << "min " << min << " max " << max << std::endl;
    
    int indexSlice=0;
    int j=0;
    for (int i=0 ; i < width*height ; i++)
    {
        float data= (texture->getAmplitude(texture->getEquilibrium(i))-min)*255/(max-min);
        //std::cout<<"data["<<i<<"]="<<data<<"/"<<texture->getSizeGlobale() <<std::endl;
        imageTexture[j] = (GLubyte)data;j++;
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)data; j++;
        imageTexture[j] = (GLubyte)255; j++;
        indexSlice++;
        
    }
    
    
    
    
    
    glGenTextures(1, idTexture);
    glBindTexture(GL_TEXTURE_2D, *idTexture);
    
    glTexImage2D( GL_TEXTURE_2D, 0, 4, width, height, 0, GL_RGBA,
                 GL_UNSIGNED_BYTE, imageTexture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    
    delete []imageTexture;
}



//*****************************************************************************
//---------------------------------------
//                           Dessins TEXTUREs
//---------------------------------------
//*****************************************************************************

//---------------------------------------
//Dessin TEXTURE
//---------------------------------------



void SceneOGL14::drawTextureTransverse(Point3D_t<float>& min,Point3D_t<float>& max){
    
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureVolT);
    
    glBegin (GL_QUADS);
    glTexCoord2i (0,0); glVertex3i (min.x, min.y, min.z);
    glTexCoord2i (1,0); glVertex3i (max.x, min.y, min.z);
    glTexCoord2i (1,1); glVertex3i (max.x, min.y, max.z);
    glTexCoord2i (0,1); glVertex3i (min.x, min.y, max.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void SceneOGL14::drawTextureFrontale(Point3D_t<float>& min,Point3D_t<float>& max){
    
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureVolF);
    glBegin (GL_QUADS);
    glTexCoord2i (0,0); glVertex3i (min.x, max.y, min.z);
    glTexCoord2i (1,0); glVertex3i (max.x, max.y, min.z);
    glTexCoord2i (1,1); glVertex3i (max.x, min.y, min.z);
    glTexCoord2i (0,1); glVertex3i (min.x, min.y, min.z);
    glEnd();
    glDisable(GL_TEXTURE_2D);
}

void SceneOGL14::drawTextureSagitale(Point3D_t<float>& min,Point3D_t<float>& max){
    glColor3f(1, 1, 1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, _textureVolS);
    
    glBegin (GL_QUADS);
    glTexCoord2i (0,0); glVertex3i (max.x, max.y, min.z);
    glTexCoord2i (1,0); glVertex3i (max.x, max.y, max.z);
    glTexCoord2i (1,1); glVertex3i (max.x, min.y, max.z);
    glTexCoord2i (0,1); glVertex3i (max.x, min.y, min.z);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
}

void SceneOGL14::drawTexturesFromImage3D()
{
    
    
    //calcul des textures
    TranscribeDatasFromContainer();
    
    //Texture transverse
    if(_textureVolCoordT.size() == 2)
    {
        Point3D_t<float> &min = _textureVolCoordT.getRef(0);
        Point3D_t<float> &max = _textureVolCoordT.getRef(1);
        drawTextureTransverse( min, max);
    }
    //Texture Frontale
    if (_textureVolCoordF.size() == 2)
    {
        Point3D_t<float> &min = _textureVolCoordF.getRef(0);
        Point3D_t<float> &max = _textureVolCoordF.getRef(1);
        drawTextureFrontale( min, max);
    }
    //Texture sagitale
    if (_textureVolCoordS.size() == 2)
    {
        Point3D_t<float> &min = _textureVolCoordS.getRef(0);
        Point3D_t<float> &max = _textureVolCoordS.getRef(1);
        drawTextureSagitale( min, max);
        
    }
    
}

void SceneOGL14::drawTexturesFromMesh()
{
    Point3D_t<float> min(_box->getXMin(), _box->getYMin(),_box->getZMin());
    Point3D_t<float> max(_box->getXMax(), _box->getYMax(),_box->getZMax());
    // std::cout<<"drawVolumeTexture:"<< _Meshs->getTypeSlice()<<std::endl;
    
    switch(_Meshs->getTypeSlice()){
        case 0://frontal
        {
            //affecte les valeurs
            int width = _Meshs->getWidth();
            int depth = _Meshs->getDepth();
            
            
            setTextureThz(_Meshs, &_textureVolF,width,depth);
            
            //plaque la texture sur un quad Frontale
            drawTextureFrontale(min,max);
            break;
        }
        case 1://sagital
        {
            //affecte les valeurs
            int depth = _Meshs->getDepth();
            int height = _Meshs->getHeight();
            
            setTextureThz(_Meshs, &_textureVolS,depth,height);
            
            //plaque la texture sur un quad  Sagitale
            drawTextureSagitale(min,max);
            break;
        }
        case 2://transverse
        {
            //affecte les valeurs
            int width = _Meshs->getWidth();
            int height = _Meshs->getHeight();
            setTextureThz(_Meshs, &_textureVolT,width,height);
            
            //plaque la texture sur un quad transverse
            drawTextureTransverse(min,max);
            break;
        }
        case 3: //transverse equilibrium
        {
            int width = _Meshs->getWidthEquilibrium();
            int height = _Meshs->getHeightEquilibrium();
            setTextureEquilibrium(_Meshs, &_textureVolT, width, height);
            drawTextureTransverse(min,max);
            break;
            
        }
            
        default:
            break;
    }
}

void SceneOGL14::drawVolumeTexture()
{
    
    if(_Meshs!=NULL){
        drawTexturesFromMesh();
    }
    if(_Objets2D!=NULL){
        drawTexturesFromImage3D();
    }
}
//---------------------------------------
//POINTS
//---------------------------------------


void SceneOGL14::DrawPoint(float x,float y,float z, float value){
    
    
    glBegin(GL_POINTS);
    glColor4f(value, value, value, 1.0f);
    glVertex3f(x, y, z);
    glEnd();
    
}

void SceneOGL14::DrawLstPoint(){
    for (int i=0; i<_Meshs->getSize(); i++)
    {
        //std::cout<<"data["<<i<<"]="<<_Meshs->getAmplitude(i)<<std::endl;
        
        DrawPoint(_Meshs->getX(i), _Meshs->getY(i), _Meshs->getZ(i),_Meshs->getAmplitude(i) );
        
    }
}

//---------------------------------------
//TRIANGLES
//---------------------------------------

void SceneOGL14::DrawTriangle(float x1,float y1,float z1,
                              float x2,float y2,float z2,
                              float x3,float y3,float z3){
    glBegin(GL_TRIANGLES);
    glVertex3d(x1,y1,z1);
    glVertex3d(x2,y2,z2);
    glVertex3d(x3,y3,z3);
    glEnd();
}

void SceneOGL14::DrawLstTriangle(){
    
    //on ne dessine pas si on est sur un des points du bord
    for (int i=0; i<_Meshs->getSizeFace(); ++i)
    {
        int p1 = _Meshs->getP1(i);
        int p2 = _Meshs->getP2(i);
        int p3 = _Meshs->getP3(i);
        DrawTriangle(_Meshs->getX(p1), _Meshs->getY(p1), _Meshs->getZ(p1),
                     _Meshs->getX(p2), _Meshs->getY(p2), _Meshs->getZ(p2),
                     _Meshs->getX(p3), _Meshs->getY(p3), _Meshs->getZ(p3));
        
    }
    
    
}

void SceneOGL14::DrawLstTriangleFilaire(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);	// on tracera uniquement les contours des polygones
    DrawLstTriangle();
    glDisable(GL_POLYGON_OFFSET_FILL);
}

void SceneOGL14::DrawLstTrianglePlein(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);	// on tracera uniquement les contours des polygones
    DrawLstTriangle();
    glDisable(GL_POLYGON_OFFSET_FILL);
}

//---------------------------------------
//FOND,REPERE,BOUNDINGBOX
//---------------------------------------

void SceneOGL14::drawRepere(){
    //Repère au centre d'intérêt
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter());
    glVertex3f(_box->getXCenter()+100.0, _box->getYCenter(), _box->getZCenter());
    glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
    glVertex3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter());
    glVertex3f(_box->getXCenter(), _box->getYCenter()+100.0, _box->getZCenter());
    glColor4f(0.0f, 0.0f, 1.0f, 1.0f);
    glVertex3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter());
    glVertex3f(_box->getXCenter(), _box->getYCenter(), _box->getZCenter()+100.0);
    glEnd();
    
}

void SceneOGL14::drawBackground()
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glOrtho(-1,1,-1,1,-1,1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    glPushAttrib(GL_ENABLE_BIT);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_TRIANGLE_STRIP);
    glColor3ub(128,128,255);  	glVertex2f(-1, 1);
    glColor3ub( 0, 0,   0);	glVertex2f(-1,-1);
    glColor3ub(128,128,255);   glVertex2f( 1, 1);
    glColor3ub( 0, 0,   0);	glVertex2f( 1,-1);
    glEnd();
    
    glPopAttrib();
    glPopMatrix(); // restore modelview
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
    glEnable(GL_CULL_FACE);
}

void SceneOGL14::drawBoundingBox()
{
    
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(255, 255, 0);
    glBegin(GL_QUADS);
    /* front face */
    glVertex3f (_box->getXMin(), _box->getYMin(), _box->getZMin());
    glVertex3f (_box->getXMax(), _box->getYMin(), _box->getZMin());
    glVertex3f (_box->getXMax(), _box->getYMax(), _box->getZMin());
    glVertex3f (_box->getXMin(), _box->getYMax(), _box->getZMin());
    glEnd();
    
    glBegin(GL_QUADS);
    /* back face */
    glVertex3f (_box->getXMin(), _box->getYMin(), _box->getZMax());
    glVertex3f (_box->getXMax(), _box->getYMin(), _box->getZMax());
    glVertex3f (_box->getXMax(), _box->getYMax(), _box->getZMax());
    glVertex3f (_box->getXMin(), _box->getYMax(), _box->getZMax());
    glEnd();
    
    glBegin(GL_QUADS);
    /* left face */
    glVertex3f (_box->getXMin(), _box->getYMin(), _box->getZMin());
    glVertex3f (_box->getXMin(), _box->getYMin(), _box->getZMax());
    glVertex3f (_box->getXMin(), _box->getYMax(), _box->getZMax());
    glVertex3f (_box->getXMin(), _box->getYMax(), _box->getZMin());
    glEnd();
    
    glBegin(GL_QUADS);
    /* right face */
    glVertex3f (_box->getXMax(), _box->getYMin(), _box->getZMin());
    glVertex3f (_box->getXMax(), _box->getYMin(), _box->getZMax());
    glVertex3f (_box->getXMax(), _box->getYMax(), _box->getZMax());
    glVertex3f (_box->getXMax(), _box->getYMax(), _box->getZMin());
    glEnd();
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    
}









void SceneOGL14::drawProfils(){
    //recuperation de la taille
    Triplet_t<int,int,int>* triplet=this->_box->getSizes();
    int width=triplet->first;
    int height=triplet->second;
    int depth=triplet->third;
    delete triplet;
    
    //recuperation des index images
    Point3D_t<int>*p=_Objets2D->getIndexProfils();
    int indexX=p->x;
    int indexY=p->y;
    int indexZ=p->z;
    delete p;
    
    //drawProfilX()
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(indexX,0,indexZ );
    glVertex3f(indexX,height,indexZ );
    glEnd();
    
    //drawProfilY();
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(indexX,indexY,0 );
    glVertex3f(indexX,indexY,depth );
    glEnd();
    
    //drawProfilZ()
    glBegin(GL_LINES);
    glColor4f(1.0f, 0.0f, 0.0f, 1.0f);
    glVertex3f(0,indexY,indexZ );
    glVertex3f(width,indexY,indexZ );
    glEnd();
}

//---------------------------------------
//SCENE
//---------------------------------------

void SceneOGL14::draw()
{
    
    // std::cout<<"------------------------------------"<<std::endl;
    // std::cout<<"PipelineGrapique 3D:  Mesh="<<_Meshs<<"  Container2D="<<_Objets2D <<std::endl;
    // std::cout<<"------------------------------------"<<std::endl;
    
    if(_Meshs!=NULL){
        
        switch(_renderMode)
        {
                
            case PLOT:
                
                if(_Meshs->is3D()){
                    DrawLstPoint();
                    drawRepere();
                }
                else{
                    DrawLstPoint();
                    drawRepere();
                }
                
                break;
                
            case FACE:
                if(_Meshs->is3D()){
                    glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
                    int p1, p2, p3;
                    float value;
                    
                    for (int i=0; i<_Meshs->getSizeFace(); ++i)
                    {
                        
                        p1 = _Meshs->getP1(i);
                        p2 = _Meshs->getP2(i);
                        p3 = _Meshs->getP3(i);
                        
                        glLoadName(i);
                        glBegin(GL_TRIANGLES);
                        
                        value = _Meshs->getAmplitude(p1);
                        glColor4f(value, value, value, 1.0f);
                        glVertex3f(_Meshs->getX(p1), _Meshs->getY(p1), _Meshs->getZ(p1));
                        
                        value = _Meshs->getAmplitude(p2);
                        glColor4f(value, value, value, 1.0f);
                        glVertex3f(_Meshs->getX(p2), _Meshs->getY(p2), _Meshs->getZ(p2));
                        
                        value = _Meshs->getAmplitude(p3);
                        glColor4f(value, value, value, 1.0f);
                        glVertex3f(_Meshs->getX(p3), _Meshs->getY(p3), _Meshs->getZ(p3));
                        
                        glEnd();
                    }
                    
                }
                else{
                    drawVolumeTexture();
                }
                break;
                
            case FLAT:
                _Meshs->setTypeSlice(3);
                drawVolumeTexture();
                
                
                break;
                
                
                
        }
    }
    
    if(_Objets2D!=NULL){
        
        drawTexturesFromImage3D();
        //drawProfils();
    }
    
    //    drawBackground();
    //   drawBoundingBox();
    
    
}













//*******************************************************************************************
//*******************************************************************************************
//
//OPENGL version 33
//
//*******************************************************************************************
//*******************************************************************************************

SceneOGL33::SceneOGL33( int width, int height,int depth)
: Scene( width, height, depth),
_cam(new Camera())
{
    _Meshs=NULL;
    _Objets2D=NULL;
}

SceneOGL33::~SceneOGL33()
{
    
}

void SceneOGL33::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    
    _cam->setEye(Vec3f(0, 0, _box->getZMax() - _box->getZMin()));
    _cam->setTarget(Vec3f(0, 0, 0));
    _cam->lookAt();
    
    glMatrixMode(GL_MODELVIEW);
    
    modelviewfloor.setTranslate(0.0f, 0.0f, _zoom);
    glLoadMatrixf(modelviewfloor);
    
    modelviewfloor.addRotate(_rotx, 1.0f, 0.0f, 0.0f);
    modelviewfloor.addRotate(_roty, 0.0f, 1.0f, 0.0f);
    
    glUseProgram(shaderProgramObject);
    glUniformMatrix4fv(modelviObjectLoc,1,GL_FALSE, modelviewfloor);
    glUniformMatrix4fv(projectObjectLoc,1,GL_FALSE, projection);
    glUniformMatrix4fv(cameraObjectLoc, 1, GL_FALSE, _cam->c_matrix);
    
    draw();
    
    glUseProgram(0);
    glBindVertexArray(0);
}

void SceneOGL33::init()
{
    glClearColor (0.0, 0.9, 0.7, 0.0);
    glViewport (0, 0, _width, _height);
    glEnable(GL_DEPTH_TEST);
    
    glMatrixMode (GL_PROJECTION);
    projection.setPerspective (40.0, float(_width)/float(_height), 0.01, 1000.0 );
    glLoadMatrixf(projection);
    
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
        std::cerr << "Glew Initialization error" << std::endl;
        return;
    }
    
    
    initdatas();
    init3DDatas();
    initShader("shader.vert", "shader.frag");
}

void SceneOGL33::updateIntensity()
{
    initdatas();
    init3DDatas(true);
}

void SceneOGL33::draw()
{
    glActiveTexture(0);
    
    glEnableVertexAttribArray(vcolorObjectLoc);
    glBindBuffer(GL_ARRAY_BUFFER, color_ID[0]);
    glVertexAttribPointer(vcolorObjectLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
    
    glEnableVertexAttribArray(vpositiObjectLoc);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_Buffer_ID[0]);
    glVertexAttribPointer(vpositiObjectLoc,3,GL_FLOAT, GL_FALSE,0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_Buffer_ID[0]);
    std::cout<<"SceneOGL33::RENDERMODE"<<std::endl;
    switch(_renderMode)
    {
            std::cout<<"SceneOGL33::RENDERMODE"<<std::endl;
        case PLOT:
            std::cout<<"Mesh"<<std::endl;
            if (_Meshs->getSizeFace() > 0){
                std::cout<<"Meshs->getSizeFace() > 0"<<std::endl;
                glDrawElements(GL_POINTS, indices.size(), GL_UNSIGNED_INT, 0);
            }else{
                std::cout<<"Meshs->getSizeFace() < 0"<<std::endl;
                glDrawArrays(GL_POINTS, 0, vertices.size());
            }
            break;
        case FACE:
            glDrawElements(GL_TRIANGLE_STRIP, indices.size(), GL_UNSIGNED_INT, 0);
            break;
            
    }
    
    glDisableVertexAttribArray(vpositiObjectLoc);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

std::vector<int> faceCol;

bool pointToRed(int index)
{
    for(int i=0; i<faceCol.size();++i)
        if(faceCol[i] == index)
            return true;
    return false;
}

void SceneOGL33::initdatas()
{
    vertices.clear();
    colors.clear();
    indices.clear();
    
    for(int i=0; i<_Meshs->getSize(); ++i)
    {
        vertices.push_back(_Meshs->getX(i) - _box->getXCenter());
        vertices.push_back(_Meshs->getY(i) - _box->getYCenter());
        vertices.push_back(_Meshs->getZ(i) - _box->getZCenter());
        
        if(pointToRed(i))
        {
            colors.push_back(1.0);
            colors.push_back(0.0);
            colors.push_back(0.0);
        }
        else
        {
            colors.push_back(_Meshs->getAmplitude(i));
            colors.push_back(_Meshs->getAmplitude(i));
            colors.push_back(_Meshs->getAmplitude(i));
        }
    }
    
    for (int i=0; i<_Meshs->getSizeFace(); ++i)
    {
        indices.push_back(_Meshs->getP1(i));
        indices.push_back(_Meshs->getP2(i));
        indices.push_back(_Meshs->getP3(i));
    }
}

void SceneOGL33::init3DDatas(bool clean)
{
    if (clean)
    {
        glDeleteBuffers(1, &color_ID[0]);
        glDeleteBuffers(1, &vertex_Buffer_ID[0]);
        glDeleteBuffers(1, &index_Buffer_ID[0]);
    }
    glGenBuffers(1, &color_ID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, color_ID[0]);
    glBufferData(GL_ARRAY_BUFFER, colors.size() * sizeof(GLfloat), &colors[0], GL_STATIC_DRAW);
    
    glGenBuffers(3, &vertex_Buffer_ID[0]);
    glBindBuffer(GL_ARRAY_BUFFER, vertex_Buffer_ID[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(GLfloat), &vertices[0], GL_STATIC_DRAW);
    
    glGenBuffers(1, &index_Buffer_ID[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_Buffer_ID[0]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), &indices[0], GL_STATIC_DRAW);
}

void SceneOGL33::initShader(const std::string &vfile, const std::string &ffile)
{
    try
    {
        shaderProgramObject = Shader::loadShader(vfile,ffile);
    }
    catch ( ShaderException e )
    {
        std::cerr << e.getMessage() << std::endl;
    }
    
    modelviObjectLoc = glGetUniformLocation(shaderProgramObject, "modelview");
    projectObjectLoc = glGetUniformLocation(shaderProgramObject, "projection");
    vcolorObjectLoc = glGetAttribLocation(shaderProgramObject, "vcolor");
    
    vpositiObjectLoc = 0;
    glBindAttribLocation(shaderProgramObject,0,"vposition");
}


