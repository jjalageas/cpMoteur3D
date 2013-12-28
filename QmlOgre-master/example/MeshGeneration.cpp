#include "MeshGeneration.hpp"
#include "Vector3d.h"
#include "Struct.hpp"

#include <QCoreApplication>
#include <QtQml/QQmlContext>
#include <QDir>
#include <QDebug>
#include <OgreMath.h>
#include "../lib/mesh.hpp"
#include "../lib/tetgen.h"
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/point_types.h>
#include <pcl/console/parse.h>
#include <pcl/surface/concave_hull.h>
#include <pcl/surface/simplification_remove_unused_vertices.h>
#include <pcl/surface/vtk_smoothing/vtk_mesh_smoothing_laplacian.h>
#include <pcl/surface/vtk_smoothing/vtk_utils.h>
#include <vtkSmartPointer.h>
#include <vtkSmoothPolyDataFilter.h>
#include <boost/lexical_cast.hpp>
#include <pcl/surface/vtk_smoothing/vtk_mesh_subdivision.h>
#include <pcl/surface/vtk_smoothing/vtk_utils.h>
#include <vtkLinearSubdivisionFilter.h>
#include <vtkLoopSubdivisionFilter.h>
#include <vtkButterflySubdivisionFilter.h>

#define LOW 0
#define REGULAR 1
#define HIGH 2


/*Code inspired by PCL tutorials from http://pointclouds.org/documentation/tutorials/greedy_projection.php#greedy-triangulation*/
void MeshGeneration::Point_clouds(Ogre::SceneNode*parent, Mask3d* mask, Ogre::SceneManager* scene){

    Mesh* mesh = new Mesh(mask);

    pcl::PointCloud<pcl::PointXYZ> cloud_strt;

    // Fill in the cloud data
    cloud_strt.width    = mesh->getWidth();
    cloud_strt.height   = mesh->getHeight();
    cloud_strt.is_dense = false;
    cloud_strt.points.resize (cloud_strt.width * cloud_strt.height);

    for (size_t i = 0; i < cloud_strt.points.size (); ++i)
    {
        cloud_strt.points[i].x = mesh->getVerticeValue(i*3);
        cloud_strt.points[i].y = mesh->getVerticeValue(i*3+1);
        cloud_strt.points[i].z = mesh->getVerticeValue(i*3+2);
    }

    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud_strt);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCLPointCloud2 cloud_blob;
    pcl::io::loadPCDFile ("test_pcd.pcd", cloud_blob);
    pcl::fromPCLPointCloud2 (cloud_blob, *cloud);

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);
    //* normals should not contain the point normals + surface curvatures

    // Concatenate the XYZ and normal fields*
    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
    //* cloud_with_normals = cloud + normals

    // Create search tree*
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud (cloud_with_normals);

    // Initialize objects
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh triangles;

    // Set the maximum distance between connected points (maximum edge length)
    gp3.setSearchRadius(5);

    // Set typical values for the parameters
    gp3.setMu(3);
    gp3.setMaximumNearestNeighbors(20);
    gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
    gp3.setMinimumAngle(M_PI/18); // 10 degrees
    gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
    gp3.setNormalConsistency(false);

    // Get result
    gp3.setInputCloud (cloud_with_normals);
    gp3.setSearchMethod (tree2);
    gp3.reconstruct (triangles);

    pcl::io::saveVTKFile("mesh_regular.vtk", triangles);

    Ogre::ManualObject* lManualObject = MeshGeneration::CreateMesh(triangles, cloud_with_normals, scene);
    parent->createChildSceneNode()->attachObject(lManualObject);


}


void MeshGeneration::meshSmoothing(Ogre::SceneNode*parent, Mask3d* mask, Ogre::SceneManager* scene){
    int start = clock();
    Mesh* mesh = new Mesh(mask);

    pcl::PointCloud<pcl::PointXYZ> cloud_strt;
    cloud_strt.width    = mesh->getWidth();
    cloud_strt.height   = mesh->getHeight();
    cloud_strt.is_dense = false;
    cloud_strt.points.resize (cloud_strt.width * cloud_strt.height);

    for (size_t i = 0; i < cloud_strt.points.size (); ++i)
    {
        cloud_strt.points[i].x = mesh->getVerticeValue(i*3);
        cloud_strt.points[i].y = mesh->getVerticeValue(i*3+1);
        cloud_strt.points[i].z = mesh->getVerticeValue(i*3+2);
    }

    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud_strt);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCLPointCloud2 cloud_blob;
    pcl::io::loadPCDFile ("test_pcd.pcd", cloud_blob);
    pcl::fromPCLPointCloud2 (cloud_blob, *cloud);

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);


    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);
    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud (cloud_with_normals);
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh triangles;

    gp3.setSearchRadius(5);
    gp3.setMu(3);
    gp3.setMaximumNearestNeighbors(20);
    gp3.setMaximumSurfaceAngle(M_PI/4);
    gp3.setMinimumAngle(M_PI/18);
    gp3.setMaximumAngle(2*M_PI/3);
    gp3.setNormalConsistency(false);

    gp3.setInputCloud (cloud_with_normals);
    gp3.setSearchMethod (tree2);
    gp3.reconstruct (triangles);

    vtkSmartPointer<vtkPolyData> vtk_polygons_;
    pcl::VTKUtils::convertToVTK (triangles, vtk_polygons_);

    // Apply the VTK algorithm
    vtkSmartPointer<vtkPolyDataAlgorithm> vtk_subdivision_filter;
    vtk_subdivision_filter = vtkLinearSubdivisionFilter::New ();
    vtk_subdivision_filter->SetInput (vtk_polygons_);
    vtk_subdivision_filter->Update ();

    pcl::PolygonMesh output;
    vtk_polygons_ = vtk_subdivision_filter->GetOutput ();

    pcl::VTKUtils::convertToPCL (vtk_polygons_, output);
    pcl::io::saveVTKFile("mesh_smooth.vtk", output);

    Ogre::ManualObject* lManualObject = MeshGeneration::CreateMesh(output, cloud_with_normals, scene);
    parent->createChildSceneNode()->attachObject(lManualObject);

}




Vector3d& normal(struct::Point3D_t<float> p1, struct::Point3D_t<float> p2, struct::Point3D_t<float> p3 ){

    Vector3d u(p2.x - p1.x, p2.y - p1.y ,p2.z - p1.z);
    Vector3d v(p3.x - p1.x, p3.y - p1.y ,p3.z - p1.z);

    Vector3d normal(0,0,0);

    normal.cross(u, v);
    normal.normalize();

    return normal;
}





void MeshGeneration::DrawMask_3DScene(Ogre::SceneNode*parent,std::string name,Mask3d* mask, Ogre::SceneManager* scene){

    Mesh* mesh = new Mesh(mask);

    pcl::PointCloud<pcl::PointXYZ> cloud_strt;

    // Fill in the cloud data
    cloud_strt.width    = mesh->getWidth();
    cloud_strt.height   = mesh->getHeight();
    cloud_strt.is_dense = false;
    cloud_strt.points.resize (cloud_strt.width * cloud_strt.height);

    for (size_t i = 0; i < cloud_strt.points.size (); ++i)
    {
        cloud_strt.points[i].x = mesh->getVerticeValue(i*3);
        cloud_strt.points[i].y = mesh->getVerticeValue(i*3+1);
        cloud_strt.points[i].z = mesh->getVerticeValue(i*3+2);
    }

    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud_strt);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCLPointCloud2 cloud_blob;
    pcl::io::loadPCDFile ("test_pcd.pcd", cloud_blob);
    pcl::fromPCLPointCloud2 (cloud_blob, *cloud);

    Ogre::ManualObject* lManualObject = CreatePointMesh(cloud, "pointCloud", scene);
    parent->createChildSceneNode()->attachObject(lManualObject);

}




void MeshGeneration::DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name, Mesh* mesh, Ogre::SceneManager* scene){

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

    unsigned short *faces = new unsigned short[ibufCount];
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
    ibuf->writeData(0, ibuf->getSizeInBytes(), &faces, true);

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

    Ogre::Entity* thisEntity = scene->createEntity("cc", "ColourCube");
    thisEntity->setMaterialName("Test/ColourTest");
    Ogre::SceneNode* thisSceneNode = parent->createChildSceneNode();
    thisSceneNode->setPosition(-35, 0, 0);
    thisSceneNode->attachObject(thisEntity);
}




Point3D_t<float> MeshGeneration::produitVec(Point3D_t<float> A,Point3D_t<float> B,Point3D_t<float> C)
{
    Point3D_t<float> vecAB(B.x-A.x,B.y-A.y,B.z-A.z);
    Point3D_t<float> vecBC(C.x-A.x,C.y-A.y,C.z-A.z);
    Point3D_t<float> ProdVect= Point3D_t<float> (vecAB.y*vecBC.z-vecAB.z*vecBC.y,
                                                     vecAB.z*vecBC.x-vecAB.x*vecBC.z,
                                                     vecAB.x*vecBC.y-vecAB.y*vecBC.x);

    return ProdVect;
}





void MeshGeneration::DrawTriangle(Point3D_t<float> p1,Point3D_t<float> p2,Point3D_t<float> p3,
                              Point3D_t<float> n1,Point3D_t<float> n2,Point3D_t<float> n3, std::string name, Ogre::SceneManager* scene){
    Ogre::ManualObject* lManualObject = NULL;
    Ogre::String lManualObjectName = "face" + name;
    cout << lManualObjectName << endl;
    lManualObject = scene->createManualObject(lManualObjectName);
    lManualObject->setDynamic(false);
    lManualObject->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_LIST);
        {

            lManualObject->position(p1.x, p1.y,p1.z);// a vertex
            lManualObject->colour(Ogre::ColourValue(0.0f, 1.0f, 0.0f, 1.0f));
            lManualObject->normal(n1.x, n1.y,n1.z);


            lManualObject->position(p2.x, p2.y,p2.z);// a vertex
            lManualObject->colour(Ogre::ColourValue(1.0f, 1.0f, 0.0f, 1.0f));
            lManualObject->normal(n2.x, n2.y,n2.z);


            lManualObject->position(p3.x, p3.y,p3.z);// a vertex
            lManualObject->colour(Ogre::ColourValue(1.0f, 0.0f, 0.0f, 1.0f));
            lManualObject->normal(n3.x, n3.y,n3.z);


            lManualObject->triangle(0,1,2);
        }
        lManualObject->end();

        Ogre::String lNameOfTheMesh = "myFace";
        lManualObject->convertToMesh(lNameOfTheMesh);

        Ogre::Entity* lEntity = scene->createEntity(lNameOfTheMesh);
        Ogre::MaterialPtr Material = Ogre::MaterialManager::getSingleton().create("text", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);

        //permet d'afficher des deux coté de la texture
        Material->getTechnique(0)->getPass(0)->setCullingMode( Ogre::CULL_NONE);
        Material->getTechnique(0)->getPass(0)->createTextureUnitState("GreenSkin.jpg");

        //Assign the new material to our plane entity.
        lEntity->setMaterialName("text");
        Ogre::SceneNode* lNode = scene->getRootSceneNode()->createChildSceneNode();
        lNode->attachObject(lEntity);

}




/*void MeshGeneration::CreateMeshManualLODLevel(char *mesh_name, double lod_distance, char *lod_mesh_name, )
{
   Ogre::MeshPtr mesh = Ogre::MeshManager::getSingleton().getByName(mesh_name);
   mesh->createManualLodLevel(lod_distance, lod_mesh_name);


}*/



void MeshGeneration::DrawPointcloud(std::string name, const std::string resourcegroup, const int numpoints, float *parray, Ogre::SceneNode*parent, Ogre::SceneManager* scene)
{

   Ogre::MeshPtr msh = Ogre::MeshManager::getSingleton().createManual(name, resourcegroup);
   Ogre::SubMesh* sub = msh->createSubMesh();


   msh->sharedVertexData = new Ogre::VertexData();
   msh->sharedVertexData->vertexCount = numpoints;


   Ogre::VertexDeclaration* decl = msh->sharedVertexData->vertexDeclaration;
   decl->addElement(0, 0, Ogre::VET_FLOAT3, Ogre::VES_POSITION);
   Ogre::HardwareVertexBufferSharedPtr vbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(
               decl->getVertexSize(0), msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

   vbuf->writeData(0, vbuf->getSizeInBytes(), parray, true);

   decl->addElement(1, 0, Ogre::VET_COLOUR, Ogre::VES_DIFFUSE);
   Ogre::HardwareVertexBufferSharedPtr cbuf = Ogre::HardwareBufferManager::getSingleton().createVertexBuffer(Ogre::VertexElement::getTypeSize(Ogre::VET_COLOUR),
                                                                         msh->sharedVertexData->vertexCount, Ogre::HardwareBuffer::HBU_DYNAMIC_WRITE_ONLY_DISCARDABLE);

   Ogre::RenderSystem* rs = Ogre::Root::getSingleton().getRenderSystem();
   Ogre::RGBA *colours = new Ogre::RGBA[numpoints];
   for(int i=0, k=0; i<numpoints*3, k<numpoints; i+=3, k++){
       rs->convertColourValue(Ogre::ColourValue(0.5f, 0.0f, 0.0f, 1.0f), &colours[k]);
   }

   cbuf->writeData(0, cbuf->getSizeInBytes(), colours, true);
   delete[] colours;

   Ogre::VertexBufferBinding* bind = msh->sharedVertexData->vertexBufferBinding;
   bind->setBinding(0, vbuf);
   bind->setBinding(1, cbuf);
   sub->useSharedVertices = true;
   sub->operationType = Ogre::RenderOperation::OT_POINT_LIST;
   msh->load();

   Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create(
               "Test/ColourTest", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
   material->getTechnique(0)->getPass(0)->setVertexColourTracking(Ogre::TVC_AMBIENT);
   Ogre::Entity* thisEntity = scene->createEntity(name, name);
   thisEntity->setMaterialName("Test/ColourTest");
   Ogre::SceneNode* thisSceneNode = parent->createChildSceneNode();
   thisSceneNode->setPosition(-35, 0, 0);
   thisSceneNode->attachObject(thisEntity);

}

void MeshGeneration::DrawMeshLstPoint(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene){
    Ogre::ManualObject* manual = scene->createManualObject(name);
    manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_POINT_LIST);

    for(int i=0;i<mesh->getNbVertice()*3;++i){
        manual->position(mesh->getVerticeValue(i),mesh->getVerticeValue(i+1) ,mesh->getVerticeValue(i+2));
    }


    manual->end();
    parent->createChildSceneNode()->attachObject(manual);
}

void MeshGeneration::DrawMeshStripLine(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene){
    Ogre::ManualObject* manual = scene->createManualObject(name);
    manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_STRIP);

    for(int i=0;i<mesh->getNbVertice()*3;++i){
        manual->position(mesh->getVerticeValue(i),mesh->getVerticeValue(i+1) ,mesh->getVerticeValue(i+2));
    }

    manual->end();
    parent->createChildSceneNode()->attachObject(manual);
}

void MeshGeneration::DrawMeshStripTriangle(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene){

    Ogre::ManualObject* manual = scene->createManualObject(name);
    manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_STRIP);

    // define vertex position of index 0..3
    manual->position(-100.0, -100.0, 0.0);
    manual->position( 100.0, -100.0, 0.0);
    manual->position( 100.0,  100.0, 0.0);
    manual->position(-100.0,  100.0, 0.0);

    // define usage of vertices by refering to the indexes
    manual->index(0);
    manual->index(1);
    manual->index(2);
    manual->index(3);
    manual->index(0);

    manual->end();
    parent->createChildSceneNode()->attachObject(manual);
}

void MeshGeneration::DrawMeshFanTriangle(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene){
    Ogre::ManualObject* manual = scene->createManualObject(name);
    manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_TRIANGLE_FAN);



    manual->end();
    parent->createChildSceneNode()->attachObject(manual);
}

void MeshGeneration::DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name,Mesh* mesh,int type, Ogre::SceneManager* scene){
    switch(type){
    case 0://list of point
        DrawMeshLstPoint(parent,name, mesh, scene);
        break;
    case 1://list of strip line
        DrawMeshStripLine(parent,name, mesh, scene);
        break;
    case 2://list of strip triangle
        DrawMeshStripTriangle(parent,name, mesh, scene);
        break;
    case 3://list of fan triangle
        DrawMeshFanTriangle(parent,name, mesh, scene);
        break;
    }

}


/*Following three methods taken from https://github.com/Chiru/ChiruAddons/blob/master/ObjectCaptureModule/MeshReconstructor/MeshConverter.cpp*/
Ogre::ManualObject* MeshGeneration::createManualObject(size_t vertexCount, size_t indicesCount, std::string materialName, Ogre::RenderOperation::OperationType operationType, Ogre::SceneManager* scene)
{
    Ogre::ManualObject *ogreManual = scene->createManualObject("ImportedMesh");

    ogreManual->clear();
    ogreManual->estimateVertexCount(vertexCount);
    ogreManual->estimateIndexCount(indicesCount);
    ogreManual->begin(materialName, operationType);
    ogreManual->setDynamic(true);

    return ogreManual;
}



Ogre::ManualObject* MeshGeneration::CreateMesh(pcl::PolygonMesh inputMesh, pcl::PointCloud<pcl::PointNormal>::Ptr inputCloud, Ogre::SceneManager* scene)
{
    pcl::PointCloud<pcl::PointNormal>::Ptr input_cloud = inputCloud;

    size_t vertexcount = input_cloud->points.size();
    size_t indicescount = 0;

    for (size_t i = 0; i < inputMesh.polygons.size(); i++)
                indicescount += inputMesh.polygons[i].vertices.size();

    Ogre::ManualObject *ogreManual = createManualObject(vertexcount, indicescount, "CapturedObject", Ogre::RenderOperation::OT_TRIANGLE_LIST, scene);


    if (indicescount > 0)
    {
        for (size_t i = 0; i < input_cloud->points.size(); i++)
        {
            ogreManual->position(input_cloud->points[i].x, input_cloud->points[i].y, input_cloud->points[i].z);

            Ogre::Real r = rand() % 255;
            Ogre::Real g = rand() % 255;
            Ogre::Real b = rand() % 255;
            ogreManual->colour(r, g, b);

            ogreManual->normal(input_cloud->points[i].data_c[0], input_cloud->points[i].data_c[1], input_cloud->points[i].data_c[2]);
        }

        for (size_t i = 0; i < inputMesh.polygons.size(); i++)
        {
            for (size_t j = 0; j < inputMesh.polygons[i].vertices.size(); j++)
            {
                int index = inputMesh.polygons[i].vertices[j];
                ogreManual->index(index);
            }
        }
        ogreManual->end();

        return ogreManual;
    }


}

/*Point cloud display through manual object*/
Ogre::ManualObject* MeshGeneration::CreatePointMesh(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string materialName, Ogre::SceneManager* scene)
{
    size_t vertexcount = cloud->points.size();

    Ogre::ManualObject *ogreManual = createManualObject(vertexcount, vertexcount, materialName, Ogre::RenderOperation::OT_POINT_LIST, scene);

    for (size_t i = 0; i < cloud->points.size(); i++)
    {
        ogreManual->position(cloud->points[i].x, cloud->points[i].y, cloud->points[i].z);
        ogreManual->colour(Ogre::ColourValue(0.5f, 0.0f, 0.0f, 1.0f));
        ogreManual->index(i);
    }

    ogreManual->end();

    return ogreManual;
}

/*Point removal from point cloud*/
Mesh* MeshGeneration::MeshSimplification(Mask3d* mask){

    Mesh* mesh = new Mesh(mask);
    int newNbVertice = mesh->getNbVertice()/8;
    float* newTabVertice=new float[newNbVertice*3];

    for(int i=0; i<newNbVertice*3; i+=3){
        newTabVertice[i]=mesh->getVerticeValue(i*8);
        newTabVertice[i+1]=mesh->getVerticeValue(i*8+1);
        newTabVertice[i+2]=mesh->getVerticeValue(i*8+2);
    }

    mesh->setNbVertice(newNbVertice);
    mesh->setTabVertices(newTabVertice);

    return mesh;
}


/*Simplified meshing through point removal*/
void MeshGeneration::Point_clouds_Simplified(Ogre::SceneNode*parent,Mask3d* mask, Ogre::SceneManager* scene){

    Mesh* mesh = MeshGeneration::MeshSimplification(mask);

    pcl::PointCloud<pcl::PointXYZ> cloud_strt;

    cloud_strt.width    = mesh->getWidth();
    cloud_strt.height   = mesh->getHeight();
    cloud_strt.is_dense = false;
    cloud_strt.points.resize (cloud_strt.width * cloud_strt.height);

    for (size_t i = 0; i < cloud_strt.points.size (); ++i)
    {
        cloud_strt.points[i].x = mesh->getVerticeValue(i*3);
        cloud_strt.points[i].y = mesh->getVerticeValue(i*3+1);
        cloud_strt.points[i].z = mesh->getVerticeValue(i*3+2);
    }

    pcl::io::savePCDFileASCII ("test_pcd.pcd", cloud_strt);

    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud (new pcl::PointCloud<pcl::PointXYZ>);
    pcl::PCLPointCloud2 cloud_blob;
    pcl::io::loadPCDFile ("test_pcd.pcd", cloud_blob);
    pcl::fromPCLPointCloud2 (cloud_blob, *cloud);

    pcl::NormalEstimation<pcl::PointXYZ, pcl::Normal> n;
    pcl::PointCloud<pcl::Normal>::Ptr normals (new pcl::PointCloud<pcl::Normal>);
    pcl::search::KdTree<pcl::PointXYZ>::Ptr tree (new pcl::search::KdTree<pcl::PointXYZ>);
    tree->setInputCloud (cloud);
    n.setInputCloud (cloud);
    n.setSearchMethod (tree);
    n.setKSearch (20);
    n.compute (*normals);

    pcl::PointCloud<pcl::PointNormal>::Ptr cloud_with_normals (new pcl::PointCloud<pcl::PointNormal>);
    pcl::concatenateFields (*cloud, *normals, *cloud_with_normals);

    pcl::search::KdTree<pcl::PointNormal>::Ptr tree2 (new pcl::search::KdTree<pcl::PointNormal>);
    tree2->setInputCloud (cloud_with_normals);
    pcl::GreedyProjectionTriangulation<pcl::PointNormal> gp3;
    pcl::PolygonMesh triangles;

    gp3.setSearchRadius(50);

    gp3.setMu(3);
    gp3.setMaximumNearestNeighbors(50);
    gp3.setMaximumSurfaceAngle(M_PI/4);
    gp3.setMinimumAngle(M_PI/18);
    gp3.setMaximumAngle(2*M_PI/3);
    gp3.setNormalConsistency(false);

    gp3.setInputCloud (cloud_with_normals);
    gp3.setSearchMethod (tree2);
    gp3.reconstruct (triangles);

    pcl::io::saveVTKFile("mesh_simplified.vtk", triangles);

    Ogre::ManualObject* lManualObject = MeshGeneration::CreateMesh(triangles, cloud_with_normals, scene);
    parent->createChildSceneNode()->attachObject(lManualObject);

}

/*Mesh switch for level of detail*/
void MeshGeneration::MeshLOD(int lod, Ogre::SceneNode*parent, Mask3d* mask, Ogre::SceneManager* scene){

    switch(lod){

    case LOW:
        MeshGeneration::Point_clouds_Simplified(parent, mask, scene);
        break;
    case REGULAR:
        MeshGeneration::Point_clouds(parent, mask, scene);
        break;
    case HIGH:
        MeshGeneration::meshSmoothing(parent, mask, scene);
        break;
    }
}

/*Draws blue edges to be used along with draw triangle*/
void MeshGeneration::DrawEdge(Point3D_t<float> p1, Point3D_t<float> p2, Ogre::SceneManager* scene){

    Ogre::ManualObject* manual = scene->createManualObject("manual");
    manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);

    manual->position(p1.x, p1.y, p1.z);
    manual->colour((Ogre::ColourValue(0.,1.,0.)));
    manual->position(p2.x, p2.y, p2.z);
    manual->colour((Ogre::ColourValue(0.,1.,0.)));

    manual->end();
    scene->getRootSceneNode()->attachObject(manual);

}
