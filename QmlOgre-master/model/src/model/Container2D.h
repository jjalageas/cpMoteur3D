#ifndef 2D_CONTAINER_H
#define 2D_CONTAINER_H

#include "Image3d.hpp"
#include "Image.hpp"
#include <SliceType.h>

class Container2D
{
 private :
  vector<Image<float>> sagital;
  vector<Image<float>> coronal;
  vector<Image<float>> frontal;



 public :
  Container2D(Image3D image3D);
  ~Container2D();
  Image<float> getCoupe(int i, SliceType type);

}

#endif
