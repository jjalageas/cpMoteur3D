#ifndef BOUNDINGBOX_H_
#define BOUNDINGBOX_H_

#include <Mesh.hpp>
#include <Triplet_t.hpp>


class BoundingBox
{
public:
    BoundingBox(Mesh *Meshs);
    BoundingBox(int width, int height, int depth);
    ~BoundingBox();

    inline float getXMin() { return _xMin; }
    inline float getYMin() { return _yMin; }
    inline float getZMin() { return _zMin; }
    inline float getXMax() { return _xMax; }
    inline float getYMax() { return _yMax; }
    inline float getZMax() { return _zMax; }

    inline float getXCenter() { return (_xMin + _xMax) * 0.5; }
    inline float getYCenter() { return (_yMin + _yMax) * 0.5; }
    inline float getZCenter() { return (_zMin + _zMax) * 0.5; }

    void Display();
    Triplet_t<int,int,int>* getSizes();
    void setSizeFromMesh(Mesh *Meshs);
    void setSize(int widthBoundingBox,int heightBoundingBox,int depthBoundingBox);

private:
    int _width,_height,_depth;
    float _xMin, _yMin, _zMin;
    float _xMax, _yMax, _zMax;
    int _xCenter, _yCenter, _zCenter;
};

#endif /* BOUNDINGBOX_H_ */
