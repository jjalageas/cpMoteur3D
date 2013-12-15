/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#include "exampleapp.h"
#include "Vector3d.h"
#include "Struct.hpp"
#include "MeshGeneration.hpp"

#include <QCoreApplication>
#include <QtQml/QQmlContext>
#include <QDir>
#include <QDebug>
#include "../lib/mesh.hpp"
#include "../lib/tetgen.h"
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <boost/lexical_cast.hpp>








static QString appPath()
{
    QString path = QCoreApplication::applicationDirPath();
    QDir dir(path);
#ifdef Q_WS_MAC
    dir.cdUp();
    dir.cdUp();
    dir.cdUp();
#elif defined(Q_WS_WIN)
    dir.cdUp();
#endif
    return dir.absolutePath();
}

ExampleApp::ExampleApp(QWindow *parent) :
    QQuickView(parent)
  , m_cameraObject(0)
  , m_cameraObject2(0)
  , m_cameraObject3(0)
  , m_cameraObject4(0)
  , m_ogreEngine(0)
  , m_sceneManager(0)
  , m_sceneManager2(0)
  , m_sceneManager3(0)
  , m_sceneManager4(0)
  , m_root(0)
{
    //  qmlRegisterType<CameraNodeObject>("Example", 1, 0, "Camera");

    // start Ogre once we are in the rendering thread (Ogre must live in the rendering thread)
    connect(this, &ExampleApp::beforeRendering, this, &ExampleApp::initializeOgre, Qt::DirectConnection);
    connect(this, &ExampleApp::ogreInitialized, this, &ExampleApp::addContent);
}

ExampleApp::~ExampleApp()
{
    if (m_sceneManager) {
        m_root->destroySceneManager(m_sceneManager);
    }
}

Examen* ExampleApp::tmpLoadData(std::string filename)
{

    ParserMi3DBinary parser_bmi3d;
    Examen* examAfter= parser_bmi3d.loadFile(filename);
    return examAfter;
}



void ExampleApp::initializeModel(Examen* exam, std::string name)
{
    Ogre::SceneNode* NodeRoot = Ogre::Root::getSingleton().getSceneManager(name)->getRootSceneNode();

    Volume* data=exam->getImage();

    //récupère les coupes et crée la boundingbox
    DrawBoundingBox(NodeRoot,"boundingBox", data );

    //récupère le skeleton
    //Skeleton* skel=examAfter->getSkeleton();
    //initializeSkeleton("skeleton" ,skel);


    //récupère le mask 3D (nuage de point)
    Mask3d* mask=exam->getMask();
    Mesh* mesh = new Mesh(mask);
    MeshGeneration::DrawMeshStripLine(NodeRoot,name,mesh, m_sceneManager);
    //mask->TransformMapIntoListIndex1D(1);
    //dessine le nuage de point
   // MeshGeneration::DrawPointcloud("mask", "General" , 123381, mask->TransformMapIntoListIndex1D_bis(1), NodeRoot, m_sceneManager);
   // initializeMask("mask", mask, name);
}


void ExampleApp::initializeMesh(Examen* exam, std::string name)
{
    Ogre::SceneNode* NodeRoot = Ogre::Root::getSingleton().getSceneManager(name)->getRootSceneNode();
    Volume* data = exam->getImage();
    DrawBoundingBox(NodeRoot,"boundingBox", data );
    Mask3d* mask=exam->getMask();
    MeshGeneration::Point_clouds(NodeRoot, name, mask, m_sceneManager);
}

void ExampleApp::DrawLine(Ogre::SceneNode*parent,const Ogre::Vector3& start, const Ogre::Vector3& stop, const Ogre::ColourValue& col)
{
    Ogre::SceneNode* myManualObjectNode =parent->createChildSceneNode();


    Ogre::ManualObject* myManualObject = m_sceneManager->createManualObject();
    myManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
    myManualObject->position(start);
    myManualObject->colour(col);
    myManualObject->position(stop);
    myManualObject->colour(col);
    myManualObject->end();
    myManualObjectNode->attachObject(myManualObject);

}

void ExampleApp::DrawGrid(Ogre::SceneNode*parent,int width, int height,int depth, int step_size)
{

    Ogre::SceneNode* myManualObjectNode = parent->createChildSceneNode();

    // Draw X line
    DrawLine(myManualObjectNode,Ogre::Vector3(-width,0,0),Ogre::Vector3(width,0,0),Ogre::ColourValue(1.0,0.0,0.0,1.0));

    // draw each vertical of X
    for(int x_step = -width; x_step <= width; x_step+= step_size)
    {
        // prevent displaying on Y axis
        if(x_step != 0)
        {
            DrawLine(myManualObjectNode,Ogre::Vector3(x_step,0.0,-depth),Ogre::Vector3(x_step,0.0,depth),Ogre::ColourValue(1.0,1.0,1.0,1.0));
        }
    }

    // Draw Y line
    DrawLine(myManualObjectNode,Ogre::Vector3(0,-height,0),Ogre::Vector3(0,height,0),Ogre::ColourValue(0.0,1.0,0.0,1.0));


    for(int y_step = -height; y_step <= height; y_step += step_size)
    {
        if(y_step != 0)
        {
            DrawLine(myManualObjectNode,Ogre::Vector3(-width,y_step,0.0),Ogre::Vector3(width,y_step,0.0),Ogre::ColourValue(1.0,1.0,1.0,1.0));
        }
    }


    //Draw Z line
    DrawLine(myManualObjectNode,Ogre::Vector3(0,0,-depth),Ogre::Vector3(0,0,depth),Ogre::ColourValue(0.0,0.0,1.0,1.0));

    for(int z_step = -depth; z_step <= depth; z_step+= step_size)
    {
        // prevent displaying on Y axis
        if(z_step != 0)
        {
            DrawLine(myManualObjectNode,Ogre::Vector3(-width,0.0,z_step),Ogre::Vector3(width,0.0,z_step),Ogre::ColourValue(1.0,1.0,1.0,1.0));
        }
    }
}


void ExampleApp::DrawCube(Ogre::SceneNode*parent,int width,int height,int depth){

    //Ogre::SceneNode* myManualObjectNode = parent->createChildSceneNode();


    Ogre::AxisAlignedBox box (Ogre::Vector3( 0,  0, 0),
                              Ogre::Vector3(width, height,  depth));
    DebugDrawer::getSingleton().drawCuboid(box.getAllCorners(),
                                           Ogre::ColourValue(51.0f  / 255.0f, 51.0f  / 255.0f, 51.0f  / 255.0f, 0.4), true);



    //myManualObjectNode->attachObject(box);

}


void ExampleApp::LoadImageIntoTexture(Ogre::SceneNode*parent,std::string name,Image<float>* imagedata )
{
    Ogre::SceneNode* NodeTexture = parent->createChildSceneNode();
    //transformation de vos donnée brute en donnée visualisable

    //chargement dans un texture
    Ogre::Image* image = new Ogre::Image();
    image->loadDynamicImage((uchar*)imagedata, imagedata->getWidth(),imagedata->getHeight(), Ogre::PF_B8G8R8);
    /*  Ogre::TextureManager::getSingleton().loadImage(name,
                                                   Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
                                                   image,
                                                   Ogre::TEX_TYPE_2D, 0, 1.0f);
*/
}

void ExampleApp::DrawBoundingBox(Ogre::SceneNode*parent,std::string ,Volume* data){

    Ogre::SceneNode* NodeBoundingBox = parent->createChildSceneNode();
    NodeBoundingBox->setPosition(0,0.5,0);



    int width=data->getWidth();
    int height=data->getHeight();
    int depth=data->getDepth();

    int midw=width/2;
    int midh=height/2;
    int midd=depth/2;

    //--------------------------------------
    //définit Le cube de la bounding box
    //--------------------------------------
    DrawCube(NodeBoundingBox, width, height, depth);
    //DrawGrid(NodeBoundingBox, midw, midh , midd,  5);


    //--------------------------------------
    //définit nos images de coupes
    //--------------------------------------
    //Coronal=data->getSlice(midw,CORONAL);
    Image<float>* Coronal=data->getSlice(midw,CORONAL);
    std::cout<<"ok"<<std::endl;
    Image<float>* Frontal=data->getSlice(midh,FRONTAL);
    std::cout<<"ok"<<std::endl;
    Image<float>* Sagitale=data->getSlice(midd,SAGITAL);
    std::cout<<"ok"<<std::endl;

    //--------------------------------------
    //définit les faces du cube
    //--------------------------------------
    Image<float>* CoronalFront=data->getSlice(0,CORONAL);



    std::cout<<"ok"<<std::endl;
    Image<float>* FrontalFront=data->getSlice(0,FRONTAL);
    std::cout<<"ok"<<std::endl;
    Image<float>* SagitaleFront=data->getSlice(0,SAGITAL);
    std::cout<<"ok"<<std::endl;
    // Image<float>* CoronalBack=data->getSlice(width-1,CORONAL);
    std::cout<<"ok"<<std::endl;
    // Image<float>* FrontalBack=data->getSlice(height-1,FRONTAL);
    std::cout<<"ok"<<std::endl;
    // Image<float>* SagitaleBack=data->getSlice(depth-1,SAGITAL);
    std::cout<<"ok"<<std::endl;

    //y'a plu qu'a charger....

}



void ExampleApp::initializeMask(std::string name,Mask3d* mask,std::string managerName)
{
    Ogre::SceneManager* sceneManager = Ogre::Root::getSingleton().getSceneManager(managerName);
    Ogre::ManualObject* m_ManualObject=sceneManager->createManualObject(name);
    int width=mask->getWidth();
    int height=mask->getHeight();
    int depth=mask->getDepth();
    m_ManualObject->setDynamic(true);
    m_ManualObject->begin("BaseWhiteNoLighting",Ogre::RenderOperation::OT_POINT_LIST);


    for(int k=0;k<depth;++k){
        for(int j=0;j<height;++j){
            for(int i=0;i<width;++i){
                if(mask->get(i, j, k)){
                    //std::cout<<"position ("<<i<<","<<j<<","<<k<<")="<<mask->get(i, j, k)<<std::endl;
                    m_ManualObject->position(i, j, k);
                    // m_ManualObject->normal(nx, ny, nz);
                    m_ManualObject->colour(Ogre::ColourValue(0.5f, 0.0f, 0.0f, 1.0f));
                }
            }
        }

    }
    m_ManualObject->end();
    sceneManager->getRootSceneNode()->createChildSceneNode()->attachObject(m_ManualObject);
}



void ExampleApp::initializeSkeleton(std::string ,Skeleton* ){


}



void ExampleApp::DrawMultiCube(){
    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                Ogre::AxisAlignedBox box (Ogre::Vector3(i * 10.0f + 2.0f, j * 10.0f + 2.0f, k * 10.0f + 2.0f),
                                          Ogre::Vector3((i + 1) * 10.0f - 2.0f, (j + 1) * 10.0f - 2.0f, (k + 1) * 10.0f - 2.0f));
                DebugDrawer::getSingleton().drawCuboid(box.getAllCorners(),
                                                       Ogre::ColourValue(51.0f * i / 255.0f, 51.0f * j / 255.0f, 51.0f * k / 255.0f), true);
            }
        }
    }

}


void ExampleApp::DrawMultiIcoSphere(){

    for (int i = 0; i < 5; ++i)
    {
        for (int j = 0; j < 5; j++)
        {
            for (int k = 0; k < 5; k++)
            {
                // Draws a sphere with radius 20.0f
                DebugDrawer::getSingleton().drawSphere(Ogre::Vector3(i * 50.0f, j * 50.0f, k * 50.0f),
                                                       20.0f,
                                                       Ogre::ColourValue(51.0f * i / 255.0f, 51.0f * j / 255.0f, 51.0f * k / 255.0f),
                                                       true);
            }
        }
    }

}






void ExampleApp::initializeOgre()
{

    // we only want to initialize once
    disconnect(this, &ExampleApp::beforeRendering, this, &ExampleApp::initializeOgre);

    // start up Ogre
    m_ogreEngine = new OgreEngine(this);
    m_root = m_ogreEngine->startEngine();
    m_ogreEngine->setupResources();

    // set up Ogre scene 1
    std::string name = "scene";
    m_sceneManager = m_root->createSceneManager(Ogre::ST_GENERIC, name);
    Ogre::Camera *camera1 = m_sceneManager->createCamera("myCamera2");
    camera1->setNearClipDistance(1);
    camera1->setFarClipDistance(99999);
    camera1->setAspectRatio(1);
    camera1->setAutoTracking(true, m_sceneManager->getRootSceneNode());
    m_sceneManager->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    //TODO : Non fonctionnel, suite à un bug encore inconnu
    //m_sceneManager2->setSkyBox(true, "SpaceSkyBox", 10000);
    m_ogreEngine->activateOgreContext();
    m_cameraObject = new CameraNodeObject(name,camera1);

    /*  // set up Ogre scene 2
    std::string name2 = "scene2";
    m_sceneManager2 = m_root->createSceneManager(Ogre::ST_GENERIC, name2);
    Ogre::Camera *camera2 = m_sceneManager2->createCamera("myCamera2");
    camera2->setNearClipDistance(1);
    camera2->setFarClipDistance(99999);
    camera2->setAspectRatio(1);
    camera2->setAutoTracking(true, m_sceneManager2->getRootSceneNode());
    m_sceneManager2->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    //m_sceneManager2->setSkyBox(true, "SpaceSkyBox", 10000);
    m_ogreEngine->activateOgreContext();
    m_cameraObject2 = new CameraNodeObject(name2,camera2);


    // set up Ogre scene 3
    std::string name3 = "scene3";
    m_sceneManager3 = m_root->createSceneManager(Ogre::ST_GENERIC, name3);
    Ogre::Camera *camera3 = m_sceneManager3->createCamera("myCamera3");
    camera3->setNearClipDistance(1);
    camera3->setFarClipDistance(99999);
    camera3->setAspectRatio(1);
    camera3->setAutoTracking(true, m_sceneManager3->getRootSceneNode());
    m_sceneManager3->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    //m_sceneManager3->setSkyBox(true, "SpaceSkyBox", 10000);
    m_ogreEngine->activateOgreContext();
    m_cameraObject3 = new CameraNodeObject(name3,camera3);

    // set up Ogre scene 4
    std::string name4 = "scene4";
    m_sceneManager4 = m_root->createSceneManager(Ogre::ST_GENERIC, name4);
    Ogre::Camera *camera4 = m_sceneManager4->createCamera("myCamera4");
    camera3->setNearClipDistance(1);
    camera3->setFarClipDistance(99999);
    camera3->setAspectRatio(1);
    camera3->setAutoTracking(true, m_sceneManager4->getRootSceneNode());
    m_sceneManager4->setAmbientLight(Ogre::ColourValue(0.3, 0.3, 0.3));
    //m_sceneManager4->setSkyBox(true, "SpaceSkyBox", 10000);
    m_ogreEngine->activateOgreContext();
    m_cameraObject4 = new CameraNodeObject(name4,camera4);*/

    std::string file_out="../resources/Campan_MethodeHB_Seuil_970_Plus60_thinning_sliceBranchePropre2.bmi3d";
    Examen* exam=tmpLoadData( file_out);


    // Initialise the DebugDrawer singleton
    new DebugDrawer(m_sceneManager, 0.5f);

    initializeMesh(exam,name);



    //initializeModel(exam,name2);
    //initializeModel(exam,name3);
    //initializeModel(exam,name4);

    // Let's draw the bounding box for the ogre head!
    DebugDrawer::getSingleton().build();
    //m_sceneManager->setSkyBox(true, "SoftBackGround", 10000);

    m_ogreEngine->doneOgreContext();
    emit(ogreInitialized());

}

void ExampleApp::addContent()
{
    // expose objects as QML globals
    rootContext()->setContextProperty("Window", this);
    rootContext()->setContextProperty("OgreEngine", m_ogreEngine);
    rootContext()->setContextProperty("camera1",m_cameraObject);
    rootContext()->setContextProperty("camera2",m_cameraObject2);
    rootContext()->setContextProperty("camera3",m_cameraObject3);
    rootContext()->setContextProperty("camera4",m_cameraObject4);
    // load the QML scene
    setResizeMode(QQuickView::SizeRootObjectToView);
    setSource(QUrl("qrc:/qml/example.qml"));
}
