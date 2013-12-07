#include "MeshGeneration.hpp"
#include "Vector3d.h"
#include "Struct.hpp"

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



void MeshGeneration::Point_clouds(Ogre::SceneNode*parent,std::string name,Mask3d* mask, Ogre::SceneManager* scene){

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
     gp3.setMaximumNearestNeighbors(10);
     gp3.setMaximumSurfaceAngle(M_PI/4); // 45 degrees
     gp3.setMinimumAngle(M_PI/18); // 10 degrees
     gp3.setMaximumAngle(2*M_PI/3); // 120 degrees
     gp3.setNormalConsistency(true);

     // Get result
     gp3.setInputCloud (cloud_with_normals);
     gp3.setSearchMethod (tree2);
     gp3.reconstruct (triangles);



     // Additional vertex information
    // std::vector<int> parts = gp3.getPartIDs();
    // std::vector<int> states = gp3.getPointStates();

     pcl::io::saveVTKFile("mesh610.vtk", triangles);


     // Write polygons
     // compute the correct number of values:
     size_t triangle_size = triangles.polygons.size ();
     size_t correct_number = triangle_size;
     for (size_t i = 0; i < triangle_size; ++i)
         correct_number += triangles.polygons[i].vertices.size ();

     cout << "\nPOLYGONS " << triangle_size << " " << correct_number << std::endl;
     // mesh->createTabFace(6880);
     //  mesh->createTabNormals(mesh->getNbVertice()+1);



     for (size_t i = 0; i < triangle_size; ++i)
     {
       cout << triangles.polygons[i].vertices.size () << " ";
       size_t j = 0;
       int indiceVertex0;
       int indiceVertex2;
       int indiceVertex3;
       for (j = 0; j < triangles.polygons[i].vertices.size () - 1; j+=3){
         cout << triangles.polygons[i].vertices[j] <<" ";
         cout << triangles.polygons[i].vertices[j+1] <<" ";
         cout << triangles.polygons[i].vertices[j+2] <<" ";
         cout << std::endl;

         indiceVertex0 = triangles.polygons[i].vertices[j];
         indiceVertex2 = triangles.polygons[i].vertices[j+1];
         indiceVertex3 = triangles.polygons[i].vertices[j+2];

         //mesh->setface(indiceVertex0, indiceVertex2, indiceVertex3, i);

         Point3D_t<float> pt1 = Point3D_t<float>(mesh->getVerticeValue(indiceVertex0*3),mesh->getVerticeValue(indiceVertex0*3+1),mesh->getVerticeValue(indiceVertex0*3+2));
         Point3D_t<float> pt2 = Point3D_t<float>(mesh->getVerticeValue(indiceVertex2*3),mesh->getVerticeValue(indiceVertex2*3+1),mesh->getVerticeValue(indiceVertex2*3+2));
         Point3D_t<float> pt3 = Point3D_t<float>(mesh->getVerticeValue(indiceVertex3*3),mesh->getVerticeValue(indiceVertex3*3+1),mesh->getVerticeValue(indiceVertex3*3+2));

         Point3D_t<float> normal = produitVec(pt1, pt2, pt3);
         Vector3d* u = new Vector3d(normal.x, normal.y, normal.z);
         u->normalize();
         normal = Point3D_t<float>(u->x, u->y, u->z);
         cout << triangles.polygons[i].vertices[j]*3 << endl;
         std::string name = boost::lexical_cast<string>(i);

         //  mesh->setnormal(triangles.polygons[i].vertices[j]*3, normal.x);
         //  mesh->setnormal(triangles.polygons[i].vertices[j]*3+1, normal.y);
         //  mesh->setnormal(triangles.polygons[i].vertices[j]*3+2, normal.z);

        // DrawTriangle(pt1, pt2, pt3, normal, normal, normal, name, scene);

       }

     }

     // for(int i=0; i<mesh->getNbVertice()*3; i++){
     //  if(mesh->getNormaleValue(i)>1 && mesh->getNormaleValue(i)<0)
     //     mesh->setnormal(i, 0);


     //  DrawMesh_3DScene(parent, "mesh", mesh);

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

    Ogre::SceneNode* NodeMask = parent->createChildSceneNode();
    Ogre::ManualObject* m_ManualObject=scene->createManualObject(name);
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
