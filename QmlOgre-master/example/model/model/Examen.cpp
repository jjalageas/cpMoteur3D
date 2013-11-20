#include <Examen.h>
#include <Image3d.hpp>
#include <ImageMask2d.h>
#include <Skeleton.h>
#include <SliceType.h>
#include <Image.hpp>
#include <iostream>

using namespace std;

/*Examen::Examen()
    : _volume(NULL), _mask(NULL)
{
    _skeleton = new Skeleton();
}*/

Examen::Examen(Volume* image, ExamenParams *params, Mask3d* mask)
    : _volume(image),
      _skeleton(NULL) {
    eassert(image != NULL);    
    if (mask == NULL) {
        mask = new Mask3d(image->getWidth(), image->getHeight(), image->getDepth());
        mask->initialize(false);
    }
    _mask = NULL;
    checkSizeConsistency(mask);
    _mask = mask;
    //if (params == NULL)
    //    params = new ExamenParams();
    _params = params;
}

Examen::~Examen()
{
    delete _volume;
    _volume = NULL;
    delete _mask;
    _mask = NULL;
    delete _skeleton;
    _skeleton = NULL;
}

Image3d<float>&
Examen::getImageRef() const
{
    return *_volume;
}

Image3d<float>*
Examen::getImageCopy() const
{
    return new Image3d<float>(*_volume);
}

void
Examen::setImage(Image3d<float>* image)
{
    checkSizeConsistency(image);
    delete _volume;
    _volume = image;
}

void
Examen::setImageCopy(Image3d<float>* image)
{    
    // authorize NULL argument?
    /*if (_volume == NULL) {
        _volume = new Image3d<float>();
    }*/
    checkSizeConsistency(image);
    _volume = image;
}

Mask3d&
Examen::getMaskRef() const
{
    return *_mask;
}

Mask3d*
Examen::getMaskCopy() const
{
    return new Mask3d(*_mask);
}

void
Examen::setMask(Mask3d* mask)
{
    checkSizeConsistency(mask);
    delete _mask;
    _mask = mask;
}

void
Examen::setMaskCopy(Mask3d* mask)
{
    checkSizeConsistency(mask);
    _mask->setDataCopy(mask->getData());
}

ImageMask2d*
Examen::getImageMask2d(int index, SliceType type)
{
    Image<float>* img = _volume->getSlice(index, type);
    Mask2d* mask = _mask->getSlice(index, type);
    return new ImageMask2d(img, mask, _params);
}

const Skeleton&
Examen::getSkeletonRef() const
{
    return *_skeleton;
}

ExamenParams&
Examen::getParams()
{
    return *_params;
}

template <typename T>
void
Examen::checkSizeConsistency(T& maskOrVolume) {
    eassert(maskOrVolume != NULL);
    eassert(_mask == NULL ||
            (_mask->getWidth() == maskOrVolume->getWidth() &&
             _mask->getHeight()== maskOrVolume->getHeight() &&
             _mask->getDepth() == maskOrVolume->getDepth()));
    eassert(_volume == NULL ||
            (_volume->getWidth() == maskOrVolume->getWidth() &&
             _volume->getHeight()== maskOrVolume->getHeight() &&
             _volume->getDepth() == maskOrVolume->getDepth()));
    (void) maskOrVolume; // fix warning in release mode
}
