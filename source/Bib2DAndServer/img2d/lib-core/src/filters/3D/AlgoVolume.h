#ifndef ALGO_VOLUME_H
#define ALGO_VOLUME_H

#include <Image3d.hpp>
#include <Image.hpp>
#include <Struct.hpp>

class Examen;
class ImageMask2d;
class Skeleton;

using namespace std;

class Node;

class AlgoVolume
{
public:

       static void AllPoints(Examen *examen);

       //--------------------------------------
       //adaptation entre type
       //--------------------------------------
       static MiList<Point3D_t<int>* >* setListOfPointFromVolume(Image3d<float> *volume);
       static void setVolumeFromlstPoints(Image3d<float> *volume, MiList<Point3D_t<int> *>* lst);

       static Point3D_t<int>* getPointFromIndex(int index, int w,int h);//RICHARD
       static Point3D_t<int> getSPointFromIndex(int index, int w,int h);
       static Point3D_t<int> getPointFromPointeur(Point3D_t<int>*p);
       static MiList<int>ComputeFrontiere(int w,int h,int d,bool *Volume,int value);



       //--------------------------------------
       //permet de stocker le contenue d'une image a la bonne position dans un volume==mask 3D
       //--------------------------------------
       static void MaskImageToVolume(Image3d<float> *volume, ImageMask2d*image,int z);
       static void MaskImageToVolume(Image3d<float> *volume, Image3d<bool>* mask, bool* image,int z);
       static void MaskImageToVolume(Image3d<float> *volume, Image3d<bool>* mask, ImageMask2d*image,int z);
       static void MaskImageToVolume(Image3d<float> *volume, Image3d<bool>* mask, bool* image,int z,int w,int h);
       static void VolumeToMaskImage(Examen *examen);
       static void VolumeToMaskImage(Examen *examen, Image3d<bool>* vol);
       static void SliceImageToVolume(Image3d<bool> *volume ,Image3d<bool>* mask, Image<Point3D_t<int> > *sliceCoord,int w,int h);


       //--------------------------------------
       //biseuillage 3D
       //--------------------------------------

       static Image3d<bool>* biseuillage3D(Image3d<float> * volume ,int Smin, int Smax);


       //--------------------------------------
       //region growing simple
       //--------------------------------------

       //tableau de voisinnage
       static int dx[26];
       static int dy[26];
       static int dz[26];

       //fonction de voisinnagess
       static MiList<Point3D_t<int>* >* GetNeighbor(int vwidth, int vheight, int vdepth,
                                                         Point3D_t<int>* Voxel, int connexity);
       static MiList< Point3D_t<int> *> *GetNeighbour(int width, int height, int depth,
                                                      Point3D_t<int> *ps, int connexity);

       static MiList< Point3D_Data_t<int, int> *> *GetNeighbour(int width, int height, int depth,
                                                                Point3D_Data_t<int, int> *ps, int connexity);
       static void GetNeighbourHB(int width, int height, int depth, MiList<Point3D_t< int> *>* file,
                                                                     Image3d<bool>*visited, Image3d<bool>*VolumeTotal,Examen*examen, Image3d<bool>*res,int Smin, int Smax,
                                                                     Point3D_t<int> *ps, int connexity);
       //fonction de RG a partir de voisinnage par tableaux
       static void CTRG(Examen *examen, int connexity, int distance);
       static void NCRG(Examen *examen, int connexity, int distance);
       static Image3d<bool>* CTRG2(int width,int  height,int depth, Image3d<bool>* volume,Point3D_t<int> seed, int connexity);

       void GetNeighbor_Conditionnel_Threshold_Intersection
               (MiList<Point3D_t< int> *>* file,
                Image3d<bool>*visited, Image3d<bool>*VolumeTotal, Examen*examen,
                int Smin, int Smax, Image3d<bool>*res, int width, int height, int depth,
                Point3D_t<int>* Voxel, int borneInf,int borneSup);

};

#endif
