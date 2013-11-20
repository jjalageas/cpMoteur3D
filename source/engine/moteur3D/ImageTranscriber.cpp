#include "ImageTranscriber.h"


MiList<ImageData<float> *> *ImageTranscriber::AllImages(Examen *exam, int type)
{
    MiList<ImageData<float> *> *res = new MiList<ImageData<float> *>();
    int nb = 0;
    switch (type) {
        case 0: //transverse
            nb = exam->getSize();
            break;
        case 1: //frontale
            nb = exam->getHeight();
            break;
        case 2: //sagitale
            nb = exam->getWidth();
    }
    for(int i=0;i<nb;++i)
    {
        ImageData<float> *img = exam->getImage2D(i,type)->toImagedata();
        img->normalize(255);
        res->add(img);
    }
    return res;
}

 MiList<Point3D_Data_t<float,int> *> *ImageTranscriber::ToVolume(Examen *examen)
 {
     MiList<Point3D_Data_t<float,int> *> *res = new MiList<Point3D_Data_t<float,int> *>();
     MiList<ImageData<float> *> *listSlices = AllImages(examen,0);

     for(int i=0;i<listSlices->size();i++)
     {
         ImageData<float> *img = listSlices->get(i);
         int width = img->getWidth();
         int height = img->getHeight();
         for(int j=0; j<height;j++)
             for(int k=0; k<width; k++)
             {
                 if(img->getData(k,j) != 0)
                     res->add(new Point3D_Data_t<float,int>(k,j,i,img->getData(k,j)));
             }
     }
     return res;
 }

 Triplet_t<float*,char*,int> ImageTranscriber::ToVBO (MiList< Point3D_Color_t<float> *> *points)
 {
        Triplet_t<float*,char*,int> res (NULL, NULL, 0);
        if (points != NULL)
        {
               int size = points->size();
               float *indice = new float[3 * size];
               char *couleur = new char[3 * size];
               res = Triplet_t<float*,char*,int>(indice, couleur, size);

               Point3D_Color_t<float> *p=0;
               for (int i=0 ; i < size ; ++i)
               {
                      p = points->get(i);
                      //indice
                      indice[i * 3] = (float)p->x;
                      indice[i * 3 + 1] = (float)p->y;
                      indice[i * 3 + 2] = (float)p->z;
                      //couleur
                      couleur[i * 3] = (char)p->red;
                      couleur[i * 3 + 1] = (char)p->green;
                      couleur[i * 3 + 2] = (char)p->blue;
               }
        }
        return res;
 }

 //Cette fonction permet la recuperation de tous les points du volume contenu dans l'examen
 MiList< Point3D_Color_t<float> *> *ImageTranscriber::FromVolume(Examen *examen)
 {
        MiList< Point3D_Color_t<float> *> *res = new MiList<Point3D_Color_t<float> *>();

        Image3d<float> *volume = examen->getDataRef();
        Mask *mask = examen->getMasqueRef();

        if (volume != NULL)
        {
               int width = volume->getWidth();
               int height = volume->getHeight();
               int depth = volume->getDepth();

               //pour la coloration
               int maxVal = examen->getGlobalMax();
               int windowingMin = examen->getWindowingMin();
               int windowingMax = examen->getWindowingMax();
               windowingMax = (windowingMax > maxVal) ? maxVal : windowingMax;
               float colorRatio = (float)256;
               if (windowingMax - windowingMin != 0)
                      colorRatio /= (float)(windowingMax - windowingMin);

               for (int z=0 ; z < depth ; z++)
               {
                  for (int y=0 ;  y < height ; y++)
                  {
                     for (int x=0 ; x < width ; x++)
                     {
                         if (mask->get(x, y, z) == 1)
                        {
                           Point3D_Color_t<float> *p =
                                         new Point3D_Color_t<float>((x - width/2),
                                                                    - (z - depth/2),
                                                                    (y - height/2));
                           int ndg = (volume->get(x,y,z)-windowingMin) * colorRatio;

                           if(ndg > 0)
                           {
                               //coloration en NdG
                               p->Red(ndg);
                               p->Green(ndg);
                               p->Blue(ndg);

                               res->add(p);
                           }
                        }
                     }
                  }
               }
        }
        return res;
 }

//Cette fonction permet la recuperation de tous les points contenu dans une coupe
//la valeur <int value> permet de differencier le type de la coupe (transverse, frontalle, sagitalle)
MiList< Point3D_Color_t<float> *> *ImageTranscriber::FromVolumeToImage2D(Examen *examen, int slide, int value)
{
    MiList< Point3D_Color_t<float> *> *res = new MiList<Point3D_Color_t<float> *>();

    Image3d<float> *volume = examen->getDataRef();
    Image3d<float> *coupe = volume->getImage2DFrom3D(slide, value);

    if (coupe != NULL)
    {
        float dx = examen->getResolutionX();
        float dy = examen->getResolutionY();
        float dz = examen->getResolutionZ();
        int width = examen->getWidth();
        int height = examen->getHeight();
        int depth = examen->getSize();

        //pour la coloration
        int maxVal = examen->getGlobalMax();
        int windowingMin = examen->getWindowingMin();
        int windowingMax = examen->getWindowingMax();
        windowingMax = (windowingMax > maxVal) ? maxVal : windowingMax;
        float colorRatio = (float)256;
        if (windowingMax - windowingMin != 0)
        colorRatio /= (float)(windowingMax - windowingMin);

        Point3D_Color_t<float> *p;

        switch(value)
        {
            case 0:
                for (int y=0 ;  y < height ; y++)
                {
                    for (int x=0 ; x < width ; x++)
                    {
                        if(examen->getPixelM(x,y,slide))
                        {
                            p = new Point3D_Color_t<float>((x - width/2)*dx,(y - height/2)*dy,(slide - depth/2)*dz);
                            //changed
                            int ndg = (coupe->get(x,y,0)-windowingMin) * colorRatio;
                            //end
                            if(ndg > 0)
                            {
                                //coloration en NdG
                                p->Red(ndg);
                                p->Green(ndg);
                                p->Blue(ndg);

                                res->add(p);
                            }
                        }
                    }
                }
            break;

            case 1:
                for (int z=0 ;  z < depth ; z++)
                {
                    for (int x=0 ; x < width ; x++)
                    {
                        if(examen->getPixelM(x,slide,z))
                        {
                            p = new Point3D_Color_t<float>((x - width/2)*dx,(slide - height/2)*dy,(z - depth/2)*dz);
                            //changed
                            int ndg = (coupe->get(x,z,0)-windowingMin) * colorRatio;
                            //end
                            if(ndg > 0)
                            {
                                //coloration en NdG
                                p->Red(ndg);
                                p->Green(ndg);
                                p->Blue(ndg);

                                res->add(p);
                            }
                        }
                    }
                }
            break;

        case 2:
            for (int z=0 ;  z < depth ; z++)
            {
                for (int y=0 ; y < height ; y++)
                {
                    if(examen->getPixelM(slide,y,z))
                    {
                        p = new Point3D_Color_t<float>((slide - width/2)*dx, (y - height/2)*dy, (z - depth/2)*dz);
                        //changed
                        int ndg = (coupe->get(y,z,0)-windowingMin) * colorRatio;
                        //end
                        if(ndg > 0)
                        {
                            //coloration en NdG
                            p->Red(ndg);
                            p->Green(ndg);
                            p->Blue(ndg);

                            res->add(p);
                        }
                    }
                }
            }
        break;

        }
    }
    return res;
}
