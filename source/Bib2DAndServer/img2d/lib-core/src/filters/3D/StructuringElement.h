#ifndef STRUCTURING_ELEMENT_H
#define STRUCTURING_ELEMENT_H

#include <map>
#include <Struct.hpp>
#include <Image3d.hpp>
#include <cmath>

//#include <RessourceManager.h>

using namespace std;

/* -----------------------------------------------------------------------------------------------------
  ELEMENT STRUCTURANT
 -----------------------------------------------------------------------------------------------------*/

class StructuringElement2d : public MiList<Point2D_t<int> >
{
public:

    StructuringElement2d (int numSE, int halfsize)
    {
        Point2D_t<int> p;

        switch(numSE)
        {
        case 0 : // Diamond (4-connexity)
            for (p.y=0 ; p.y <= halfsize ; p.y++)
                for (p.x=halfsize-p.y ; p.x<=halfsize+p.y ; p.x++)
                {
                addSE(p.x-halfsize, p.y-halfsize);
                addSE(p.x-halfsize, halfsize-p.y);
            }
            break;
        case 1:  // Square (8-connexity)
            for (p.y = 0 ; p.y < 2 * halfsize+1 ; p.y++)
                for (p.x = 0 ; p.x < 2 * halfsize+1 ; p.x++)
                {
                addSE(p.x-halfsize, p.y-halfsize);
            }
            break;
        case 2: // Circle
            for(p.x=0 ; p.x <= halfsize ; p.x++)
            {
                double radius = sqrt(pow(halfsize, 2) - pow(p.x, 2));
                for(p.y=0 ; p.y <= radius ; p.y++)
                {
                    addSE(p.x, p.y);
                    if (p.x>0) addSE(-p.x, p.y);
                    if (p.y>0) addSE(p.x, -p.y);
                    if (p.x>0 && p.y>0) addSE(-p.x, -p.y);
                }
            }
            break;
        case 3:  // Horizontal line.
            for(p.x = -halfsize ; p.x <= halfsize ; p.x++)
                addSE(p.x, 0);
            break;
        case 4:  // Vertical line
            for(p.y = -halfsize ; p.y<= halfsize ; p.y++)
                addSE(0, p.y);
            break;
        }
    }

    ~StructuringElement2d()
    {
        empty();
    }

private:

    void addSE (int x, int y)
    {
        bool flag = true;
        for (int i=0 ; i < size() ; i++)
        {
            Point2D_t<int> &pp = getRef(i);
            flag &= !( (pp.x == x) && (pp.y == y) );
        }
        if (flag) add(Point2D_t<int>(x, y));
    }
};

// -------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------------------------------------------------

class StructuringElement3d : public MiList<Point3D_t<int> >
{
public:

    StructuringElement3d (int numSE, int halfsize)
    {
        Point3D_t<int> p;
        int length = 2 * halfsize + 1;
        Image3d<bool> temp(length, length, length);

        switch(numSE)
        {
        case 0 : // Bipyramid
            {
                temp.initialize();
                for (p.z=0 ; p.z <= halfsize ; p.z++)
                {
                    for (p.y=0 ; p.y <= p.z ; p.y++)
                    {
                        for (p.x=0 ; p.x <= p.y ; p.x++)
                        {
                            temp.set(true, halfsize-p.x, halfsize-p.z+p.y, p.z);
                            temp.set(true, halfsize+p.x, halfsize-p.z+p.y, p.z);
                            temp.set(true, halfsize+p.x, halfsize+p.z-p.y, p.z);
                            temp.set(true, halfsize-p.x, halfsize+p.z-p.y, p.z);
                            temp.set(true, halfsize-p.x, halfsize-p.z+p.y, 2*halfsize-p.z);
                            temp.set(true, halfsize+p.x, halfsize-p.z+p.y, 2*halfsize-p.z);
                            temp.set(true, halfsize+p.x, halfsize+p.z-p.y, 2*halfsize-p.z);
                            temp.set(true, halfsize-p.x, halfsize+p.z-p.y, 2*halfsize-p.z);
                        }
                    }
                }
                addMask(temp, halfsize, length);
            }
            break;
        case 1 : // Cube
            {
                temp.initialize(1);
                addMask(temp, halfsize, length);
            }
            break;
        case 2 : // Sphere
            {
                for (p.z=0 ; p.z <= halfsize ; p.z++)
                {
                    for (p.x=0 ; p.x <= p.z ; p.x++)
                    {
                        double radius = sqrt(pow(p.z, 2) - pow(p.x, 2));
                        for (p.y=0 ; p.y <= radius ; p.y++)
                        {
                            temp.set(true, halfsize+p.x, halfsize+p.y, p.z);
                            temp.set(true, halfsize-p.x, halfsize+p.y, p.z);
                            temp.set(true, halfsize+p.x, halfsize-p.y, p.z);
                            temp.set(true, halfsize-p.x, halfsize-p.y, p.z);
                            temp.set(true, halfsize+p.x, halfsize+p.y, 2*halfsize-p.z);
                            temp.set(true, halfsize-p.x, halfsize+p.y, 2*halfsize-p.z);
                            temp.set(true, halfsize+p.x, halfsize-p.y, 2*halfsize-p.z);
                            temp.set(true, halfsize-p.x, halfsize-p.y, 2*halfsize-p.z);
                        }
                    }
                }
                addMask(temp, halfsize, length);
            }
            break;
        case 3:  // Horizontal line x-coordinate.
            for (int x =-halfsize ; x <= halfsize ; x++)
                addSE(x, 0, 0);
            break;
        case 4:  // Horizontal line y-coordinate.
            for (int y=-halfsize ; y <= halfsize ; y++)
                addSE(0, y, 0);
            break;
        case 5:  // Horizontal line z-coordinate.
            for(int z=-halfsize; z<=halfsize; z++)
                addSE(0, 0, z);
            break;
        }
    }

    ~StructuringElement3d()
    {
        empty();
    }

private:

    void addMask(Image3d<bool> &temp, int halfsize, int length)
    {
        Point3D_t<int> p;
        for (p.z=0 ; p.z < length ; p.z++)
        {
            for (p.y=0 ; p.y < length ; p.y++)
            {
                for (p.x=0 ; p.x < length ; p.x++)
                {
                    if (temp.get(p) == true)
                        addSE(p.x - halfsize, p.y - halfsize, p.z - halfsize);
                }
            }
        }
    }

    void addSE (int x, int y, int z)
    {
        bool flag = true;
        for (int i=0 ; i < size() ; i++)
        {
            Point3D_t<int> &p = getRef(i);
            flag &= !( (p.x == x) && (p.y == y) && (p.z == z) );
        }
        if (flag)
            add(Point3D_t<int>(x, y, z));
    }
};

#endif
