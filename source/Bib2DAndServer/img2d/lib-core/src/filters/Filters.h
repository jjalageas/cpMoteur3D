#ifndef FILTER_H
#define FILTER_H

#include <cstdlib>
#include <cmath>
#include <complex>

#include <Struct.hpp>
#include <Image3d.hpp>
#include <ImageMask2d.h>

/*
#include <Fourrier.h>

#include <FilterEdgeDetection.h>
#include <FilterFetita.h>
#include <FilterMorpho.h>
#include <FilterPandore.h>
#include <FilterPreFiltering.h>
#include <FilterThreshold.h>

#include <gsl/gsl_linalg.h>
#include <gsl/gsl_blas.h>
#include <gsl/gsl_math.h>
#include <gsl/gsl_eigen.h>
*/

/**
  * @brief Define a filter with these settings
  */
typedef MiList<float> Filter_t;

/**
  * @brief Classe permettant d'appliquer différents filters
  *
  * On peut appliquer les filtres en appelant les méthodes des filtres directement,
  * ou appliquer une liste de filtre directement.
  */
/*typedef struct {
       int BorneInf;
       int BorneSup;

}Classe;*/

class Filters
{
public:

       //*************************************************************************************
       // utilities methods (not filter)
       //*************************************************************************************

       /**
         * @brief Application d'un filtre de convolution
         *
         * Applique un filtre de dimension (filterWidth, filterHeight) sur une image de type Image
         *
         * @param image : Image a filtré
         * @param filterWidth : largeur du filtre
         * @param filterHeight : hauteur du filtre
         * @param filter : filtre à appliquer
         */
       static void ApplyConvolution (Image<float> *image, int filterWidth,
                                     int filterHeight, double filter[]);
       /**
         * @brief Application d'une lsite de filtre
         *
         * Méthode permettant d'appliquer directement une liste de filtre
         * en utilisant le type Filter_t sur une Image.
         * Filter_t doit contenir l'ID du filtre, suivit ses paramètres.
         *
         * @param image : Image sur laquelle appliquer les filtres
         * @param routine : liste des filtres à appliquer
         */
       static void ApplyRoutine(ImageMask2d *image, MiList<Filter_t *> *routine);

       //*************************************************************************************
       // Math/Logique
       //*************************************************************************************

       static bool compare(ImageMask2d *image,ImageMask2d *image2);
       static void Addition(ImageMask2d *image,ImageMask2d *image2);
       static void soustraction(ImageMask2d *image,ImageMask2d *image2 );
       static void Union(ImageMask2d *image,ImageMask2d *image2 );
       static void Intersection(ImageMask2d *image,ImageMask2d *image2 );
       static void Inversion(ImageMask2d *image);
       static void ImageMoinsValue(ImageMask2d *image,int value);

       //*************************************************************************************
       //Histogrammes
       //*************************************************************************************
       /*static int Max(int x, int y);
       static int Min(int x, int y);

       static float Max(float x, float y);
       static float Min(float x, float y);*/

       static float* MaxandMin(int width, int height, float *in);
       /*static float Min(int width, int height, float *in);
       static float Max(int width, int height, float *in);
       static int Max(int width, int height, int *in);
       static int Max(int size, int *in);*/
       template<typename T>
       static T Min(int width, int height, T *in);

       template<typename T>
       static T Max(int width, int height, T *in);

       /* Indice tab connexity */
       static int ConnexityX[8];
       static int ConnexityY[8];

       static void Convolution(ImageMask2d *, int, int, double[]);
       static void ConvolutionXY(ImageMask2d *, int, int, double[], double[]);



       /**
      * @brief Prewitt, ID : 4
      *
      * Applique un filtre de convolution de type PREWITT.
      *
      * @param image : Image a filtré
      */
       static void Prewitt (ImageMask2d *image);

       /**
      * @brief Sobel, ID : 5
      *
      * Applique un filtre de convolution de type SOBEL.
      *
      * @param image : Image a filtré
      */
       static void Sobel (ImageMask2d *image);

       /**
      * @brief Laplacian, ID : 6
      *
      * Applique un filtre de convolution de type LAPLACIAN.
      *
      * @param image : Image a filtré
      */
       static void Laplacian (ImageMask2d *image);



       /* Morphology convolution matrix */
       static double PrewittX[9];
       static double PrewittY[9];
       static double SobelX[9];
       static double SobelY[9];
       static double Laplacien[9];



       /**
      * @brief Bisseuillage, ID : 7
      *
      * Applique un bisseuillage sur le masque(Mask) de l'Image :
      * pour les valeur de l'image comprise entre min et max les valeurs
      * du Mask sont mises à 1, sinon 0.
      *
      * @param image : Image a filtré
      * @param min : valeur minimale pour le bisseuillage
      * @param max : valeur maximale pour le bisseuillage
      */
       static void Bisseuillage(ImageMask2d *image, float min, float max);


       /* Pré traitement */

       /**
         * @brief GaussianSpatial, ID : 0
         *
         * Applique un filtre de convolution créé par une gaussienne.
         *
         * @param image : Image a filtré
         * @param order : paramètre de la gaussienne
         */
       static void GaussianSpatial(ImageMask2d *image, float order);


       /* -------------------------------------------------------------------------------------------------
          MORPHOLOGY binaire
         -------------------------------------------------------------------------------------------------*/

          /**
            * @brief Erosion, ID : 8
            *
            * Applique un filtre de convolution de type Erosion.
            *
            * @param image : Image a filtré
            * @param iteration : nombre de fois d'application du filtre
            */
          static void Erosion (ImageMask2d *image, int iteration, int connexity);

          /**
            * @brief Erosion, ID : 9
            *
            * Applique un filtre de convolution de type Dilatation.
            *
            * @param image : Image a filtré
            * @param iteration : nombre de fois d'application du filtre
            */
          static void Dilatation (ImageMask2d *image, int iteration, int connexity);

          /**
            * @brief Erosion, ID : 10
            *
            * Applique un filtre de convolution de type Dilatation suivit d'une Erosion.
            *
            * @param image : Image a filtré
            * @param iteration : nombre de fois d'application du filtre
            */
          static void Open (ImageMask2d *image, int iteration, int connexity);

          /**
            * @brief Erosion, ID : 11
            *
            * Applique un filtre de convolution de type Erosion suivit d'une Dilatation.
            *
            * @param image : Image a filtré
            * @param iteration : nombre de fois d'application du filtre
            */
          static void Close (ImageMask2d* image, int iteration, int connexity);


   };

#endif
