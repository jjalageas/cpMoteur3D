#ifndef IMAGE_MASK_2D_H
#define IMAGE_MASK_2D_H

#include "ExamenParams.h"

template<typename T> class Image;


class ImageMask2d
{
public:
    ImageMask2d(Image<float>* image, Image<bool>* mask2d, ExamenParams* params = 0);
    ImageMask2d(const ImageMask2d& imageMask2d);

    Image<float>* getImageRef() const;
    Image<float>* getImageCopy() const;
    Image<bool>* getMaskRef() const;
    Image<bool>* getMaskCopy() const;
    ExamenParams& getParams() const;

    int getMaxVal() const;
    int getMinVal() const;
    int getWidth() const;
    int getHeight() const;

    float get(int i) const;
    float get(int i, int j) const;
    void  set(float val, int i);


private:
    Image<float>* _img;
    Image<bool>* _mask;
    ExamenParams* _params;
};

#endif // IMAGE_MASK_2D_H
