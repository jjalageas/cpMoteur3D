#ifndef EXAMEN_H
#define EXAMEN_H

#include "ExamenParams.h"
#include "SliceType.h"
#include "Image3d.hpp"

template<typename T> class Image;
template<typename T> class Image3d;
class ImageMask2d;
class Skeleton;


class Examen
{
public:
    Examen(Volume* image, ExamenParams* params = NULL, Mask3d* mask = NULL);
    ~Examen();


public:
    inline Volume* getImage() { return _volume; }
    Volume& getImageRef() const;
    Volume* getImageCopy() const;
    void setImage(Volume* image);
    void setImageCopy(Volume* image);

    inline Mask3d* getMask() { return _mask; }
    Mask3d& getMaskRef() const;
    Mask3d* getMaskCopy() const;
    void setMask(Mask3d* mask);
    void setMaskCopy(Mask3d* mask3D);

    ImageMask2d* getImageMask2d(int index, SliceType type);

    inline Skeleton* getSkeleton() { return _skeleton; }
    const Skeleton& getSkeletonRef() const;

    ExamenParams& getParams();


private:
    template <typename T> void checkSizeConsistency(T&);
    ExamenParams* _params;
    Volume* _volume;
    Mask3d* _mask;
    Skeleton* _skeleton;

};

#endif // EXAMEN_H
