#ifndef IMAGEVIEWERMODEL_H
#define IMAGEVIEWERMODEL_H

#include <Examen.h>
#include <ImageMask2d.h>

// TODO : add precaching for the next and previous slices...
// Project driving project class 2012


/** @class ImageViewerModel
A model class of the MVC pattern of the viewer2D.
It contains the Examen and methods to precompute the slices to display
*/

class ImageViewerModel
{
public:
    ImageViewerModel(Examen *examen);
    ~ImageViewerModel();
    int getIndexCurrentSlice();
    ImageMask2d* getCurrentSlice();
    void setIndexCurrentSlice(int index);
    //int getWindowingCenter();
    //int getWindowingWidth();
    Examen* getCurrentExamen();

private:
    Examen *_examen;
    ImageMask2d *_slice;
    int _indexCurrentSlice;
    int _sliceMode;
};

#endif // IMAGEVIEWERMODEL_H
