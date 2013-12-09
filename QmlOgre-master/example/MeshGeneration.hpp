
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

#include "../example/cameranodeobject.h"
#include "../lib/ogreitem.h"
#include "../lib/ogreengine.h"
#include "../lib/mesh.hpp"

class MeshGeneration : public QQuickView
{
public:

    static void Point_clouds(Ogre::SceneNode*parent,std::string name,Mask3d* mask, Ogre::SceneManager* scene);
    static void DrawMask_3DScene(Ogre::SceneNode*parent,std::string name,Mask3d* mask, Ogre::SceneManager* scene);
    static void DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name,Mesh* mesh, Ogre::SceneManager* scene);
    static void DrawTriangle(Point3D_t<float> p1,Point3D_t<float> p2,Point3D_t<float> p3,
                                  Point3D_t<float> n1,Point3D_t<float> n2,Point3D_t<float> n3, std::string name, Ogre::SceneManager* scene);
    static Point3D_t<float> produitVec(Point3D_t<float> A,Point3D_t<float> B,Point3D_t<float> C);
    static void CreateMeshManualLODLevel(char *mesh_name, double lod_distance, char *lod_mesh_name);
    static void DrawPointcloud(std::string name, const std::string resourcegroup, const int numpoints, float *parray, Ogre::SceneNode*parent, Ogre::SceneManager* scene);

};

#endif
