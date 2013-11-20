#ifndef MESH_HPP
#define MESH_HPP


#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FRONTALE 0
#define SAGITALE 1
#define TRANSVERSE 2



class Mesh
{
public:
    Mesh(int size){
        _x=NULL;
        _y= NULL;
        _z= NULL;
        _nx=NULL;
        _ny=NULL;
        _nz=NULL;
        _intensity=NULL;
        _amplitude=NULL;
        _size=size;
        _sizeIntensity=100;
        _sizeFaces=0;

        _x = new float[size];
        _y = new float[size];
        _z = new float[size];

        _nx = new float[size];
        _ny = new float[size];
        _nz = new float[size];

        _intensity = new float*[size];
        for(int i=0; i<size; ++i)
            _intensity[i] = new float[_sizeIntensity];

        _amplitude = new float[_size];
        _is3D=true;
    }

    ~Mesh(){
        delete[] _x;
        delete[] _y;
        delete[] _z;

        delete[] _nx;
        delete[] _ny;
        delete[] _nz;

        for(int i=0; i<_size; ++i)
            delete[] _intensity[i];
        delete[] _intensity;
        delete[] _amplitude;


    }


    //---------------------------------
    //Accesseur Type Image(image3D,2D)
    //---------------------------------

    inline void setXYZ(int index, float x, float y, float z)
    {
        _x[index] = x;
        _y[index] = y;
        _z[index] = z;
    }

    inline void setXYZNormal(int index, float nx, float ny, float nz)
    {
        _nx[index] = nx;
        _ny[index] = ny;
        _nz[index] = nz;
    }

    inline void clearFaces()
    {
        if (_p1 != NULL)
        {
            delete _p1;
            _p1 = NULL;
        }
        if (_p2 != NULL)
        {
            delete _p2;
            _p2 = NULL;
        }
        if (_p3 != NULL)
        {
            delete _p3;
            _p3 = NULL;
        }
    }



    //---------------------------------
    //Accesseur Type Image(image3D,2D)
    //---------------------------------


    bool is3D(){
        return _is3D;
    }

    void setDimension(bool value){
        _is3D=value;
    }

    int getTypeSlice(){
        return _TypeSlice;
    }

    void setTypeSlice(int value){
        _TypeSlice=value;
    }


    //---------------------------------
    //Accesseur resolutions
    //---------------------------------


    float getResX(){
        return _resX;
    }

    float getResY(){
        return _resY;
    }

    float getResZ(){
        return _resZ;
    }

    void setResX(float value){
        _resX=value;
    }

    void setResY(float value){
        _resY=value;
    }

    void setResZ(float value){
        _resZ=value;
    }

    void setRes(float valueX,float valueY,float valueZ){
        _resX=valueX;
        _resY=valueY;
        _resZ=valueZ;

    }



    //---------------------------------
    //Accesseur dimensions
    //---------------------------------
    int getWidth(){return _Width;}
    int getHeight(){return _Height;}
    int getDepth(){return _Depth;}
    void setWidth(int value){_Width=value;}
    void setHeight(int value){_Height=value;}
    void setDepth(int value){_Depth=value;}
    int getSizeGlobale(){return _Width*_Height*_Depth;}

    //---------------------------------
    //Accesseur Min Max
    //---------------------------------
    float getMinX(){return _MinX;}
    float getMinY(){return _MinY;}
    float getMinZ(){return _MinZ;}
    void setMinX(float value){_MinX=value;}
    void setMinY(float value){_MinY=value;}
    void setMinZ(float value){_MinZ=value;}

    float getMaxX(){return _MaxX;}
    float getMaxY(){return _MaxY;}
    float getMaxZ(){return _MaxZ;}
    void setMaxX(float value){_MaxX=value;}
    void setMaxY(float value){_MaxY=value;}
    void setMaxZ(float value){_MaxZ=value;}





    //------------------------------------------------
    //affichage pour controle console
    //------------------------------------------------
    void displayParameter(){
        std::cout<<"------------------------------------"<<std::endl;
        if(is3D())
            std::cout<<"             Mesh3D"<<std::endl;
        else
            std::cout<<"             Mesh2D"<<std::endl;
        std::cout<<"------------------------------------"<<std::endl;
        std::cout<<"taille pour x,y,z:"<<_size<<std::endl;
        std::cout<<"taille pour intensity:"<<_sizeIntensity<<std::endl;
        std::cout<<"MAX:"<<_MaxX<<", "<<_MaxY<<", "<<_MaxZ<<std::endl;
        std::cout<<"MIN:"<<_MinX<<", "<<_MinY<<", "<<_MinZ<<std::endl;
        std::cout<<"Res:"<<_resX<<", "<<_resY<<", "<<_resZ<<std::endl;
        std::cout<<"Taille:"<<_Width<<", "<<_Height<<", "<<_Depth<<std::endl;
        std::cout<<"Taille globale:"<<getSizeGlobale()<<std::endl;
    }

    void display(){
        std::cout<<"------------------------------------"<<std::endl;
        if(is3D())
            std::cout<<"             Mesh3D"<<std::endl;
        else
            std::cout<<"             Mesh2D"<<std::endl;
        std::cout<<"------------------------------------"<<std::endl;
        std::cout<<"taille pour x,y,z:"<<_size<<std::endl;
        for(int i=0;i<_size;++i){
            std::cout<<"Coord:"<<_x[i]<<", "<<_y[i]<<", "<<_z[i]<<std::endl;
            std::cout<<"     Normals:"<<_nx[i]<<", "<<_ny[i]<<", "<<_nz[i]<<std::endl;
            std::cout<<"     amplitude"<<_amplitude[i]<<std::endl;
            for(int j=0;j<_sizeIntensity;++j)
                std::cout<<"          intensity:"<<_intensity[i][j]<<std::endl;
        }

    }





    //---------------------------------
    //Accesseur Intensité
    //---------------------------------
    inline void setIntensity(int index, int indexIntensity, float value) { _intensity[index][indexIntensity] = value; }
    inline float getIntensity(int index, int indexIntensity) { return _intensity[index][indexIntensity]; }


    inline float getX(int index) { return _x[index]; }
    inline float getY(int index) { return _y[index]; }
    inline float getZ(int index) { return _z[index]; }

    inline float getNX(int index) { return _nx[index]; }
    inline float getNY(int index) { return _ny[index]; }
    inline float getNZ(int index) { return _nz[index]; }


    inline int getSize() { return _size; }
    inline int getSizeIntensity() { return _sizeIntensity; }
    inline int getSizeFace() { return _sizeFaces; }

    inline float getAmplitude(int index) { return _amplitude[index]; }
    inline void setAmplitude(int index, float value) { _amplitude[index] = value; }




    //------------------------------------------------
    //Calcul des contrasts
    //------------------------------------------------
    void compute()
    {
        computePixelForAmplitude(0);
    }


    //automatic contrast correction
    void computePixelForAmplitude(int index)
    {

        //calcul de l'amplitude pour index
        for(int i=0; i<_size; ++i)
            _amplitude[i] = _intensity[i][index];

        //calcul des extrema
        float valMax = _amplitude[0], valMin = _amplitude[0];
        for(int i=0; i<_size; ++i)
        {
            valMax = std::max(_amplitude[i], valMax);
            valMin = std::min(_amplitude[i], valMin);
        }

        //calcul de la correction de contrast
        for(int i=0; i<_size; ++i)
        {
            _amplitude[i] = ((_amplitude[i] - valMin) / (valMax - valMin));
        }


    }




    //------------------------------------------------
    //Calcul des faces
    //------------------------------------------------


    inline void initFaces(int size)
    {
        _sizeFaces = size;

        _p1 = new int[size];
        _p2 = new int[size];
        _p3 = new int[size];
    }

    inline void setFace(int index, int p1, int p2, int p3)
    {
        _p1[index] = p1;
        _p2[index] = p2;
        _p3[index] = p3;
    }

    inline int getP1(int index) { return _p1[index]; }
    inline int getP2(int index) { return _p2[index]; }
    inline int getP3(int index) { return _p3[index]; }





    //----------------------------------------------------
    //Equillibrium == Carte des coordonnées ordonnées
    //----------------------------------------------------


    void InitEquilibrium(int width,int height){
        _widthE=width;
        _heightE=height;
        _sizeE=width*height;
        _equilibrium=new int[_sizeE];
        memset(_equilibrium, -1, sizeof(int) * _sizeE);

    }

    void setEquilibrium(int index,int value){
        _equilibrium[index]=value;

    }

    int getEquilibrium(int index){
        return _equilibrium[index];

    }

    int getWidthEquilibrium(){return _widthE;}
    int getHeightEquilibrium(){return _heightE;}

    void setWidthEquilibrium(int w){ _widthE=w;}
    void setHeightEquilibrium(int h){ _heightE=h;}

    void cleanEquilibrium(){delete[] _equilibrium;_equilibrium=0;}

private:
    float *_x, *_y, *_z;
    int *_p1, *_p2, *_p3;


    float _resX,_resY,_resZ;
    float _MinX,_MinY,_MinZ;
    float _MaxX,_MaxY,_MaxZ;
    int _Width,_Height,_Depth;

    float *_nx, *_ny, *_nz;
    float **_intensity;
    float *_amplitude;

    int _size, _sizeIntensity, _sizeFaces;


    int* _equilibrium;
    int _widthE,_heightE,_sizeE;
    bool _is3D;
    int _TypeSlice;

};



#endif // MESH_HPP
