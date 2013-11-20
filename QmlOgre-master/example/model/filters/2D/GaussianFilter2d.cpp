#include "GaussianFilter2d.h"
#include <QVariant>
#include <Filters.h>

#include <iostream>
using namespace std;

GaussianFilter2D::GaussianFilter2D()
    : Filter2D("Gaussian filter")
{
    this->addArgument(new FilterArgument("order", QVariant::Double, QVariant(.1d), QVariant(10000.d), QVariant(1.d)));
    this->addArgument(new FilterArgument("test :-)", QVariant::Double, QVariant(50.d), QVariant(60.1d), QVariant()));
}

void
GaussianFilter2D::apply(ImageMask2d &img)
{
    eassert(canApply() == true);
    double order = getArgument("order")->getValue().toDouble();
    cout << "apply Gaussian with order arg : " << order << endl;
    Filters::GaussianSpatial(&img, (float) order);
}
