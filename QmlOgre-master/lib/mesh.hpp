#ifndef MESH_HPP
#define MESH_HPP


#include <AlgoVolume.h>
#include <Image3d.hpp>
#include "3D/StructuringElement.h"

class Mesh{

public:

    Mesh(Mask3d* mask){
        _minX=_minY=_minZ=0;
        _maxX=_maxY=_maxZ=0;
        _nbVertice=0;
        _normals=0;
        _nbFace=0;
        _colour=0;
        _face=0;
        _sizeFace=0;
        MaskIsocontour(mask, 1, 1, 1);

    }

    Mesh(){
        _minX=_minY=_minZ=0;
        _maxX=_maxY=_maxZ=0;
        _nbVertice=0;
        _nbFace=0;
        _nbVertice=0;
        _normals=0;
        _colour=0;
        _face=0;
        _sizeFace=0;
    }

    Mesh(float* vertice, float* normale, float*color, int nbVertice){
        _minX=_minY=_minZ=0;
        _maxX=_maxY=_maxZ=0;
        _nbVertice=nbVertice;
        _nbFace=0;
        _vertice=new float[_nbVertice*3];
        _normals=new float[_nbVertice*3];
        _colour=new float[_nbVertice*3];
    }



    void MaskIsocontour(Mask3d*mask, int num_se, int halfsize, int value)
    {
        int width=mask->getWidth();
        int height=mask->getHeight();
        int depth=mask->getDepth();


        StructuringElement3d*se = new StructuringElement3d(num_se, halfsize);
        int seSize = se->size();
        Mask3d* res=new Mask3d(width,height,depth);
        MiList<int>lstres;
        int size= mask->getGlobalSize();
        bool*tab=mask->getData();
        int nbPoint=0;

        //@COMMENT: recupere la liste des points à 1 dans l'image
        MiList<int>*lst=mask->TransformMapIntoListIndex1D(value);
        cout<<"nbPOInt origine"<<lst->size()<<endl;

        for(int i=0;i<lst->size();++i){
            //@COMMENT: conversion 1D->2D
            int firstCC=lst->get(i);
            Point3D_t<int>* pMask= mask->getPointFrom1DIndex(firstCC);

            int val=0;
            int nbVoisin=0;
            for (int l=0 ; l < seSize ; l++){
                Point3D_t<int> pse = se->getRef(l) ;
                Point3D_t<int> *p = new Point3D_t<int>(pse.x + pMask->x,
                                                       pse.y + pMask->y,
                                                       pse.z + pMask->z);
                int index1D=mask->getGlobalIndex(p);
                if (index1D>0 && index1D<size ){
                    nbVoisin++;
                    if(tab[index1D]==value)
                        val++;
                }
                delete p;
            }
            if(val!=nbVoisin){
                //@COMMENT: ==point de surface
                res->set(1,lst->get(i));
                lstres.add(lst->get(i));

                nbPoint++;
            }
            delete pMask;
        }

        delete lst;
        lst = NULL;


        _nbVertice=nbPoint;
        _vertice=new float[3*_nbVertice];

        int indexV=0;


        //test1
        _minX=_minY=_minZ=__INT32_MAX__;
        _maxX=_maxY=_maxZ=-__INT32_MAX__;

        for(int i=0;i<lstres.size();++i){

            //allocation du point
            Point3D_t<int>* p= res->getPointFrom1DIndex(lstres.get(i));
            _vertice[indexV]=p->x;indexV++;
            _vertice[indexV]=p->y;indexV++;
            _vertice[indexV]=p->z;indexV++;


            //calcul des min et max
            if(p->x<_minX)_minX=p->x;
            if(p->y<_minY)_minY=p->y;
            if(p->z<_minZ)_minZ=p->z;
            if(p->x>_maxX)_maxX=p->x;
            if(p->y>_maxY)_maxY=p->y;
            if(p->z>_maxZ)_maxZ=p->z;

            delete p;

        }

        _width=_maxX-_minX;
        _height=_maxY-_minY;
        _depth=_maxZ-_minZ;

    }

    float* getVerticeRef(){return _vertice;}
    float getVerticeValue(int i){return _vertice[i];}
    float getNormaleValue(int i){return _normals[i];}

    float* getColorRef(){return _colour;}
    float getColorValue(int i){return _colour[i];}
    unsigned short getFaceIndex(int i){return _face[i];}

    inline int getWidth(){return _width;}
    inline int getHeight()  { return _height; }
    inline int getDepth()  { return _depth; }
    inline int getGlobalSize()  { return _width*_height*_depth; }
    inline float getMinX(){return _minX; }
    inline float getMaxX(){return _maxX; }
    inline float getMinY(){return _minY; }
    inline float getMaxY(){return _maxY; }
    inline float getMinZ(){return _minZ; }
    inline float getMaxZ(){return _maxZ; }
    inline float getNbVertice(){return _nbVertice; }
    inline int getNbFace(){return _nbFace; }
    inline int getSizeFace(){return _sizeFace; }


    void createTabFace(int nbelement){_nbFace=nbelement;_sizeFace=nbelement*3;_face=new unsigned short[_sizeFace];}
    void setface(int s1,int s2,int s3,int index){_face[index]=s1;_face[index+1]=s2;_face[index+2]=s3;}

    void displayParameter(){
        std::cout<<"----------------------------------"<<std::endl;
        std::cout<<"      Mesh                "<<std::endl;
        std::cout<<"----------------------------------"<<std::endl;
        std::cout<<"width="<<getWidth()<<std::endl;
        std::cout<<"height="<<getHeight()<<std::endl;
        std::cout<<"depth="<<getDepth()<<std::endl;
        std::cout<<"size="<<getGlobalSize()<<std::endl;
        std::cout<<"MinX="<<getMinX()<<std::endl;
        std::cout<<"MaxX="<<getMaxX()<<std::endl;
        std::cout<<"MinY="<<getMinY()<<std::endl;
        std::cout<<"MaxY="<<getMaxY()<<std::endl;
        std::cout<<"MinZ="<<getMinZ()<<std::endl;
        std::cout<<"MaxZ="<<getMaxZ()<<std::endl;
        std::cout<<""<<std::endl;

        std::cout<<"nbVertice="<<getNbVertice()<<std::endl;

    }

    void test(){

         _nbVertice=8;
        _vertice=new float[_nbVertice*3];


        _vertice[0]= -100.0; _vertice[1]=100.0; _vertice[2]=-100.0;        //0 position
        _vertice[3]=100.0;_vertice[4]=100.0;_vertice[5]=-100.0;         //1 position
        _vertice[6]=100.0;_vertice[7]=-100.0;_vertice[8]=-100.0;        //2 position
        _vertice[9]=-100.0;_vertice[10]=-100.0;_vertice[11]=-100.0;       //3 position
        _vertice[12]=-100.0;_vertice[13]=100.0;_vertice[14]=100.0;        //4 position
        _vertice[15]=100.0;_vertice[16]=100.0;_vertice[17]=100.0;          //5 position
        _vertice[18]= 100.0;_vertice[19]=-100.0;_vertice[20]=100.0;        //6 position
        _vertice[21]=-100.0;_vertice[22]=-100.0;_vertice[23]=100.0;        //7 position

        _normals=new float[_nbVertice*3];
        const float sqrt13 = 0.577350269f;
        _normals[0]=-sqrt13; _normals[1]=sqrt13; _normals[2]=-sqrt13;        //0 normal
        _normals[3]=sqrt13;_normals[4]=sqrt13;_normals[5]=-sqrt13;         //1 normal
        _normals[6]=sqrt13;_normals[7]=-sqrt13;_normals[8]=-sqrt13;        //2 normal
        _normals[9]=-sqrt13;_normals[10]=-sqrt13;_normals[11]=-sqrt13;       //3 normal
        _normals[12]=-sqrt13;_normals[13]=sqrt13;_normals[14]=sqrt13;        //4 normal
        _normals[15]=sqrt13;_normals[16]=sqrt13;_normals[17]=sqrt13;          //5 normal
        _normals[18]= sqrt13;_normals[19]=-sqrt13;_normals[20]=sqrt13;        //6 normal
        _normals[21]=-sqrt13;_normals[22]=-sqrt13;_normals[23]=sqrt13;        //7 normal


        _colour=new float[_nbVertice*3];

        _colour[0]=1.0; _colour[1]=0.0; _colour[2]=0.0;        //0 colour
        _colour[3]=1.0;_colour[4]=1.0;_colour[5]=0.0;         //1 colour
        _colour[6]=0.0;_colour[7]=1.0;_colour[8]=0.0;        //2 colour
        _colour[9]=0.0;_colour[10]=0.0;_colour[11]=0.0;       //3 colour
        _colour[12]=1.0;_colour[13]=0.0;_colour[14]=1.0;        //4 colour
        _colour[15]=1.0;_colour[16]=1.0;_colour[17]=1.0;          //5 colour
        _colour[18]= 0.0;_colour[19]=1.0;_colour[20]=1.0;        //6 colour
        _colour[21]=0.0;_colour[22]=0.0;_colour[23]=1.0;        //7 colour

_nbFace=12;
_sizeFace=36;
        _face=new unsigned short[36];

        _face[0]=0; _face[1]=2; _face[2]=3;
        _face[3]=0;_face[4]=1;_face[5]=2;
        _face[6]=1;_face[7]=6;_face[8]=2;
        _face[9]=1;_face[10]=5;_face[11]=6;
        _face[12]=4;_face[13]=6;_face[14]=5;
        _face[15]=4;_face[16]=7;_face[17]=6;
        _face[18]= 0;_face[19]=7;_face[20]=4;
        _face[21]=0;_face[22]=3;_face[23]=7;
        _face[24]=0;_face[25]=5;_face[26]=1;
          _face[27]=0;_face[28]=4;_face[29]=5;
           _face[30]=2;_face[31]=7;_face[32]=3;
           _face[33]=2;_face[34]=6;_face[35]=7;

    }




private:

    float* _vertice;
    int _nbVertice;
    float* _normals;
    float* _colour;
    unsigned short* _face;
    int _sizeFace;
    int _nbFace;

    //definit la boundingBox
    int _minX;
    int _minY;
    int _minZ;
    int _maxX;
    int _maxY;
    int _maxZ;

    int _width;
    int _height;
    int _depth;

};

#endif // MESH_HPP
