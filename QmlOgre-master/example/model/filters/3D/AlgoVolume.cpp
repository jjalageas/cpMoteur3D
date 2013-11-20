#include "AlgoVolume.h"
#include <Examen.h>
#include <ImageMask2d.h>


int AlgoVolume::dx[26] = {1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, -1, -1, -1, -1, -1, -1, -1, -1, 1, 1, 1, 1};
int AlgoVolume::dy[26] = {0, 0, 1, -1, 0, 0, 1, -1, 0, 0, 1, 1, -1, -1, 1, -1, 0, 0, 1, 1, -1, -1, 1, 1, -1, -1};
int AlgoVolume::dz[26] = {0, 0, 0, 0, 1, -1, 0, 0, 1, -1, 1, -1, 1, -1, 0, 0, -1, 1, 1, -1, 1, -1, 1, -1, 1, -1};

/* -------------------------------------------------------------------------
 *            PRIVATE METHODS
 -------------------------------------------------------------------------- */

MiList< Point3D_t<int> *> *AlgoVolume::GetNeighbour(int width, int height, int depth,
                               Point3D_t<int> *ps, int connexity)
{
    MiList< Point3D_t<int> *> *res = new MiList< Point3D_t<int> *>();
    for (int i=0 ; i < connexity ; i++)
    {
        Point3D_t<int> *p = new Point3D_t<int>(ps->x + AlgoVolume::dx[i],
                                ps->y + AlgoVolume::dy[i], ps->z + AlgoVolume::dz[i]);
        if ( (p->x >= 0) && (p->y >= 0) && (p->z >= 0)
            && (p->x < width) && (p->y < height) && (p->z < depth) )
            {
            res->add(p);
        }
    }
    return res;
}

MiList< Point3D_Data_t<int, int> *> *AlgoVolume::GetNeighbour(int width, int height, int depth,
                                      Point3D_Data_t<int, int> *ps, int connexity)
{
    MiList< Point3D_Data_t<int, int> *> *res = new MiList< Point3D_Data_t<int, int> *>();
    int data = ps->data+1;
    for (int i=0 ; i < connexity ; i++)
    {
        Point3D_Data_t<int, int> *p = new Point3D_Data_t<int, int>(ps->x + AlgoVolume::dx[i],
                                           ps->y + AlgoVolume::dy[i], ps->z + AlgoVolume::dz[i],
                                           data);
        if ( (p->x >= 0) && (p->y >= 0) && (p->z >= 0)
            && (p->x < width) && (p->y < height) && (p->z < depth) )
            {
            res->add(p);
        }
    }
    return res;
}

void AlgoVolume::GetNeighbourHB(int width, int height, int depth,
                                      MiList<Point3D_t< int> *>* file,
                                      Image3d<bool>*visited, Image3d<bool>*VolumeTotal,
                                      Examen*examen, Image3d<bool>*res,
                                      int Smin, int Smax,
                                      Point3D_t<int>* ps, int connexity)
{
    Image3d<float>* img = examen->getImage();
    for (int i=0 ; i < connexity ; i++) {
        Point3D_t<int> p(ps->x + AlgoVolume::dx[i],
                   ps->y + AlgoVolume::dy[i],
                   ps->z + AlgoVolume::dz[i]);
        if (p.x >= 0 && p.y >= 0 && p.z >= 0 &&
            p.x < width && p.y < height && p.z < depth) {

            int index=p.z*width*height + p.y*width + p.x;
            int value=img->get(p.x,p.y,p.z);
            // cout<<"      value="<<value<< "  Smin="<<Smin<< "  Smax="<<Smax<<endl;
            if (VolumeTotal->get(index) == 1  ) {
                if(value >= Smin && value <= Smax) {
                    if  (visited->get(index)== 0) {
                        file->add(new Point3D_t< int>(p.x,p.y,p.z));
                        res->set(1, index);
                        visited->set(1, index);
                    }
                }
            }
        }
    }
}


/* -------------------------------------------------------------------------
 *            PUBLIC METHODS
 -------------------------------------------------------------------------- */





/*****************************************************************************
             Accesseur, et fonction de transfert

  *****************************************************************************/


//richard
Point3D_t<int>* AlgoVolume::getPointFromIndex(int index, int w,int h) {
    int z=index/(w*h);
    int y=(index-(z*w*h))/w;
    int x=(index-(z*w*h))%w;

    return new Point3D_t<int>(x,y,z);
}

Point3D_t<int> AlgoVolume::getSPointFromIndex(int index, int w,int h) {
    int x=index%w;
    int y=(index/w)%h;
    int z=(index-y*w-x)/(w*h);

    return  Point3D_t<int>(x,y,z);
}

/*MiList<Point3D_t<int> *>*  AlgoVolume::setListOfPointFromVolume(Image3d<float> *volume) {
    int width = volume->getPointWidth();
    int height = volume->getPointHeight();
    int depth = volume->getPointDepth();
    int size=width*height*depth;
    MiList<Point3D_t<int> *>*  res = new MiList<Point3D_t< int> *>;

    int compteur=0;
    for (int z=0; z < size; ++z){
        if (volume->getPoint(z) == 1) {
            res->add(getPointFromIndex(z, width,height));
            compteur++;
        }
    }
    return res;
}*/


/*void  AlgoVolume::setVolumeFromlstPoints(Image3d<float> *volume, MiList<Point3D_t<int> *>* lst) {
    volume->clear();
    for (int z=0 ; z < lst->size() ; z++)
    {
        Point3D_t<int> *p =lst->get(z) ;
        volume->setPoint(1,p->x,p->y,p->z);
    }
}*/


/*void AlgoVolume::MaskImageToVolume(Image3d<float> *volume, ImageMask2d *image, int z)
{
    Image3d<bool>* mask=image->getMaskRef();
    MaskImageToVolume(volume, mask, image, z);
}

//mask est un mask 3D et image est un mask 2D
void AlgoVolume::MaskImageToVolume(Volume *volume, Image3d<bool> *mask, ImageMask2d *image, int z)
{
    int w = volume->getPointWidth();
    int h = volume->getPointHeight();
    //cout<<"w="<< w<<"  h="<< h<<endl;

    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) {
            int value = image->getImageRef(j, i);
            //cout<<"value:"<<value <<endl;
            if(value==1) {
                //cout<<"      mask==1"<<endl;
                mask->set(1,j,i,z);
            }
        }
}*/


//mask est un mask 3D et image est un mask 2D
/*void AlgoVolume::MaskImageToVolume(Volume *volume,Image3d<bool> *mask,char *image,int z)
{
    int w = volume->getPointWidth();
    int h = volume->getPointHeight();
    //cout<<"    MaskImageToVolume::w="<< w<<"  h="<< h<<endl;

    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) {
        int index=i*w+j;
        int value = image[index];
        //cout<<"      value:"<<value <<endl;
        if(value==1){
            //cout<<"           add"<<endl;
            mask->set(1,j,i,z);
        }
    }
}*/

/*void AlgoVolume::VolumeToMaskImage(Examen *examen)
{
    Image3d<bool> *mask = examen->getVolume()->getPoint();
    int depth = mask->getDepth();
    int height = mask->getHeight();
    int width = mask->getWidth();

    for (int i = 0 ; i < depth ; ++i)
    {
        Image3d<bool> *mask2D = examen->getSlice(i)->getImage()->getMask();
        for (int j = 0 ; j < height ; ++j)
        {
            for (int k = 0 ; k < width ; ++k)
            {
                if (mask->get(k, j, i) == 1)
                    mask2D->set(1, k, j);
            }
        }
    }
}*/

/*void AlgoVolume::VolumeToMaskImage(Examen *examen, Image3d<bool>* vol)
{
    int depth = examen->getDepth();
    int height = examen->getHeight();
    int width = examen->getWidth();

    int sizeImage=width*height;
    char* volData=vol->getSrc();
    for (int i = 0; i < depth; ++i) {
        char *mask2D = examen->getSlice(i)->getImage()->getMask()->getSrc();
        int index=i*sizeImage;
        memcpy(mask2D, &volData[index], sizeof(char)*sizeImage);
    }
}*/

//mask est un mask 3D et image est un mask 2D
void AlgoVolume::MaskImageToVolume(Image3d<float> *,Image3d<bool>* mask,bool*image,int z,int w,int h)
{
    for (int i = 0; i < h; ++i)
        for (int j = 0; j < w; ++j) {
        if (image[i * w + j] == true) {
            mask->set(true,j,i,z);
        }
    }
}

//mask est un mask 3D et image est un mask 2D
void AlgoVolume::SliceImageToVolume(Image3d<bool> *volume,Image3d<bool>* mask,Image<Point3D_t<int> > *sliceCoord,int w,int h)
{
    //replace le rg dans notre volume
    int size = w * h;
    for (int n=0 ; n < size ; n++)
    {
        if (mask->get(n) == 1)
        {

            Point3D_t<int> coord = sliceCoord->get(n);
            volume->set(1,coord.x,coord.y,coord.z);
        }
    }
}


//definit une boite englobante pour le volume pour eviter du temps de calcul
/*MiList<int>AlgoVolume::ComputeFrontiere(int w,int h,int d, bool *volume,int value){
    int zmax=0,ymax=0,xmax=0;
    int zmin=1000000,ymin=1000000,xmin=1000000;
    int size=w* h* d;
    for(int p=0;p<size;++p) {
        if(volume[p]==value) {
            Point3D_t<int>* point=AlgoVolume::getPointFromIndex(p,  w, h);

            if(point->x>xmax)xmax=point->x;
            if(point->x<xmin)xmin=point->x;
            if(point->y>ymax)ymax=point->y;
            if(point->y<ymin)ymin=point->y;
            if(point->z>zmax)zmax=point->z;
            if(point->z<zmin)zmin=point->z;
            delete point;
        }
    }
    MiList<int> lstFrontiere;

    if(zmax < (d-1)) zmax+=1;else zmax=d-1;
    if(ymax < (h-1)) ymax+=1;else ymax=h-1;
    if(xmax < (w-1)) xmax+=1;else xmax=w-1;

    lstFrontiere.add(zmin);
    lstFrontiere.add(zmax);
    lstFrontiere.add(ymin);
    lstFrontiere.add(ymax);
    lstFrontiere.add(xmin);
    lstFrontiere.add(xmax);

    return lstFrontiere;
}*/


/*****************************************************************************
              selection tout points
  *****************************************************************************/

/*void AlgoVolume::AllPoints(Examen *examen)
{
    Volume *volume = examen->getVolume();
    Image3d<bool> *mask = examen->getMaskRef();
    volume->empty();

    int width = examen->getWidth();
    int height = examen->getHeight();
    int depth = examen->getDepth();

    volume->setPointSize(width, height, depth);

    for (int z=0 ; z < depth ; z++)
        for (int y=0 ; y < height ; y++)
            for (int x=0 ; x < width ; x++)
                if (mask->get(x, y, z) == true)
                    volume->set(1, x, y, z);
}*/

/*****************************************************************************
              seuille une image 3D
  *****************************************************************************/

Image3d<bool>* AlgoVolume::biseuillage3D(Image3d<float> * volume ,int Smin, int Smax){
    //réalise un biseuillage des contours
    Image3d<bool>* contour=new Image3d<bool>(volume->getWidth(),volume->getHeight(),volume->getDepth());
    int size=volume->getWidth()*volume->getHeight()*volume->getDepth();
    for(int i=0;i<size;++i){
     if(volume->get(i)>Smin && volume->get(i)<Smax)
         contour->set(1,i);
     else
         contour->set(0,i);
    }
    return contour;
}


/*****************************************************************************
              Region Growing
  *****************************************************************************/

Image3d<bool>* AlgoVolume::CTRG2(int width,int  height,int depth, Image3d<bool>* volume,Point3D_t<int> seed, int connexity)
{
    Image3d<bool> *visited = new Image3d<bool>(width, height, depth);

    // file (FIFO) contenant des Point3D_t qui ont la valeur de masque à 1, NON visité
    MiList<Point3D_Data_t<int, int> *> file;

    // SEED
    if ( (seed.x >= 0) && (seed.x < width) && (seed.y >= 0) && (seed.y < height)
        && (seed.z >= 0) && (seed.z < depth) )
        {
        if (volume->get(seed.x, seed.y, seed.z) == 1)
        {
            Point3D_Data_t<int, int> *first =
                    new Point3D_Data_t<int, int>(seed.x, seed.y, seed.z, 0);
            visited->set(1, first->x, first->y, first->z);
            file.add(first);
        }
    }


    // FILE
    while(file.size() > 0)
    {
        Point3D_Data_t<int, int> *p = file.getFirst();
        file.removeFirst();

        MiList< Point3D_Data_t<int, int> *> *neighbour =
                AlgoVolume::GetNeighbour(width, height, depth, p, connexity);

        int neighbourSize = neighbour->size();
        for (int i=0 ; i < neighbourSize ; i++)
        {
            Point3D_Data_t<int, int> *n = neighbour->get(i);

            if ( (visited->get(n->x, n->y, n->z) == 0)
                && (volume->get(n->x, n->y, n->z) == 1) )
                {
                visited->set(1, n->x, n->y, n->z);
                file.add(n);
            }
            else
                delete n;
        }
        delete p;
        delete neighbour;
    }
    return visited;
}



/*void AlgoVolume::CTRG(Examen *examen, int connexity, int distance)
{
    Volume *volume = examen->getVolume();
    volume->empty();

    int width = examen->getWidth();
    int height = examen->getHeight();
    int depth = examen->getDepth();

    //temporaire // TODO : nothing in fact -_-
    width=512;

    volume->setPointSize(width, height, depth);
    if (distance > 0)
        volume->setDataSize(width, height, depth);

    Image3d<bool> *visited = new Image3d<bool>(width, height, depth);

    // file (FIFO) contenant des Point3D_t qui ont la valeur de masque à 1, NON visité
    MiList<Point3D_Data_t<int, int> *> file;

    // SEED
    Point3D_t<int> seed = examen->getSeed();
    if ( (seed.x >= 0) && (seed.x < width) && (seed.y >= 0) && (seed.y < height)
        && (seed.z >= 0) && (seed.z < depth) )
        {
        if (examen->getPixelMask(seed.x, seed.y, seed.z) == 1)
        {
            Point3D_Data_t<int, int> *first =
                    new Point3D_Data_t<int, int>(seed.x, seed.y, seed.z, 0);
            visited->set(1, first->x, first->y, first->z);
            volume->setPoint(1, first->x, first->y, first->z);
            file.add(first);
        }
    }

    int distMax = 0;

    // FILE
    while(file.size() > 0)
    {
        Point3D_Data_t<int, int> *p = file.getFirst();
        file.removeFirst();

        if (distance > 0)
        {
            int dist = (int )p->data / distance;

            if (dist > distMax)
                distMax = dist;
            volume->setData(dist, p->x, p->y, p->z);
        }

        MiList< Point3D_Data_t<int, int> *> *neighbour =
                AlgoVolume::GetNeighbour(width, height, depth, p, connexity);

        int neighbourSize = neighbour->size();

        for (int i=0 ; i < neighbourSize ; i++)
        {
            Point3D_Data_t<int, int> *n = neighbour->get(i);

            if ( (visited->get(n->x, n->y, n->z) == 0)
                && (examen->getPixelMask(n->x, n->y, n->z) == 1) )
                {
                visited->set(1, n->x, n->y, n->z);
                volume->setPoint(1, n->x, n->y, n->z);
                file.add(n);
            }
            else
                delete n;
        }
        delete p;
        delete neighbour;
    }

    if (distance > 0)
        volume->setDataMax(distMax);

    delete visited;
}*/


/*void AlgoVolume::NCRG(Examen *examen, int connexity, int distance)
{
    Volume *volume = examen->getVolume();
    volume->empty();

    int width = examen->getWidth();
    int height = examen->getHeight();
    int depth = examen->getDepth();

    volume->setPointSize(width, height, depth);
    if (distance > 0)
        volume->setDataSize(width, height, depth);

    Image3d<bool> *visited = new Image3d<bool>(width, height, depth);

    // file (FIFO) contenant des Point3D_t qui ont la valeur de masque à 1, NON visité
    MiList< Point3D_Data_t<int, int> *> file;

    // SEED
    Point3D_t<int> seed = examen->getSeed();
    if ( (seed.x >= 0) && (seed.x < width) && (seed.y >= 0) && (seed.y < height)
        && (seed.z >= 0) && (seed.z < depth) )
        {
        if (examen->getPixelMask(seed.x, seed.y, seed.z) == 1)
        {
            Point3D_Data_t<int, int> *first =
                    new Point3D_Data_t<int, int>(seed.x, seed.y, seed.z, 0);
            visited->set(1, first->x, first->y, first->z);
            file.add(first);
        }
    }

    int distMax = 0;

    // FILE
    while(file.size() > 0)
    {
        Point3D_Data_t<int, int> *p = file.getFirst();
        file.removeFirst();

        if (distance > 0)
        {
            int dist = (int )p->data / distance;
            if (dist > distMax)
                distMax = dist;
            volume->setData(dist, p->x, p->y, p->z);
        }

        MiList<Point3D_Data_t<int, int> *> *neighbour =
                AlgoVolume::GetNeighbour(width, height, depth, p, connexity);
        int neighbourSize = neighbour->size();
        int validNeighbour = true;

        for (int i=0 ; (i < neighbourSize) && validNeighbour ; i++)
        {
            Point3D_Data_t<int, int> *n = neighbour->get(i);

            if (examen->getPixelMask(n->x, n->y, n->z) == 0)
                validNeighbour = false;
        }

        if (validNeighbour)
        {
            volume->setPoint(1, p->x, p->y, p->z);

            for (int i=0 ; i < neighbourSize ; i++)
            {
                Point3D_Data_t<int, int> *n = neighbour->get(i);

                if (visited->get(n->x, n->y, n->z) == 0)
                {
                    visited->set(1, n->x, n->y, n->z);
                    file.add(n);
                }
                else
                    delete n;
            }
        }
        else
        {
            for (int i=0 ; i < neighbourSize ; i++)
                delete neighbour->get(i);
        }
        delete neighbour;
        delete p;
    }

    if (distance > 0)
        volume->setDataMax(distMax);

    delete visited;
}*/


MiList<Point3D_t<int>* >* AlgoVolume::GetNeighbor(int vwidth, int vheight, int vdepth,
                                                  Point3D_t<int>* Voxel, int connexity)
{
    int borneInf=0;
    int borneSup=0;
    switch(connexity)
    {
    case 18://18 connexité(locale)
        borneInf=1;
        borneSup=0;
        break;
    case 26://26 connexité(locale)
        borneInf=1;
        borneSup=1;
        break;
    case 64://64 connexité(globale)
        borneInf=2;
        borneSup=2;
        break;
    case 128://128 connexité(globale)
        borneInf=3;
        borneSup=3;
        break;
    }
    MiList<Point3D_t<int> *> *res = new MiList<Point3D_t<int> *>();

    for ( int k =Voxel->z-borneInf ; k <= Voxel->z+borneSup ; k++)
    {
        if ( k >= 0 && k < vdepth)
        {
            for ( int j = Voxel->y-borneInf ; j <= Voxel->y+borneSup ; j++)
            {
                if ( j >= 0 && j < vheight)
                {
                    for ( int i = Voxel->x-borneInf ; i <= Voxel->x+borneSup ; i++)
                    {
                        if ( i >= 0 && i < vwidth)
                        {
                            if ( i >= 0 && i < vwidth)
                            {

                                res->add(new Point3D_t<int>(i, j, k) );

                            }
                        }
                    }
                }
            }
        }
    }

    return res;
}


// TODO : Check and improve. C'est la fonction que nosu a passé le chargé de Td
// pour améliorer la vitesse du voisinnage la première fois !
void AlgoVolume::GetNeighbor_Conditionnel_Threshold_Intersection
        (MiList<Point3D_t< int> *>* file,
         Image3d<bool>*visited, Image3d<bool>*VolumeTotal, Examen*examen,
         int Smin, int Smax, Image3d<bool>*res, int width, int height, int depth,
         Point3D_t<int>* Voxel, int borneInf,int borneSup)
{
    Image3d<float>* img = examen->getImage();
    //declaration des variables
    int xn, yn, zn, xnt, ynt, znt;
    int x0, y0 ,z0, x0t, y0t, z0t;

    //calcul des bornes
    z0t = (Voxel->z-borneInf); y0t = (Voxel->y-borneInf); x0t = (Voxel->x-borneInf);
    znt = (Voxel->z +borneSup+1 ); ynt = (Voxel->y +borneSup+1 ); xnt = (Voxel->x +borneSup+1 );
    z0 = z0t <= 0 ? 0 : (z0t); zn = znt < depth ? znt : depth;
    y0 = y0t <= 0 ? 0 : (y0t); yn = ynt < height ? ynt : height;
    x0 = x0t <= 0 ? 0 : (x0t); xn = xnt < width ? xnt : width;

    int sizeImage=width*height;

    //cout<<"width:"<<width<<"  height"<<height<<"  depth:"<<depth<<endl;
      // cout<<"Point courant:"<<Voxel->x<<","<<Voxel->y<<","<<Voxel->z<<endl;
    //cout<<"borne:"<<borneInf<<","<<borneSup<<endl;
    //verifications des conditions
    for(int indexz = z0; indexz < zn; indexz ++) {
        int POSITIONZ=indexz*sizeImage;
        for(int indexy = y0; indexy < yn; indexy ++) {
            int POSITIONY=indexy*width;
            for(int indexx = x0; indexx < xn; indexx ++) {
                if(indexz!=Voxel->z  ||  indexy!=Voxel->y || indexx!=Voxel->x) {
                    int index = POSITIONZ + POSITIONY + indexx;
                    int value=img->get(indexx, indexy, indexz);

                    // cout<<"      value="<<value<< "  Smin="<<Smin<< "  Smax="<<Smax<<endl;
                    if (VolumeTotal->get(index) == 1) {
                        if(value >= Smin && value <= Smax) {
                            if  (visited->get(index)== 0) {
                                file->add(new Point3D_t< int>(indexx,indexy,indexz));
                                res->set(1, index);
                                visited->set(1, index);
                            }
                        }
                    }
                }
            }
        }
    }
}
