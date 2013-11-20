#ifndef SCENE_H
#define SCENE_H

// OpenGL platform species
#ifdef _WIN64

#elif _WIN32
#include <windows.h>

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

#include "shader.h"

#include <Mesh.hpp>
#include <View2DContainer.hpp>
#include "boundingbox.h"
#include "camera.h"
#include "matrix.h"
#include <Points.hpp>
#include <modeltranscriber.hpp>


class Scene
{
public:
    enum RenderMode { PLOT = 0, FACE, FLAT };

    Scene(int width, int height, int depth);
    ~Scene();

    //Dans le cas ou on a qu'un mesh tout seul
    void setData(Mesh * Meshs);
    
    //dans le cas ou on part d'un type 3D
    void setData(Mesh * Meshs, View2DContainer* All2DViews);
    
    void setData(Mesh * Meshs, View2DContainer* All2DViews,
                 int widthBoundingBox,int heightBoundingBox,int depthBoundingBox);

    virtual void display() = 0;
    virtual void init() = 0;
    virtual void updateIntensity() = 0;

    void reshape(int width, int heigh);
    void mouseMotion(int x, int y);

    inline void zoomIn() { _zoom += 10.0; }
    inline void zoomOut() { _zoom -= 10.0; }
    inline int getWidth() {return this->_width; }
    inline int getHeight() {return this->_height; }
    inline Mesh *getMesh() { return _Meshs; }

    inline void setLastXY(int x, int y) { _lastx = x; _lasty = y; }
    inline void setRenderMode(RenderMode mode) { _renderMode = mode; }

protected:
    int _lastx, _lasty;
    int _width, _height;
    GLfloat _rotx, _roty, _zoom;

    float _resXVoxel;
    float _resYVoxel;
    float _resZVoxel;

    View2DContainer* _Objets2D;
    Mesh* _Meshs;
    BoundingBox* _box;
    RenderMode _renderMode;
};


class SceneOGL14 : public Scene
{
public:

    SceneOGL14( int width, int height,int depth);
    ~SceneOGL14();

    //Dans le cas ou on a qu'un mesh tout seul
    void setData(Mesh * Meshs);

    //dans le cas ou on part d'un type 3D
    void setData(Mesh * Meshs, View2DContainer* All2DViews,
                 int widthBoundingBox,int heightBoundingBox,int depthBoundingBox);

    void display();
    void init();
    void updateIntensity();
    void UpdateContainer();
    
    
private:
    //creations des textures
    void TranscribeDatasFromContainer();
    void SetDataTranscribedToTextures(Image2D1C<int> *textureT,Image2D1C<int> *textureF,Image2D1C<int> *textureS,
                                      Point3D_t<float> minT, Point3D_t<float> maxT, Point3D_t<float> minF,
                                      Point3D_t<float>  maxF, Point3D_t<float> minS, Point3D_t<float>  maxS);
    
    void setTexture(Image2D1C<int> *texture, GLuint *idTexture);
    void setTextureThz(Mesh *texture, GLuint *idTexture,int ,int);
    void setTextureEquilibrium(Mesh *texture, GLuint *idTexture,int ,int);


    //dessin des textures
    void drawTextureTransverse(Point3D_t<float>& min,Point3D_t<float>& max);
    void drawTextureFrontale(Point3D_t<float>& min,Point3D_t<float>& max);
    void drawTextureSagitale(Point3D_t<float>& min,Point3D_t<float>& max);

    void drawTexturesFromImage3D();
    void drawTexturesFromMesh();
    void drawVolumeTexture();

    
    //dessin des points
    void DrawPoint(float x,float y,float z, float value);
    void DrawLstPoint();


    //dessin des triangles
    void DrawTriangle(float x1,float y1,float z1,
                      float x2,float y2,float z2,
                      float x3,float y3,float z3);
    void DrawLstTriangle();
    void DrawLstTriangleFilaire();
    void DrawLstTrianglePlein();
    
    
    //dessin des triangles
    void drawRepere();
    void drawBackground();
    void drawBoundingBox();
    void drawProfils();
    void draw();

private:
    Camera *_cam;

    Vec3f location;

    // VOLUME TEXTURE
    bool _textureVolViewFlag;

    GLuint _textureVolT;
    MiList<Point3D_t<float> >_textureVolCoordT; // Size = 2

    GLuint _textureVolF;
    MiList<Point3D_t<float> >_textureVolCoordF; // Size = 2

    GLuint _textureVolS;
    MiList<Point3D_t<float> >_textureVolCoordS; // Size = 2
};


class SceneOGL33 : public Scene
{
public:
    SceneOGL33(int width, int height, int depth);
    ~SceneOGL33();

    void setSize(int widthBoundingBox,int heightBoundingBox,int depthBoundingBox);
    
    //Dans le cas ou on a qu'un mesh tout seul
    void setData(Mesh * Meshs);
    
    //dans le cas ou on part d'un type 3D
    void setData(Mesh * Meshs, View2DContainer* All2DViews);

    void display();
    void init();
    void updateIntensity();

    
private:
    void draw();
    void initdatas();
    void init3DDatas(bool clean = false);
    void initShader(const std::string &vfile, const std::string &ffile);

private:
    Camera *_cam;

    std::vector<GLfloat> vertices, colors;
    std::vector<GLuint> indices;

    GLuint vertex_Array_ID[2], vertex_Buffer_ID[2], index_Buffer_ID[2], color_ID[2];
    GLuint shaderProgramObject;
    GLint vcolorObjectLoc, vpositiObjectLoc, modelviObjectLoc, projectObjectLoc;

    Matrix4x4<GLfloat> projection, modelviewfloor;
    GLint cameraObjectLoc;
};






#endif // SCENE_H
