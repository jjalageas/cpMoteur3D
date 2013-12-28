
#ifndef MESHGENERATION_H
#define MESHGENERATION_H

#include "../lib/ogreengine.h"
#include <Examen.h>
#include <ParserManager.h>
#include <ParserMi3DBinary.h>
#include <SliceType.h>
#include <QtQuick/QQuickView>
#include <DebugDrawer.h>
#include <cameranodeobject.h>
#include <pcl/point_types.h>
#include <pcl/io/pcd_io.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/features/normal_3d.h>
#include <pcl/surface/gp3.h>
#include <pcl/io/vtk_io.h>

#include "../example/cameranodeobject.h"
#include "../lib/ogreitem.h"
#include "../lib/ogreengine.h"
#include "../lib/mesh.hpp"

class MeshGeneration : public QQuickView
{
public:

    static void Point_clouds(Ogre::SceneNode*parent,Mask3d* mask, Ogre::SceneManager* scene);
    static void DrawMask_3DScene(Ogre::SceneNode*parent,std::string name,Mask3d* mask, Ogre::SceneManager* scene);
    static void DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene);
    static void DrawTriangle(Point3D_t<float> p1,Point3D_t<float> p2,Point3D_t<float> p3,
                                  Point3D_t<float> n1,Point3D_t<float> n2,Point3D_t<float> n3, std::string name, Ogre::SceneManager* scene);
    static Point3D_t<float> produitVec(Point3D_t<float> A,Point3D_t<float> B,Point3D_t<float> C);
    static void CreateMeshManualLODLevel(char *mesh_name, double lod_distance, char *lod_mesh_name);
    static void DrawPointcloud(std::string name, const std::string resourcegroup, const int numpoints, float *parray, Ogre::SceneNode*parent, Ogre::SceneManager* scene);
    static void DrawMeshLstPoint(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene);
    static void DrawMeshStripLine(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene);
    static void DrawMeshStripTriangle(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene);
    static void DrawMeshFanTriangle(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene);
    static void DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name,Mesh* mesh,int type, Ogre::SceneManager* scene);
    static Ogre::ManualObject* CreateMesh(pcl::PolygonMesh inputMesh, pcl::PointCloud<pcl::PointNormal>::Ptr inputCloud, Ogre::SceneManager* scene);
    static Ogre::ManualObject* createManualObject(size_t vertexCount, size_t indicesCount, std::string materialName, Ogre::RenderOperation::OperationType operationType, Ogre::SceneManager* scene);
    static Ogre::ManualObject* CreatePointMesh(pcl::PointCloud<pcl::PointXYZ>::Ptr cloud, std::string materialName, Ogre::SceneManager* scene);
    static void meshSmoothing(Ogre::SceneNode*parent, Mask3d* mask, Ogre::SceneManager* scene);
    static Mesh* MeshSimplification(Mask3d* mask);
    static void Point_clouds_Simplified(Ogre::SceneNode*parent, Mask3d* mask, Ogre::SceneManager* scene);
    static void MeshLOD(int lod, Ogre::SceneNode*parent, Mask3d* mask, Ogre::SceneManager* scene);
    static void DrawEdge(Point3D_t<float> p1, Poin3D_t<float> p2);
};

#endif
