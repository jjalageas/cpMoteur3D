#include "AlgoVolumeMorpho.h"







void AlgoVolumeMorpho::GradientMorpho(Examen * examen ,int sizeElt){

    Image3d<float> *dil = examen->getImageCopy();
    Image3d<float> *erode = examen->getImageCopy();
    int iteration=1;


    //dilatation en element structurant en barre(allege la complexité )
    AlgoVolumeMorpho::Dilatation3dNDG(dil, 3, sizeElt, iteration);
    AlgoVolumeMorpho::Dilatation3dNDG(dil, 4, sizeElt, iteration);
    AlgoVolumeMorpho::Dilatation3dNDG(dil, 5, sizeElt, iteration);
    cout<<"fin dilatation"<<endl;

    //erosion en element structurant en barre(allege la complexité )
    AlgoVolumeMorpho::Erosion3dNDG(erode, 3, sizeElt, iteration);
    AlgoVolumeMorpho::Erosion3dNDG(erode, 4, sizeElt, iteration);
    AlgoVolumeMorpho::Erosion3dNDG(erode, 5, sizeElt, iteration);
    cout<<"fin erodion"<<endl;

    //**********************************************************************
    //difference entre les deux
    //**********************************************************************

    int size = dil->getGlobalSize();
    for (int i=0 ; i < size ; i++)
        dil->set((dil->get(i) - erode->get(i)), i);
    cout<<"difference:"<<endl;

    //**********************************************************************
    //nettoyage
    //**********************************************************************
    delete erode;
    erode = NULL;

    examen->setImage(dil);
}

float getMaxNeighboor(Image3d<float> *image3D,Point3D_t<int>Voxel,int width,int height,int depth){
    //declaration des variables
    int    xn, yn,zn, xnt, ynt, znt;
    int x0, y0 ,z0, x0t, y0t, z0t;

    //calcul des bornes
    z0t = (Voxel.z-1); y0t = (Voxel.y-1); x0t = (Voxel.x-1);
    znt = (Voxel.z + 2 ); ynt = (Voxel.y + 2 ); xnt = (Voxel.x + 2 );
    z0 = z0t <= 0 ? 0 : (z0t); zn = znt < depth ? znt : depth;
    y0 = y0t <= 0 ? 0 : (y0t); yn = ynt < height ? ynt : height;
    x0 = x0t <= 0 ? 0 : (x0t); xn = xnt < width ? xnt : width;


    float max=0;

    //verifications des conditions
    int sizeImage=width*height;
    for(int indexz = z0; indexz < zn; indexz ++)
    {
        int POSITIONZ=indexz*sizeImage;
        for(int indexy = y0; indexy < yn; indexy ++)
        {
            int POSITIONY=indexy*width;
            for(int indexx = x0; indexx < xn; indexx ++)
            {
                if(indexz!=Voxel.z  ||  indexy!=Voxel.y || indexx!=Voxel.x)
                {

                    int index=POSITIONZ + POSITIONY +indexx;
                    if (image3D->get(index)>max)
                    {
                        max=image3D->get(index);
                    }
                }
            }
        }
    }

    return max;

}
bool getNeighboor(Image3d<float> *image3D,Point3D_t<int>Voxel,int width,int height,int depth){
    //declaration des variables
    int    xn, yn,zn, xnt, ynt, znt;
    int x0, y0 ,z0, x0t, y0t, z0t;

    //calcul des bornes
    z0t = (Voxel.z-1); y0t = (Voxel.y-1); x0t = (Voxel.x-1);
    znt = (Voxel.z + 2 ); ynt = (Voxel.y + 2 ); xnt = (Voxel.x + 2 );
    z0 = z0t <= 0 ? 0 : (z0t); zn = znt < depth ? znt : depth;
    y0 = y0t <= 0 ? 0 : (y0t); yn = ynt < height ? ynt : height;
    x0 = x0t <= 0 ? 0 : (x0t); xn = xnt < width ? xnt : width;




    //verifications des conditions
    int sizeImage=width*height;
    for(int indexz = z0; indexz < zn; indexz ++)
    {
        int POSITIONZ=indexz*sizeImage;
        for(int indexy = y0; indexy < yn; indexy ++)
        {
            int POSITIONY=indexy*width;
            for(int indexx = x0; indexx < xn; indexx ++)
            {
                if(indexz!=Voxel.z  ||  indexy!=Voxel.y || indexx!=Voxel.x)
                {

                    int index=POSITIONZ + POSITIONY +indexx;
                    if (image3D->get(index)==0)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;

}

bool getNeighboor(Image3d<bool> *image3D,Point3D_t<int>Voxel,int width,int height,int depth){
    //declaration des variables
    int    xn, yn,zn, xnt, ynt, znt;
    int x0, y0 ,z0, x0t, y0t, z0t;

    //calcul des bornes
    z0t = (Voxel.z-1); y0t = (Voxel.y-1); x0t = (Voxel.x-1);
    znt = (Voxel.z + 2 ); ynt = (Voxel.y + 2 ); xnt = (Voxel.x + 2 );
    z0 = z0t <= 0 ? 0 : (z0t); zn = znt < depth ? znt : depth;
    y0 = y0t <= 0 ? 0 : (y0t); yn = ynt < height ? ynt : height;
    x0 = x0t <= 0 ? 0 : (x0t); xn = xnt < width ? xnt : width;




    //verifications des conditions
    int sizeImage=width*height;
    for(int indexz = z0; indexz < zn; indexz ++)
    {
        int POSITIONZ=indexz*sizeImage;
        for(int indexy = y0; indexy < yn; indexy ++)
        {
            int POSITIONY=indexy*width;
            for(int indexx = x0; indexx < xn; indexx ++)
            {
                if(indexz!=Voxel.z  ||  indexy!=Voxel.y || indexx!=Voxel.x)
                {

                    int index=POSITIONZ + POSITIONY +indexx;
                    if (image3D->get(index)==0)
                    {
                        return false;
                    }
                }
            }
        }
    }

    return true;

}

float getMaxNeighboor(Image3d<float> *image3D,Point3D_t<int>pt,StructuringElement3d &se3d){

    int se3dSize = se3d.size();
    float max=0;
    for (int i=0 ; i < se3dSize ; i++)
    {
        Point3D_t<int> &pse = se3d.getRef(i);
        if ( (pse.x != 0) || (pse.y != 0) || (pse.z != 0) )//verifie les coordonnée de l'element structurant
        {
            Point3D_t<int> pp(pse.x + pt.x, pse.y + pt.y, pse.z + pt.z);
            if ( image3D->hold(pp))//verifie ses coordonnée dans notre image 3D
            {
                if (image3D->get(pse)>max)
                {
                    max=image3D->get(pse);
                }
            }
        }
    }

    return max;

}



// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


void AlgoVolumeMorpho::Erosion3dNDG (Image3d<float> *img3, int num_se, int halfsize, int iteration)
{
    if (num_se>5 || num_se<0) {
        cerr <<"Error ErosionGeodesique: bad structuring element type" << endl;
        return;
    }
    if (halfsize < 1) {
        cerr << "Error ErosionGeodesique: bad structuring element size" << endl;
        return;
    }

    StructuringElement3d eltStructurant(num_se, halfsize);
    int eltStructurantSize = eltStructurant.size();

    int width = img3->getWidth();
    int height = img3->getHeight();
    int depth = img3->getDepth();
    int size = width * height * depth;

    Image3d<float> tmp(width, height, depth);
    tmp.initialize(0);
    float *img3Data = img3->getDataCopy();
    float *tmpData = tmp.getDataCopy();

    for (int it=0 ; it < iteration ; it++)
    {
        for (int k=0 ; k < depth ; k++)
        {
            for (int j=0 ; j <  height; j++)
            {
                for (int i=0 ; i <  width; i++)
                {
                    float val = img3->get(i, j, k);
                    for (int l=0 ; l < eltStructurantSize ; l++)
                    {
                        Point3D_t<int> &pse = eltStructurant.getRef(l) ;
                        Point3D_t<int> p(pse.x + i, pse.y + j, pse.z + k);

                        if ( tmp.hold(p) && (tmp.get(p) < val) )
                            tmp.set(val, p);
                    }
                }
            }
        }

        memcpy (img3Data, tmpData, sizeof(float) * size);
    }
}


void AlgoVolumeMorpho::Dilatation3dNDG  (Image3d<float> *img3, int num_se, int halfsize, int iteration)
{
    if (num_se>5 || num_se<0) {
        cerr <<"Error ErosionGeodesique: bad structuring element type" << endl;
        return;
    }
    if (halfsize < 1) {
        cerr << "Error ErosionGeodesique: bad structuring element size" << endl;
        return;
    }

    StructuringElement3d eltStructurant(num_se, halfsize);
    int eltStructurantSize = eltStructurant.size();

    int width = img3->getWidth();
    int height = img3->getHeight();
    int depth = img3->getDepth();
    int size = width * height * depth;

    Image3d<float> tmp(*img3);
    float *img3Data = img3->getDataCopy();
    float *tmpData = tmp.getDataCopy();

    for (int it=0 ; it < iteration ; it++)
    {
        for (int k=0 ; k < depth ; k++)
        {
            for (int j=0 ; j <  height; j++)
            {
                for (int i=0 ; i <  width; i++)
                {
                    float val = img3->get(i, j, k);
                    for (int l=0 ; l < eltStructurantSize ; l++)
                    {
                        Point3D_t<int> &pse = eltStructurant.getRef(l) ;
                        Point3D_t<int> p(pse.x + i, pse.y + j, pse.z + k);

                        //verifie la validité des coordonnées(hold) et et si l'intensité est superieur au point courant
                        //on affecte l'intensité du point courant au point observé!
                        if ( tmp.hold(p) && (tmp.get(p) > val) )
                            tmp.set(val, p);
                    }
                }
            }
        }
        memcpy (img3Data, tmpData, sizeof(float) * size);
    }
}

//fermeture 26 connexe en NVG dont les contours sont protégé par un biseuillage contour préalable
void AlgoVolumeMorpho::Fermeture3dNDG(Image3d<float> * volume ,int sizeElt){


    //lance la fermeture NDG protect
    int iteration=1;

    //erosion en element structurant en barre(allege la complexité )<=>erosion 26 connexe
    Erosion3dNDG(volume, 3, sizeElt, iteration);
    Erosion3dNDG(volume, 4, sizeElt, iteration);
    Erosion3dNDG(volume, 5, sizeElt, iteration);

    //dilatation en element structurant en barre(allege la complexité )<=>dilatation26 connexe
    Dilatation3dNDG(volume, 3, sizeElt, iteration);
    Dilatation3dNDG(volume, 4, sizeElt, iteration);
    Dilatation3dNDG(volume, 5, sizeElt, iteration);



    cout<<"fin fermeture protect"<<endl;

}

//fermeture 26 connexe en NVG dont les contours sont protégé par un biseuillage contour préalable
void AlgoVolumeMorpho::Ouverture3dNDG(Image3d<float> * volume ,int sizeElt){

    //lance la fermeture NDG protect
    int iteration=1;
    //dilatation en element structurant en barre(allege la complexité )<=>dilatation26 connexe
    Dilatation3dNDG(volume, 3, sizeElt, iteration);
    Dilatation3dNDG(volume, 4, sizeElt, iteration);
    Dilatation3dNDG(volume, 5, sizeElt, iteration);

    //erosion en element structurant en barre(allege la complexité )<=>erosion 26 connexe
    Erosion3dNDG(volume, 3, sizeElt, iteration);
    Erosion3dNDG(volume, 4, sizeElt, iteration);
    Erosion3dNDG(volume, 5, sizeElt, iteration);


    cout<<"fin fermeture protect"<<endl;

}













// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------
// ----------------------------------------------------------------------------------------------------------------------------


Image3d<bool>* AlgoVolumeMorpho::Erosion3DM(int width, int height, int depth,
                                   Image3d<bool>* mask, int connexity, int iteration)
{
    Image3d<bool> *copy = NULL;
    for (int it=0 ; it < iteration ; it++)
    {
        copy = new Image3d<bool>(*mask);

        for (int z=1 ; z < depth-1 ; z++)
        {
            for (int y=1 ; y < height-1 ; y++)
            {
                for (int x=1 ; x < width-1 ; x++)
                {
                    int val = 0;
                    for (int c=0 ; c < connexity ; c++)
                        val += mask->get(x + AlgoVolume::dx[c],
                                         y + AlgoVolume::dy[c], z + AlgoVolume::dz[c]);
                    copy->set((val == connexity) ? 1 : 0, x, y, z);
                }
            }
        }
    }
    return copy;
}




Image3d<bool>* AlgoVolumeMorpho::Dilatation3DM(int width,int height,int depth ,Image3d<bool>*mask, int connexity, int iteration)
{
    Image3d<bool> *copy = NULL;
    for (int it=0 ; it < iteration ; it++)
    {
        copy = new Image3d<bool>(*mask);

        for (int z=1 ; z < depth-1 ; z++)
        {
            for (int y=1 ; y < height-1 ; y++)
            {
                for (int x=1 ; x < width-1 ; x++)
                {
                    int val = 0;
                    for (int c=0 ; c < connexity ; c++)
                        val += mask->get(x + AlgoVolume::dx[c],
                                         y + AlgoVolume::dy[c], z + AlgoVolume::dz[c]);
                    copy->set((val > 0) ? 1 : 0, x, y, z);
                }
            }
        }

    }
    return copy;
}


