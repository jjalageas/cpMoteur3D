#ifndef IMAGE__H
#define IMAGE__H

#include "Image3d.hpp"
#include "Struct.hpp"

#include <cstring>

template<typename T> class Image3d;


template<typename T>
class Image
{
public:
    Image<T>(int width, int height)
        : img3d(width, height, 1)
    {}

    Image<T>(T* data, int width, int height)
        : img3d(data, width, height, 1)
    {}

    Image<T>(const Image<T>& img)
        : img3d(Image3d<T>(img.img3d))
    {}


public:
    //------------------------------
    // Accesseurs
    //------------------------------
    inline T* getData() { return img3d.getData(); }
    inline T* getDataCopy() { return img3d.getDataCopy(); }

    inline void setDataCopy(T* data) { eassert(data != NULL); img3d.setDataCopy(data); }
    inline void setData(T* data) { eassert(data != NULL); img3d.setData(data); }

    inline int getWidth() const { return img3d.getWidth(); }
    inline int getHeight() const { return img3d.getHeight(); }
    inline int getGlobalSize() const { return img3d.getGlobalSize(); }

    inline T get(int n) const { return img3d.get(n); }
    inline T get(int x, int y) const { return img3d.get(x, y, 0); }
    inline T get(Point2D_t<int>& p) const { return get(p.x, p.y); }

    inline void set(T val, int n) { img3d.set(val, n); }
    inline void set(T val, int x, int y) { img3d.set(val, x, y, 0); }
    inline void set(T val, Point2D_t<int>& p) { set(val, p.x, p.y); }

    inline T getMin() { return img3d.getMin(); }
    inline T getMax() { return img3d.getMax(); }

    //------------------------------
    // Contrôle la validité d'un pixel
    //------------------------------
    inline bool hold(int n) const { return img3d.hold(n); }
    inline bool hold(int x, int y) const { return img3d.hold(x, y, 0); }
    inline bool hold(Point2D_t<int>& p) const { return img3d.hold(p.x, p.y); }


private:
    Image3d<T> img3d;
};

typedef Image<bool> Mask2d;


#endif /* IMAGE__H */
