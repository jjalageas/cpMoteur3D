#ifndef ALGO_VOLUME_MORPHO_H
#define ALGO_VOLUME_MORPHO_H

#include <AlgoVolume.h>
//#include <AlgoVolumeCC.h>
#include <Skeleton.h>
#include <Examen.h>
//#include <Volume.h>
#include <Image3d.hpp>
#include <Struct.hpp>
//#include <Tools.h>
//#include <Image.h>
#include <StructuringElement.h>

class AlgoVolumeMorpho
{
public:
    /*-------------------------------------------------------------------------------------------------------

                                     OPERATEUR EN NIVEAU DE GRIS

     -------------------------------------------------------------------------------------------------------- */

    // operateur morpho depuis les slices de l'examen en NDG
    // Input : Image3d<float> *img3 = examen.getData();
    // Output : examen.setData(Image3d<float> *img3);
    static void Erosion3dNDG (Image3d<float> *img3, int num_se, int halfsize, int iteration);
    static void Dilatation3dNDG  (Image3d<float> *img3, int num_se, int halfsize, int iteration);
    static void GradientMorpho(Examen * volume ,int sizeElt);
    static void Fermeture3dNDG(Image3d<float> * volume ,int sizeElt);
    static void Ouverture3dNDG(Image3d<float> * volume ,int sizeElt);



    /*-------------------------------------------------------------------------------------------------------

                                       OPERATEUR USUEL BINAIRE

     -------------------------------------------------------------------------------------------------------- */



    //operateur morpho depuis n'importe quel Mask

    static Image3d<bool>* Dilatation3DM(int width,int height,int depth ,Image3d<bool>*mask, int connexity, int iteration);
    static Image3d<bool>* Erosion3DM(int width,int height,int depth,Image3d<bool>*mask, int connexity, int iteration);


    static void AllPointAndErodeFromOtherMask(int iter, Image3d<float> *volume,
                                              Image3d<bool>*maskres,Image3d<bool>* maskPlein);


};

#endif // ALGO_VOLUME_MORPHO_H
