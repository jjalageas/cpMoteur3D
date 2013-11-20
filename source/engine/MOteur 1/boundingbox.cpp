#include "boundingbox.h"

BoundingBox::BoundingBox(Mesh *Meshs)   
{
    _xMin=100000; _xMax=-100000;
    _yMin=100000; _yMax=-100000;
    _zMin=100000; _zMax=-100000;
    setSizeFromMesh(Meshs);
}


BoundingBox::BoundingBox(int width, int height, int depth)
{
    setSize( width, height, depth);
}


BoundingBox::~BoundingBox() { }


//Coordonnées depuis 0
void
BoundingBox::setSize(int width,int height,int depth)
{
    _xMin=0; _xMax=width;
    _yMin=0; _yMax=height;
    _zMin=0; _zMax=depth;
    _xCenter=(width)/2;
    _yCenter=(height)/2;
    _zCenter=(depth)/2;
    _width=width;
    _height=height;
    _depth=depth;
}


//Coordonnées Absolue
void
BoundingBox::setSizeFromMesh(Mesh *Meshs)
{
    std::cout<<"BoundingBox::setSizeFromMesh(Mesh *Meshs): "<<Meshs<<std::endl;
    _xMin=100000; _xMax=-100000;
    _yMin=100000; _yMax=-100000;
    _zMin=100000; _zMax=-100000;

    for(int i=0; i<Meshs->getSize()-1; i++)
    {
       // std::cout<<"Meshs->getX("<<i<<")="<<Meshs->getX(i)<<std::endl;
        //std::cout<<"Meshs->getY("<<i<<")="<<Meshs->getY(i)<<std::endl;
        //std::cout<<"Meshs->getZ("<<i<<")="<<Meshs->getZ(i)<<std::endl;
        float x = Meshs->getX(i);
        float y = Meshs->getY(i);
        float z = Meshs->getZ(i);

        if(x > _xMax)
            _xMax = x;
        if (x < _xMin)
            _xMin = x;

        if(y > _yMax)
            _yMax = y;
        if (y < _yMin)
            _yMin = y;

        if(z > _zMax)
            _zMax = z;
        if (z < _zMin)
            _zMin = z;
    }

    std::cout<<"BoundingBox::setSizeFromMesh:setCenter: "<<std::endl;
    _xCenter=(_xMax-_xMin)/2;
    _yCenter=(_yMax-_yMin)/2;
    _zCenter=(_zMax-_zMin)/2;

    std::cout<<"BoundingBox::setSizeFromMesh:setSize: "<<std::endl;
    _width=(int)_xMax-_xMin;
    _height=(int)_yMax-_yMin;
    _depth=(int)_zMax-_zMin;
}


Triplet_t<int,int,int>*
BoundingBox::getSizes()
{
    Triplet_t<int,int,int>*res = new Triplet_t<int,int,int>(_width,_height,_depth);
    return res;
}


void
BoundingBox::Display(){
    std::cout << "---------------------------------"<< std::endl;
    std::cout << "         Bounding Box            "<< std::endl;
    std::cout << "---------------------------------"<< std::endl;
    std::cout << "         MIN : " << _xMin << " " << _yMin << " " << _zMin << std::endl;
    std::cout << "         MAX : " << _xMax << " " << _yMax << " " << _zMax << std::endl;
    std::cout << "         Size : " << _width << " " << _height << " " << _depth << std::endl;
    std::cout << "         Center : " << _xCenter << " " <<_yCenter  << " " <<_zCenter  << std::endl;
}
