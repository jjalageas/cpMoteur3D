#include <ImageMask2d.h>

#include <Image3d.hpp>
#include <Struct.hpp>
#include <debug.h>


ImageMask2d::ImageMask2d(Image<float> *image, Mask2d *mask2d, ExamenParams *params) :
 _params(params)
{
    eassert(image->getWidth() == mask2d->getWidth());
    eassert(image->getHeight() == mask2d->getHeight());
    _img = image;
    _mask = mask2d;
    eassert(_img != NULL);
    eassert(_mask != NULL);
    eassert(_params != NULL);
}

ImageMask2d::ImageMask2d(const ImageMask2d &imageMask2d) {
    _img = new Image<float>(*imageMask2d._img);
    _mask = new Mask2d(*imageMask2d._mask);
    _params = new ExamenParams(*imageMask2d._params);
}

Mask2d *ImageMask2d::getMaskRef() const {
    return _mask;
}

Mask2d *ImageMask2d::getMaskCopy() const {
    return new Image<bool>(*_mask);
}

Image<float> *ImageMask2d::getImageRef() const {
    return _img;
}

Image<float> *ImageMask2d::getImageCopy() const {
    return new Image<float>(*_img);
}

float ImageMask2d::get(int i, int j) const {
    return _img->get(i, j);
}

float ImageMask2d::get(int i) const {
    return _img->get(i);
}

void ImageMask2d::set(float val, int i) {
    _img->set(val, i);
}

int ImageMask2d::getMaxVal() const {
    return _img->getMax();
}

int ImageMask2d::getMinVal() const {
    return _img->getMin();
}

int ImageMask2d::getWidth() const {
    return _img->getWidth();
}

int ImageMask2d::getHeight() const {
    return _img->getHeight();
}

ExamenParams& ImageMask2d::getParams() const {
    return *_params;
}
