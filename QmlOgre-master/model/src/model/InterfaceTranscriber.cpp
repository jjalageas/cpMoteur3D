#include <InterfaceTranscriber.h>
#include <Examen.h>
#include <Image3d.hpp>
#include <ImageMask2d.h>
#include <Skeleton.h>
#include <iostream>

using namespace std;


//--------------------------------
// Image
//--------------------------------
Image<int>*
InterfaceTranscriber::FromImage(ImageMask2d* image, bool showMask)
{
    Image<float>* tmp = image->getImageRef();
    Image<int>* res = InterfaceTranscriber::FromImage(tmp);
    if (showMask) {
        Image<bool>* mask = image->getMaskRef();
        int size = mask->getWidth() * mask->getHeight();
        for (int i=0; i<size; ++i) {
            if (mask->get(i) == 1) {
                res->set(-1, i);
            }
            else if (mask->get(i) == 2) {
                res->set(-2, i);
            }
            else if (mask->get(i) == 3) {
                res->set(-3, i);
            }
        }
    }
    return res;
}

Image<int>*
InterfaceTranscriber::FromImage(ImageMask2d* image,
                                GrayViewWindow& window,
                                bool showImage, bool showMask)
{
    //int maxVal = image->getMaxVal();
    GrayValue* min = window.getMin();
    int windowingMin = min->getExamenValue();
    //windowingMin = (windowingMin < 0) ? 0 : windowingMin;
    delete min; min = NULL;

    GrayValue* max = window.getMax();
    int windowingMax = max->getExamenValue();
    //windowingMax = (windowingMax > maxVal) ? maxVal : windowingMax;
    delete max; max = NULL;

    float colorRatio = 255.;
    if (windowingMax - windowingMin != 0) {
        colorRatio /= (float)(windowingMax - windowingMin);
    }

    int width = image->getWidth();
    int height = image->getHeight();
    Image<int>* res = new Image<int>(width, height);
    Image<bool>* mask = image->getMaskRef();

    for (int j=0; j<height; ++j) {
        for (int i=0; i<width; ++i) {
            int val = 0;
            if (showMask && (mask->get(i, j) == true)) {
                val = -1;
            }
            else if (showImage) {
                float color = image->get(i, j);
                color = (color < windowingMin) ? windowingMin : color;
                color = (color > windowingMax) ? windowingMax : color;
                color = (color - windowingMin) * colorRatio;
                val = (int)color;
            }
            res->set(val, i, j);
        }
    }
    return res;
}

Image<int>*
InterfaceTranscriber::FromImage(ImageMask2d *image, ImageMask2d *image2,
                                GrayViewWindow& window)
{
    int maxVal = image->getMaxVal();
    int width = image->getWidth();
    int height = image->getHeight();

    GrayValue* min = window.getMin();
    int windowingMin = min->getExamenValue();
    windowingMin = (windowingMin < 0) ? 0 : windowingMin;
    delete min; min = NULL;

    GrayValue* max = window.getMax();
    int windowingMax = max->getExamenValue();
    windowingMax = (windowingMax > maxVal) ? maxVal : windowingMax;
    delete max; max = NULL;

    float colorRatio = 255.;
    if ((windowingMax - windowingMin) != 0) {
        colorRatio /= (float)(windowingMax - windowingMin);
    }

    Image<int>* res = new Image<int>(width, height);
    Image<bool>* mask = image->getMaskRef();
    Image<bool>* mask2 = image2->getMaskRef();

    for (int j=0; j<height; ++j) {
        for (int i=0; i<width; ++i) {
            int val = 0;
            // affichage du mask
            if (mask->get(i, j) == 1 && mask2->get(i, j) == 0) {
                val = -1;
            }
            if (mask2->get(i, j) == 1 && mask->get(i, j) == 0) {
                val = -2;
            }
            if (mask2->get(i, j) == 1 && mask->get(i, j) == 1) {
                val = -3;
            }
            // affichage de l'image
            if (val == 0) {
                float color = image->get(i, j);
                color = (color < windowingMin) ? windowingMin : color;
                color = (color > windowingMax) ? windowingMax : color;
                color = (color - windowingMin) * colorRatio;
                val = (int)color;
            }
            res->set(val, i, j);
        }
    }
    return res;
}

Image<int>*
InterfaceTranscriber::FromImage(ImageMask2d* image, ImageMask2d* image2, ImageMask2d* image3,
                                GrayViewWindow& window)
{
    int maxVal = image->getMaxVal();
    int width = image->getWidth();
    int height = image->getHeight();

    GrayValue* min = window.getMin();
    int windowingMin = min->getExamenValue();
    windowingMin = (windowingMin < 0) ? 0 : windowingMin;
    delete min; min = NULL;

    GrayValue* max = window.getMax();
    int windowingMax = max->getExamenValue();
    windowingMax = (windowingMax > maxVal) ? maxVal : windowingMax;
    delete max; max = NULL;

    float colorRatio = 255.;
    if ((windowingMax - windowingMin) != 0) {
        colorRatio /= (float)(windowingMax - windowingMin);
    }

    Image<int>* res = new Image<int>(width, height);
    Image<bool>* mask = image->getMaskRef();
    Image<bool>* mask2 = image2->getMaskRef();
    Image<bool>* mask3 = image3->getMaskRef();

    for (int j=0; j<height; ++j) {
        for (int i=0; i<width; ++i) {
            int val = 0;
            // affichage du mask
            if (mask->get(i, j) == 1 && mask2->get(i, j) == 0 &&
                    mask3->get(i, j) == 0) {
                val = -1;
            }
            if (mask2->get(i, j) == 0 && mask->get(i, j) == 1 &&
                    mask3->get(i, j) == 0) {
                val = -2;
            }
            if (mask2->get(i, j) == 0 && mask->get(i, j) == 0 &&
                    mask3->get(i, j) == 1) {
                val = -3;
            }
            // affichage de l'image
            if (val == 0) {
                float color = image->get(i, j);
                color = (color < windowingMin) ? windowingMin : color;
                color = (color > windowingMax) ? windowingMax : color;
                color = (color - windowingMin) * colorRatio;
                val = (int)color;
            }
            res->set(val, i, j);
        }
    }
    return res;
}

Image<int>*
InterfaceTranscriber::FromImage(Image<float>* image)
{
    int width = image->getWidth();
    int height = image->getHeight();
    float min = image->getMin();
    float max = image->getMax();
    std::cout << "Itf transcriber - Min : " << min << ", max : " << max << std::endl;

    float colorRatio = 255.f / (max - min);
    Image<int>* res = new Image<int>(width, height);

    for (int i=0; i < width*height; ++i) {
        float color = image->get(i);
        //cout << "i " << i << "-" << color << " " << endl;
        color -= min;
        color *= colorRatio;
        res->set((int)color, i);
    }
    return res;
}


//--------------------------------
// Volume
//--------------------------------
Triplet_t<float*,char*,int>
InterfaceTranscriber::ToVBO (MiList< Point3D_Color_t<float>* >* points)
{
    Triplet_t<float*,char*,int> res(NULL, NULL, 0);
    if (points != NULL) {
        int size = points->size();
        float* indice = new float[3*size];
        char* couleur = new char[3*size];
        res = Triplet_t<float*,char*,int>(indice, couleur, size);

        Point3D_Color_t<float>* p = 0;
        for (int i=0; i<size; ++i) {
            p = points->get(i);
            //indice
            indice[i*3] = (float)p->x;
            indice[i*3+1] = (float)p->y;
            indice[i*3+2] = (float)p->z;
            //couleur
            couleur[i*3] = (char)p->red;
            couleur[i*3+1] = (char)p->green;
            couleur[i*3+2] = (char)p->blue;
        }
    }
    return res;
}


//--------------------------------
// Skeleton
//--------------------------------
MiList< MiList<Segment> >*
InterfaceTranscriber::FromSkeletonWire(Examen* examen)
{
    return InterfaceTranscriber::FromSkeletonWire(examen, NULL);
}

MiList< MiList<Segment> >*
InterfaceTranscriber::FromSkeletonWire(Examen* examen,
                                       MiList<int>* special)
{
    ExamenParams& infos = examen->getParams();
    float dx = infos.resolutionX;
    float dy = infos.resolutionY;
    float dz = infos.resolutionZ;

    Skeleton* skeleton = examen->getSkeleton();

    int width = examen->getImageRef().getWidth() / 2;
    int height = examen->getImageRef().getHeight() / 2;
    int depth = examen->getImageRef().getDepth() / 2;

    Color colorSpecial(159, 62, 0);
    Color colorDefault = (special == NULL) ? colorSpecial : Color(255,255,0);

    int branchesSize = skeleton->getBranchesSize();

    MiList< MiList<Segment> >* branches = new MiList< MiList<Segment> >();
    for (int i=0; i<branchesSize; ++i) {
        Branch* branch = skeleton->getBranch(i);
        MiList<Segment> segList;
        if (branch->flagview) {
            Color color = colorDefault;
            if ((special != NULL) && (special->size() > 0)) {
                color = (special->isExist(i)) ? colorSpecial : colorDefault;
            }
            for (int b=1; b < branch->nodes.size(); ++b) {
                Node* srcP = skeleton->getNode(branch->nodes.get(b-1));
                Node* trgP = skeleton->getNode(branch->nodes.get(b));
                Point3D_t<float> src((srcP->x - width) * dx, - (srcP->z - depth) * dz,
                                     (srcP->y - height) * dy);
                Point3D_t<float> trg((trgP->x - width) * dx, - (trgP->z - depth) * dz,
                                     (trgP->y - height) * dy);
                segList.add(Segment(src, trg, color));
            }
        }
        branches->add(segList);
    }
    return branches;
}
