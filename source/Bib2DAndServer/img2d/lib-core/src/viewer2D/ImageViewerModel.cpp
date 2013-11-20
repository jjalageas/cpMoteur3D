#include <ImageViewerModel.h>
#include <debug.h>
#include <SliceType.h>
#include <Image3d.hpp>


ImageViewerModel::ImageViewerModel(Examen* examen)
    : _examen(examen), _indexCurrentSlice(0), _sliceMode(CORONAL)
{}

ImageViewerModel::~ImageViewerModel()
{
    delete _examen;
    _examen = NULL;
}


int ImageViewerModel::getIndexCurrentSlice() {
    if (_examen != NULL)
    {
        eassert(_indexCurrentSlice >= 0 && _indexCurrentSlice < _examen->getImage()->getDepth());
        return _indexCurrentSlice;
    }
    return -1;
}

void ImageViewerModel::setIndexCurrentSlice(int index) {
    eassert(_examen != NULL);
    eassert(_indexCurrentSlice >= 0 && _indexCurrentSlice < _examen->getImage()->getDepth());
    if (_indexCurrentSlice != index) {
        _indexCurrentSlice = index;
        delete _slice;
        _slice = NULL;
    }
}

// TODO : modify Examen or Image3d to be able to write this method
/*int ImageViewerModel::getMaxIndexCurrentSlice() {
    return exam.
}*/

ImageMask2d* ImageViewerModel::getCurrentSlice() {
    if (_slice == NULL) {
        //Image<float> *img = _examen->getImage()->getSlice(_indexCurrentSlice, CORONAL);
        //Image<bool> *mask = _examen->getMaskRef().getSlice(_indexCurrentSlice, CORONAL);
        //ExamenParams *params = new ExamenParams(_examen->getParams());
        // TODO : change params to compute the actual parameters
        //_slice = new ImageMask2d(img, mask, params);
    }
    return _slice;
}

Examen* ImageViewerModel::getCurrentExamen() {
    return _examen;
}

