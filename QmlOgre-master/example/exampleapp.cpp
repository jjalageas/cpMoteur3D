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

#include <QCoreApplication>
#include <QtQml/QQmlContext>
#include <QDir>
#include <QDebug>
#include "../lib/mesh.hpp"
#include "../lib/tetgen.h"


Vector3d& normal(struct::Point3D_t<float> p1, struct::Point3D_t<float> p2, struct::Point3D_t<float> p3 ){

    Vector3d u(p2.x - p1.x, p2.y - p1.y ,p2.z - p1.z);
    Vector3d v(p3.x - p1.x, p3.y - p1.y ,p3.z - p1.z);

    Vector3d normal(0,0,0);

    normal.cross(u, v);
    normal.normalize();

    return normal;
}



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

    //dessine le nuage de point
    Delaunay_it(NodeRoot, name, mask);
    // initializeMask("mask", mask, name);
}


void ExampleApp::initializeMesh()
{

    std::string file_out="../resources/Campan_MethodeHB_Seuil_970_Plus60_thinning_sliceBranchePropre2.bmi3d";
    Examen* exam=tmpLoadData( file_out);

    std::string name = "scene";

    Ogre::SceneNode* NodeRoot = Ogre::Root::getSingleton().getSceneManager(name)->getRootSceneNode();

    Volume* data=exam->getImage();
    DrawBoundingBox(NodeRoot,"boundingBox", data );
    Mask3d* mask=exam->getMask();
    Delaunay_it(NodeRoot, name, mask);

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
    int height=mask->getHeight(); //out.save_nodes("mesh");
    //out.save_elements("mesh");
    //out.save_faces("mesh");
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

void ExampleApp::DrawMask_3DScene(Ogre::SceneNode*parent,std::string name,Mask3d* mask){

    Ogre::SceneNode* NodeMask = parent->createChildSceneNode();
    Ogre::ManualObject* m_ManualObject=m_sceneManager->createManualObject(name);
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
    NodeMask->attachObject(m_ManualObject);

}

void ExampleApp::DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name,Mesh* mesh){

    /// Create the mesh via the MeshManager
    Ogre::MeshPtr msh = Ogre::MeshManager::getSingleton().createManual("ColourCube", "General");

    /// Create one submesh
    Ogre::SubMesh* sub = msh->createSubMesh();

    /// Define the vertices (8 vertices, each consisting of 2 groups of 3 floats
    const size_t nVertices = mesh->getNbVertice();
    const size_t vbufCount = 3*2*nVertices;
    float vertices[vbufCount];
    int indexVBuf=0;
    int indexVertice=0;
    int indexNormale=0;
    int indexColor=0;
    Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
    Ogre::RGBA colours[nVertices];
    Ogre::RGBA *pColour = colours;

    for(int i=0;i<mesh->getNbVertice();++i){

        //vertice
        vertices[indexVBuf]=mesh->getVerticeValue(indexVertice);indexVBuf++;indexVertice++;
        vertices[indexVBuf]=mesh->getVerticeValue(indexVertice);indexVBuf++;indexVertice++;
        vertices[indexVBuf]=mesh->getVerticeValue(indexVertice);indexVBuf++;indexVertice++;

        //normal
        vertices[indexVBuf]=mesh->getNormaleValue(indexNormale);indexVBuf++;indexNormale++;
        vertices[indexVBuf]=mesh->getNormaleValue(indexNormale);indexVBuf++;indexNormale++;
        vertices[indexVBuf]=mesh->getNormaleValue(indexNormale);indexVBuf++;indexNormale++;

        //colour (Use render system to convert colour value since colour packing varies)
        if(mesh->getColorRef()!=NULL){
            float r=mesh->getColorValue(indexColor);indexColor++;
            float g=mesh->getColorValue(indexColor);indexColor++;
            float b=mesh->getColorValue(indexColor);indexColor++;
            rs->convertColourValue(Ogre::ColourValue(r,g,b), pColour++);
        }else{
            rs->convertColourValue(Ogre::ColourValue(1,0.4,0.), pColour++);
        }

    }


    /// Define 12 triangles (two triangles per cube face)
    /// The values in this table refer to vertices in the above table
    const size_t ibufCount = mesh->getSizeFace();

    unsigned short faces[ibufCount];
    int indexFace=0;
    for(int i=0;i<mesh->getNbFace();++i){
        //définit 1 triangle
        faces[indexFace]=mesh->getFaceIndex(indexFace);indexFace++;
        faces[indexFace]=mesh->getFaceIndex(indexFace);indexFace++;
        faces[indexFace]=mesh->getFaceIndex(indexFace);indexFace++;
    }

    /// Create vertex data structure for 8 vertices shared between submeshes
    msh->sharedVertexData = new Ogre::VertexData();
    msh->sharedVertexData->vertexCount = nVertices;

    /// Create declaration (memory format) of vertex data
    Ogre::VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
    size_t offset = 0;
    // 1st buffer
    decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
    decl->addElement(0, offset, Ogre::VET_FLOAT3, Ogre::VES_NORMAL);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_FLOAT3);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount)
    /// and bytes per vertex (offset)
    Ogre::HardwareVertexBufferSharedPtr vbuf =
            Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                offset, msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), vertices, true);

    /// Set vertex buffer binding so buffer 0 is bound to our vertex buffer
    Ogre::VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding;
    bind->setBinding(0, vbuf);

    // 2nd buffer
    offset = 0;
    decl->addElement(1, offset, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
    offset += Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR);
    /// Allocate vertex buffer of the requested number of vertices (vertexCount)
    /// and bytes per vertex (offset)
    vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
                offset, msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);
    /// Upload the vertex data to the card
    vbuf->writeData(0, vbuf->getSizeInBytes(), colours, true);

    /// Set vertex buffer binding so buffer 1 is bound to our colour buffer
    bind->setBinding(1, vbuf);

    /// Allocate index buffer of the requested number of vertices (ibufCount)
    Ogre::HardwareIndexBufferSharedPtr ibuf = Ogre::HardwareBufferManager::getSingleton().
            createIndexBuffer(
                Ogre::HardwareIndexBuffer::IT_16BIT,
                ibufCount,
                Ogre::HardwareBuffer::HBU_STATIC_WRITE_ONLY);

    /// Upload the index data to the card
    ibuf->writeData(0, ibuf->getSizeInBytes(), faces, true);

    /// Set parameters of the submesh
    sub->useSharedVertices = true;
    sub->indexData->indexBuffer = ibuf;
    sub->indexData->indexCount = ibufCount;
    sub->indexData->indexStart = 0;

    /// Set bounding information (for culling)
    msh->_setBounds(Ogre::AxisAlignedBox(-100,-100,-100,100,100,100));
    msh->_setBoundingSphereRadius(Ogre::Math::Sqrt(3*100*100));

    /// Notify -Mesh object that it has been loaded
    msh->load();

    Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
                "Test/ColourTest", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
    material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_AMBIENT);

    Ogre::Entity* thisEntity = m_sceneManager->createEntity("cc", "ColourCube");
    thisEntity->setMaterialName("Test/ColourTest");
    Ogre::SceneNode* thisSceneNode = parent->createChildSceneNode();
    thisSceneNode->setPosition(-35, 0, 0);
    thisSceneNode->attachObject(thisEntity);
}

Point3D_t<float>* ExampleApp::produitVec(Point3D_t<float> A,Point3D_t<float> B,Point3D_t<float> C)
{
    Point3D_t<float> vecAB(B.x-A.x,B.y-A.y,B.z-A.z);
    Point3D_t<float> vecBC(C.x-A.x,C.y-A.y,C.z-A.z);
    Point3D_t<float>* ProdVect=new Point3D_t<float> (vecAB.y*vecBC.z-vecAB.z*vecBC.y,
                                                     vecAB.z*vecBC.x-vecAB.x*vecBC.z,
                                                     vecAB.x*vecBC.y-vecAB.y*vecBC.x);

    return ProdVect;
}

void ExampleApp::Delaunay_it(Ogre::SceneNode*parent,std::string name,Mask3d* mask){

    Mesh* mesh = new Mesh(mask);
    //Mesh * mesh = new Mesh();
    //mesh->test();

    //calcul de Delaunay
    tetgenio in, out;
    //int i;

    MiTimer* t2=new MiTimer();
    t2->start();
    // All indices start from 1.
    in.firstnumber = 1;

    in.numberofpoints = mesh->getNbVertice();

    int sizeTabVertice=mesh->getNbVertice()*3;
    cout<<"numberofpoints:"<<mesh->getNbVertice() <<" sizeTab: "<< sizeTabVertice<<endl;
    in.pointlist = new REAL[sizeTabVertice];
    for(int i=0;i<sizeTabVertice;++i)
    {
        // creation d'un noeud
        in.pointlist[i] = mesh->getVerticeValue(i);
    }

    t2->stop("chargement point dans model tetgen: ");
    cout<<"start tetrahedralize"<<endl;
    tetgenbehavior b;
    //char *switches="pq1.414a0.1";
    char *switches="Qv";
    if (!b.parse_commandline(switches)) {
        terminatetetgen(1);
    }

    MiTimer* t3=new MiTimer();
    t3->start();
    tetrahedralize(&b, &in, &out);
    t3->stop("tetrahedralize: ");

    cout<<"numberoftetrahedra:"<< out.numberoftetrahedra<<" numberofcorners:"<< out.numberofcorners<<" numberoftetrahedronattributes:"<<out.numberoftetrahedronattributes<<endl;
    for (int i = 0; i < 3; i++) {
        cout<<"indexs["<<i + out.firstnumber<<"]=";
        for (int j = 0; j < out.numberofcorners; j++) {
            cout<<" indice Corner"<<out.tetrahedronlist[i * out.numberofcorners + j]<<","<<endl;
            int indiceVertex=out.tetrahedronlist[i * out.numberofcorners + j];
            for (int j = 0; j < 3; j++) {
                cout<<" Composante point "<< out.pointlist[indiceVertex+j]<<",";
            }
            cout<<endl;
        }

        cout<<endl;
    }

    cout<<"numberoffacetconstraints "<<out.numberoffacetconstraints<<endl;
    cout<<"numberoftrifaces "<<out.numberoftrifaces<<endl;
    cout<<"numberofvedges "<<out.numberofvedges<<endl;
    cout<<"numberofvfacets "<<out.numberofvfacets<<endl;
    cout<<"numberofcorners "<<out.numberofcorners<<endl;
    cout<<"numberofedges "<<out.numberofedges<<endl;
    cout<<"numberoffacets "<<out.numberoffacets<<endl;
    cout<<"numberofholes "<<out.numberofholes<<endl;
    cout<<"numberofpbcgroups "<<out.numberofpbcgroups<<endl;
    cout<<"numberofpointattributes "<<out.numberofpointattributes<<endl;
    cout<<"numberofpointmtrs "<<out.numberofpointmtrs<<endl;
    // cout<<"numberofpointpairs "<<out.numberofpointpairs<<endl;
    cout<<"numberofpoints "<<out.numberofpoints<<endl;
    cout<<"numberofregions "<<out.numberofregions<<endl;
    cout<<"numberofsegmentconstraints "<<out.numberofsegmentconstraints<<endl;
    cout<<"numberoftetrahedronattributes "<<out.numberoftetrahedronattributes<<endl;
    cout<<"numberoftrifaces "<<out.numberoftrifaces<<endl;
    cout<<"numberoffvcells"<<out.numberofvcells<<endl;
    cout<<"numberofvpoints "<<out.numberofvpoints<<endl;

    cout<<"numberoftrifaces: "<< out.numberoftrifaces<<endl;

    int nbtri = out.numberoftrifaces;
    int nbpts = out.numberofpoints;
    Point3D_t<float> faceTab[nbtri * 3];
    Point3D_t<float>* normalTab[nbtri];

    mesh->createTabFace(out.numberoftrifaces);

    for(int i = 0; i < nbtri; i++) {
        mesh->setface( out.trifacelist[i * 3]-1, out.trifacelist[i * 3+1]-1, out.trifacelist[i * 3+2]-1, i*3);

        Point3D_t<float> p[3];
        for (int j = 0; j < 3; ++j) {
            int tc = out.trifacelist[i*3+j];
            int pi = (tc-1)*3;
            p[j].x = out.pointlist[(pi+0)];
            p[j].y= out.pointlist[(pi+1)];
            p[j].z= out.pointlist[(pi+2)];
            cout << p[j].x << ":" << p[j].y << ":" << p[j].z << endl;
            faceTab[i*3+j] = p[j];
        }
        normalTab[i] = produitVec(p[0], p[1], p[2]);
        Vector3d* u = new Vector3d(normalTab[i]->x, normalTab[i]->y, normalTab[i]->z);
        u->normalize();
        Point3D_t<float>* pn = new Point3D_t<float>(u->x, u->y, u->z);
        normalTab[i] = pn;
    }

    Point3D_t<float> normalMoy[nbpts];


    for(int i = 0; i < nbpts*3; i+=3){
        std::vector< Point3D_t<float>* > adj;
        for(int j=0; j < nbtri * 3; j++){
            if(out.pointlist[i] == faceTab[j].x && out.pointlist[i+1] == faceTab[j].y && out.pointlist[i+2] == faceTab[j].z){
                adj.push_back(normalTab[(int)(j/3)]);
            }
        }

        Point3D_t<float> pnorm;
        pnorm.x =0;
        pnorm.y =0;
        pnorm.z =0;

        if(adj.size() > 0){
            for(int k=0; k<adj.size(); k++){

                pnorm.x += adj[k]->x;
                pnorm.y += adj[k]->y;
                pnorm.z += adj[k]->z;
            }

            pnorm.x = pnorm.x / adj.size();
            pnorm.y = pnorm.y / adj.size();
            pnorm.z = pnorm.z / adj.size();


            normalMoy[i/3].x = pnorm.x;
            normalMoy[i/3].y = pnorm.y;
            normalMoy[i/3].z = pnorm.z;
        }
        else{
            normalMoy[i/3].x = 0;
            normalMoy[i/3].y = 0;
            normalMoy[i/3].z = 0;
        }
    }


    mesh->createTabNormals(nbpts);
    mesh->createTabColours(nbpts);

    for(int i=0; i< nbpts*3; i+=3){
        mesh->setnormal(i,normalMoy[i/3].x);
        mesh->setnormal(i+1,normalMoy[i/3].y);
        mesh->setnormal(i+2,normalMoy[i/3].z);

        if(i%2 == 0)
            mesh->setcolour(i, 1.0);
        else mesh->setcolour(i,0.0);

    }

    //out.save_nodes("mesh");
    //out.save_elements("mesh");u
    //out.save_faces("mesh");
    DrawMesh_3DScene(parent,"mesh", mesh);

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

    initializeModel(exam,name);

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
