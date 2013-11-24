/*!
 * \copyright (c) Nokia Corporation and/or its subsidiary(-ies) (qt-info@nokia.com) and/or contributors
 * For the full copyright and license information, please view the LICENSE
 * file that was distributed with this source code.
 *
 * \license{This source file is part of QmlOgre abd subject to the BSD license that is bundled
 * with this source code in the file LICENSE.}
 */

#ifndef EXAMPLEAPP_H
#define EXAMPLEAPP_H

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

class ExampleApp : public QQuickView
{
    Q_OBJECT
public:
    explicit ExampleApp(QWindow *parent = 0);
    ~ExampleApp();

signals:
    void ogreInitialized();

public slots:

    Examen* tmpLoadData(std::string filename);

    void initializeModel(Examen* exam, std::string name);
    void initializeMesh();
    void initializeOgre();

    void initializeMask(std::string name,Mask3d* mask, std::string managerName);
    void initializeSkeleton(std::string ,Skeleton* );
    void DrawBoundingBox(Ogre::SceneNode*parent,std::string ,Volume* );

    void DrawCube(Ogre::SceneNode*parent,int width,int height,int depth);

    //void DrawCube(Ogre::SceneNode*parent,std::string name,int width,int height,int depth);
    void DrawLine(Ogre::SceneNode*parent,const Ogre::Vector3& start, const Ogre::Vector3& stop, const Ogre::ColourValue& col);
    void DrawGrid(Ogre::SceneNode*parent,int width, int height,int depth, int step_size);
    void LoadImageIntoTexture(Ogre::SceneNode*parent,std::string name,Image<float>* imagedata);
    void DrawMultiCube();
    void DrawMultiIcoSphere();
    void DrawMask_3DScene(Ogre::SceneNode*parent,std::string name,Mask3d* mask);
    void DrawMesh_3DScene(Ogre::SceneNode*parent,std::string name,Mesh* mesh);
    void Delaunay_it(Ogre::SceneNode*parent,std::string name,Mask3d* mask);
    Point3D_t<float>* produitVec(Point3D_t<float> A,Point3D_t<float> B,Point3D_t<float> C);
    void addContent();

private:

    OgreEngine *m_ogreEngine;
    CameraNodeObject *m_cameraObject;
    CameraNodeObject *m_cameraObject2;
    CameraNodeObject *m_cameraObject3;
    CameraNodeObject *m_cameraObject4;
    Ogre::SceneManager *m_sceneManager;
    Ogre::SceneManager *m_sceneManager2;
    Ogre::SceneManager *m_sceneManager3;
    Ogre::SceneManager *m_sceneManager4;
    Ogre::Root *m_root;
};

#endif // EXAMPLEAPP_H
