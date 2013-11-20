#include "primitiveGl.h"
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glext.h>
#include <GL/freeglut.h>

//---------------------------------------------------
//Primitive
//---------------------------------------------------

/*Point3D_t<int> PrimitiveGL:: RepereOpenGl(Point3D_t<int> A)
{
    return Point3D_t<int>(-A.x+p1.x,-A.z+p1.y,-A.y+p1.z );
}*/

//Modification de la fonction initiale
Point3D_Color_t<float> PrimitiveGL:: RepereOpenGl2(Point3D_Color_t<float> A)
{
    return Point3D_Color_t<float>( -A.x+p1.x, -A.z+p1.y, -A.y+p1.z,
                                   A.Red(), A.Green(), A.Blue());
}

/*void PrimitiveGL::setLstPointFromVolume(ImageSequence<char>*mask){
    //rappel p1=Point(w/2,d/2,h/2);
    //coordonne lst = x y z
    //coordonne en opengl = x z y

    _volume=new MiList<Point3D_t<int> >;
    int size=mask->getGlobalSize();
    for (int i=0;i<size;++i)
    {
        if(mask->get(i)==1)
        {
            Point3D_t<int>p=mask->getPoint3DFromIndex(i,mask->getWidth(),mask->getHeight());
            _volume->add(RepereOpenGl(p));
        }
    }
}*/

//Modification de la fonction initiale
bool PrimitiveGL::setLstPointFromVolume(MiList<Point3D_Color_t<float> *> * list)
{
    _vol = new MiList<Point3D_Color_t<float> >;
    int size=list->size();
    for (int i=0;i<size;++i)
    {
        Point3D_Color_t<float> * p = new Point3D_Color_t<float>(list->get(i)->x, list->get(i)->z, list->get(i)->y,
                                                                list->get(i)->Red(), list->get(i)->Green(), list->get(i)->Blue());
        _vol->add(RepereOpenGl2(*p));
    }
    return true;
}

void PrimitiveGL::setLstPointFromNode(MiList<Node *> nodes){
    //rappel p1=Point(w/2,d/2,h/2);
    //coordonne lst = x y z
    //coordonne en opengl = x z y

    _nodes=new MiList<Point3D_t<int> >;
    int size=nodes.size();
    for (int i=0;i<size;++i){
        Node*p=nodes.get(i);
        _nodes->add(Point3D_t<int>(-p->x+p1.x,-p->z+p1.y, -p->y+p1.z));
    }
}

//Permet de récupérer, sous forme d'image, ce qui est affiché dans le moteur 3D
GLvoid PrimitiveGL::copyScreen(const string & filename)
{
    GLint viewport[4] ;
    glGetIntegerv(GL_VIEWPORT, viewport);

    int width=viewport[2], height=viewport[3];

    ofstream file (filename.c_str (), ios::out|ios::binary);
    if (! file)
        cerr << "Cannot open file \"" << filename.c_str () << "\"!\n";
    else
    {
        file << "P6\n#\n" << width << ' ' << height << "\n255\n";

        glPixelStorei (GL_PACK_ALIGNMENT, 1);

        char * pixels = (char *)malloc((3 * width * height) * sizeof(char));
        glReadPixels (0, 0, width, height, GL_RGB, GL_UNSIGNED_BYTE, pixels);

        char * ppix = pixels + (3 * width * (height));
        for (unsigned int j = height; j-- ; ppix -= 3 * width) file.write (ppix, 3 * width);

        free(pixels);

        file.close ();
    }
}

GLvoid  PrimitiveGL::draw_xyz_repere()
{
    glBegin(GL_LINES);
    //axe X en rouge
    glColor3f(1.0,0.0,0.0);
    glVertex3f(-1000,0, 0);
    glVertex3f(1000,0, 0);

    //axe Y en vert
    glColor3f(0.0,1.0,0.0);
    glVertex3f(0,-1000, 0);
    glVertex3f(0,1000, 0);

    //axe Z en vert
    glColor3f(0.0,0.0,1.0);
    glVertex3f(0,0, -1000);
    glVertex3f(0, 0, 1000);

    //axe Z en vert
    glColor3f(1.0,1.0,1.0);
    glVertex3f(100,0, 0);
    glVertex3f(100, 0, 0);

    glEnd();
}

/*GLvoid PrimitiveGL::drawLine(MiList<Point3D_t<int> >* Line)
{
    double vert2[4] = {0, 0.78, 0, 1.0};
    glColor4dv(  vert2 );
    glPointSize (10.0);
    glBegin (GL_POINTS);

    for (int i=0;i<Line->size();++i){
        Point3D_t<int> T= RepereOpenGl(Line->get(i));
        glVertex3f( T.x, T.y, T.z );
    }
    glEnd();
}*/

/*GLvoid PrimitiveGL::drawingVolume()
{
    glPointSize (1.0);
    glColor3d(1, 0, 0);
    glBegin (GL_POINTS);

    for (int i=0;i<_volume->size();++i)
    {
        Point3D_t<int>p= _volume->get(i);
        glVertex3f(p.x ,p.y ,p.z );
    }
    glEnd();
}*/

//Modification de la fonction initiale
GLvoid PrimitiveGL::drawingVolume()
{
    glPointSize (0.5);
    glBegin (GL_POINTS);

    for (int i=0;i<_vol->size();++i)
    {
        Point3D_Color_t<float> p = _vol->get(i);
        glColor3d(((double)p.Red()/255), ((double)p.Green()/255), ((double)p.Blue()/255));
        glVertex3f(p.x ,p.z ,p.y );
    }
    glEnd();
    copyScreen(_name+"_Client3D_Streaming.ppm");
}

GLvoid PrimitiveGL::drawLstNode()
{
    glPointSize (1.0);
    glColor3d(1, 0.8, 0.2);
    glBegin (GL_POINTS);

    for (int i=0; i<_nodes->size();++i)
    {
        Point3D_t<int>p= _volume->get(i);
        glVertex3f(p.x ,p.y ,p.z );
    }
    glEnd();
}


//test des composantes
//void PrimitiveGL::DrawCC()
//{
//    for(int i=0;i< this->Composante->size();++i){




//        if(i==0){


//            double vert[4]= {0, 1, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }

//        if(i==1){


//            double vert[4]= {1, 0, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }

//        if(i==2){


//            double vert[4]= {0, 0, 1, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==3){


//            double vert[4]= {0, 0.8, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==4){


//            double vert[4]= {1, 0, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }

//        if(i==5){


//            double vert[4]= { 0.2,0, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==6){


//            double vert[4]= {0.4, 0, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==7){


//            double vert[4]= {0.6, 0, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==8){


//            double vert[4]= {0.8, 0, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==9){


//            double vert[4]= {0.2, 0.2, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==10){


//            double vert[4]= {0.4, 0.2, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==11){


//            double vert[4]= {0.6, 0.2, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i==12){


//            double vert[4]= {0.8, 0.2, 0, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//        if(i>12){


//            double vert[4]= {0.5, 0.2, 0.6, 1.0} ;

//            glColor4dv( vert  );
//            glPointSize (10.0);
//            glBegin (GL_POINTS);

//            for (int f=0;f<this->Composante->at(i)->size();++f){
//                Point T= RepereOpenGl(this->Composante->at(i)->at(f));
//                glVertex3f( T.x, T.y, T.z );

//            }

//            glEnd();
//        }
//    }





//}

//GLvoid PrimitiveGL::drawLstBranch(){

//    for (int i=0; i<lst->size();++i){
//        //glLoadName(i);
//        drawingLstNode(lst->at(i)->getlstNode());

//    }

//}



//GLvoid PrimitiveGL::drawingSkeleton(){


//    //cout<<"nb noeud="<<lst->size()<<endl;
//    QList<Node*> nodeq;
//    nodeq.append(new Node(*lst->first()) );
//    while ( !nodeq.isEmpty() ) {
//        Node *n = nodeq.first();

//        int i;
//        n->children.first();
//        for (i=0; i<n->children.size();++i) {
//            Node *child = n->children.at(i);
//            glColor3d(1, 1, 0);
//            glPointSize (10.0);

//            //dessin du pere et du fils
//            glBegin (GL_POINTS);
//            glVertex3f( -n->cx+p1.x, -n->cz+p1.y, -n->cy+p1.z );
//            glVertex3f(-child->cx+p1.x, -child->cz+p1.y, -child->cy+p1.z);
//            glEnd();


//            //dessin des lignes
//            glBegin( GL_LINES );
//            glVertex3f( -n->cx+p1.x, -n->cz+p1.y, -n->cy+p1.z );
//            glVertex3f(-child->cx+p1.x, -child->cz+p1.y, -child->cy+p1.z);
//            glEnd();

//            glPopName();
//            nodeq.append( child );
//        }
//        nodeq.removeFirst();
//    }

//}

void PrimitiveGL::drawScene(GLenum mode)
{
    if (mode == GL_SELECT)
    {
        if(SKELETON)
        {
            /*if(!lstBranch->isEmpty())
            {
                drawLstBranch(lstBranch);
            }*/
            if(LABEL)
            {
            }
            if(SIZE)
            {
            }
        }
    }
    if (mode == GL_RENDER)
    {

        if(REPERE)
        {
            glColor3d(0,1,0);
            draw_xyz_repere();
        }
        if(VOLUME)
        {
            drawingVolume();
        }
        if(SKELETON)
        {

        }
    }
}
