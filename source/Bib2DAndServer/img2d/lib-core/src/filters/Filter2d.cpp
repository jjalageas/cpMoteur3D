#include "Filter2d.h"
#include "Tools.h"

using namespace std;

Filter2D::Filter2D(string name) : FilterV2(name)
{}


void Filter2D::apply(Examen &exam, SliceType type)
{
    int lastId = Tools::lastSliceId(exam, type);
    for (int i=0; i<lastId; ++i) {
        ImageMask2d *slice = exam.getImageMask2d(i, type);
        apply(*slice);
        exam.getImageRef().putSlice(*slice->getImageRef(), i, type);
        exam.getMaskRef().putSlice(*slice->getMaskRef(), i, type);
        delete slice;
    }
}
