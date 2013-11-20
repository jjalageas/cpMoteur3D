#ifndef IMAGE3D_H
#define IMAGE3D_H

#include "Image.hpp"
#include "Struct.hpp"
#include "SliceType.h"
#include <debug.h>

#include <cstring>

template<typename T> class Image;


template<typename T>
class Image3d
{
public:
    Image3d<T>(int width, int height, int depth)
        : _width(width), _height(height), _depth(depth),
          _wh(_width*_height), _max(0), _min(0), _outdatedMinMax(true)
    {
        _data = new T[getGlobalSize()];
        memset(_data, 0, getGlobalSize()*sizeof(T));
    }

    Image3d<T>(T* data, int width, int height, int depth)
        : _width(width), _height(height), _depth(depth),
          _wh(width*height), _max(0), _min(0), _outdatedMinMax(true)
    {
        _data = new T[getGlobalSize()];
        memcpy(_data, data, getGlobalSize()*sizeof(T));
    }

    Image3d<T>(const Image3d<T>& img)
        : _width(img._width), _height(img._height), _depth(img._depth),
          _wh(img._wh), _max(img._max), _min(img._min),
          _outdatedMinMax(img._outdatedMinMax)
    {
        _data = new T[getGlobalSize()];
        memcpy(_data, img._data, getGlobalSize()*sizeof(T));
    }

    ~Image3d ()
    {
        delete[] _data;
        _data = NULL;
    }

    void initialize(T val = 0)
    {
        memset(_data, val, getGlobalSize()*sizeof(T));
    }


public:
    //------------------------------
    // Accesseurs
    //------------------------------
    inline T* getData()
    {
        return _data;
    }

    inline const T& getDataRef() const
    {
        return *_data;
    }

    T* getDataCopy() const
    {
        int size = getGlobalSize();
        T* res = new T[size];
        memcpy(res, _data, size*sizeof(T));
        return res;
    }

    void setDataCopy(T* data)
    {
        eassert(data != NULL);
        int size = getGlobalSize();
        memcpy(_data, data, size*sizeof(T));
    }
    void setData(T* data) { eassert(data != NULL); delete[] _data; _data = data; }

    inline int getWidth() const { return _width; }
    inline int getHeight() const { return _height; }
    inline int getDepth() const { return _depth; }
    inline int getGlobalSize() const { return _wh*_depth; }

    T get(int n) const { eassert(hold(n)); return _data[n]; }
    T get(int x, int y, int z) const { eassert(hold(x, y, z)); return _data[getGlobalIndex(x, y, z)]; }
    T get(Point3D_t<int>& p) const { return get(p.x, p.y, p.z); }

    void set(T val, int n) { eassert(hold(n)); _data[n] = val; }
    void set(T val, int x, int y, int z) { eassert(hold(x, y, z)); _data[getGlobalIndex(x, y, z)] = val; }
    void set(T val, Point3D_t<int>& p) { set(val, p.x, p.y, p.z); }

    void setSlice(T* slice, int index) {
        memcpy(_data+(_wh*index), slice, _wh * sizeof(T));
    }

    T getMin() const { refreshMinMax(); return _min; }
    T getMax() const { refreshMinMax(); return _max; }

    //------------------------------
    // Contrôle la validité d'un pixel
    //------------------------------
    bool hold(int n) const
    {
        return (n>=0) && (n<getGlobalSize());
    }
    bool hold(int x, int y, int z) const
    {
        return checkIncluded(x, y, z);
    }
    bool hold(Point3D_t<int>& p) const
    {
        return hold(p.x, p.y, p.z);
    }

    //------------------------------
    // Récupère ou insère une image 2D dans le volume
    //------------------------------
    Image<T>* getSlice(int index, SliceType type) const
    {
        switch(type) {
        case CORONAL:
            return GetSliceTransverse(index);
        case FRONTAL:
            return GetSliceFrontale(index);
        case SAGITAL:
            return GetSliceSagitale(index);
        default:
            eassert(false);
            return NULL;
        }
    }

    void putSlice(const Image<T> &img,int index, SliceType type)
    {
        switch(type) {
        case CORONAL:
            PutSliceTransverse(img, index);
            break;
        case FRONTAL:
            PutSliceFrontale(img, index);
            break;
        case SAGITAL:
            PutSliceSagitale(img,index);
            break;
        }
    }

    //------------------------------
    // Redéfinition des opérateurs
    //------------------------------
    Image3d<T>& operator-= (T val)
    {
        int size = getGlobalSize();
        for (int i=0; i<size; ++i) {
            _data[i] -= val;
        }
        return this;
    }

    Image3d<T>& operator-= (const Image3d<T>& img)
    {
        eassert(_width  == img.getWidth()  &&
                _height == img.getHeight() &&
                _depth  == img.getDepth());
        int size = getGlobalSize();
        for (int i=0; i<size; ++i) {
            _data[i] -= img._data[i];
        }
        return this;
    }

    // TODO : put outdatedSrc in all image modification methods
    /**
      Please use "setModifiedSrc" when you modify the image src data
      on the data */
    void setModifiedSrc() { _outdatedMinMax = true; }


private:
    /**
      Refreshes the min and max value if these values are outdated.
      Please use "setModifiedSrc" to because there is
      no access control on the data */
    void refreshMinMax() const
    {
        eassert(getGlobalSize() > 0);
        _outdatedMinMax = true;
        if (_outdatedMinMax == true) {
            T min = _data[0];
            T max = min;
            for (int i=0; i<_width*_height; ++i) {
                if (_data[i] < min) {
                    min = _data[i];
                }
                else if (_data[i] > max) {
                    max = _data[i];
                }
            }
            _outdatedMinMax = false;
            _min = min;
            _max = max;
        }
    }

    Image<T>* GetSliceTransverse(int index) const
    {
        eassert(index >= 0 && index < getDepth());
        int width = getWidth();
        int height = getHeight();
        int indexImage2D = 0;
        Image<T>* res = new Image<T>(width, height);
        for (int j=0; j<height; ++j) {
            for (int i=0; i<width; ++i) {
                res->set(get(i, j, index), indexImage2D++);
            }
        }
        return res;
    }
    Image<T>* GetSliceFrontale(int index) const
    {
        eassert(index >= 0 && index < getHeight());
        int depth = getDepth();
        int width = getWidth();
        int indexImage2D = 0;
        Image<T>* res = new Image<T>(width, depth);
        for (int i=0; i<depth; ++i) {
            for (int j=0; j<width; ++j) {
                res->set(get(j, index, i), indexImage2D++);
            }
        }
        return res;
    }
    Image<T>* GetSliceSagitale(int index) const
    {
        eassert(index >= 0 && index < getWidth());
        int depth = getDepth();
        int height = getHeight();
        int indexImage2D = 0;
        Image<T>* res = new Image<T>(depth, height);
        for (int j=0; j<height; ++j) {
            for (int i=0; i<depth; ++i) {
                res->set(get(index, j, i), indexImage2D++);
            }
        }
        return res;
    }

    void PutSliceTransverse(const Image<T>& img2d, int index)
    {
        eassert(index >= 0 && index < getDepth());
        eassert(img2d.getWidth() == getWidth() &&
                img2d.getHeight() == getHeight());
        int width = getWidth();
        int height = getHeight();
        int indexImage2D = 0;
        for (int j=0; j<height; ++j) {
            for (int i=0; i<width; ++i) {
                this->set(img2d.get(indexImage2D++), i, j, index);
            }
        }
    }
    void PutSliceFrontale(const Image<T>& img2d, int index)
    {
        eassert(index >= 0 && index < getHeight());
        eassert(img2d.getWidth() == getWidth() &&
                img2d.getHeight() == getDepth());
        int depth = getDepth();
        int width = getWidth();
        int indexImage2D = 0;
        for (int i=0; i<depth; ++i) {
            for (int j=0; j<width; ++j) {
                this->set(img2d.get(indexImage2D++), j, index, i);
            }
        }
    }
    void PutSliceSagitale(const Image<T>& img2d, int index)
    {
        eassert(index >= 0 && index < getWidth());
        eassert(img2d.getWidth() == getHeight() &&
                img2d.getHeight() == getDepth());
        int depth = getDepth();
        int height = getHeight();
        int indexImage2D = 0;
        for (int j=0; j<height; ++j) {
            for (int i=0; i<depth; ++i) {
                this->set(img2d.get(indexImage2D++), index, j, i);
            }
        }
    }

    //------------------------------
    // Accès index
    //------------------------------
    int getGlobalIndex(int x, int y, int z) const
    {
        return (z*_wh + y*_width + x);
    }

    bool checkIncluded(int x, int y, int z) const
    {
        return (x>=0 && x<_width &&
                y>=0 && y<_height &&
                z>=0 && z<_depth);
    }


private:
    T* _data;
    int _width;
    int _height;
    int _depth;
    int _wh;
    mutable T _max;
    mutable T _min;
    mutable bool _outdatedMinMax;
};

typedef Image3d<float> Volume;
typedef Image3d<bool> Mask3d;


#endif /* IMAGE3D_H */
