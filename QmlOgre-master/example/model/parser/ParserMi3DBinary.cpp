#include <ParserMi3DBinary.h>
#include <Examen.h>
#include <Image3d.hpp>
#include <ImageMask2d.h>
#include <Skeleton.h>
#include <SliceType.h>

#include <fstream>

using namespace std;


ParserMi3DBinary::ParserMi3DBinary()
    : Parser("bmi3d")
{}

Examen*
ParserMi3DBinary::loadFile(string filename)
{
    Examen* examen = NULL;
    ifstream imageReader;
    imageReader.open(filename.c_str(), ios::in | ios::binary);

    if (imageReader) {
        // ENTETE
        bool volumeFlag, skeletonFlag, skeletonSlicesFlag;
        int sliceWidth, sliceHeight, nbSlice;
        float maxVal, resolutionX, resolutionY, resolutionZ;

        imageReader.read((char *)&volumeFlag, sizeof(bool));
        imageReader.read((char *)&skeletonFlag, sizeof(bool));
        imageReader.read((char *)&skeletonSlicesFlag, sizeof(bool));

        imageReader.read((char *)&sliceWidth, sizeof(int));
        imageReader.read((char *)&sliceHeight, sizeof(int));
        imageReader.read((char *)&nbSlice, sizeof(int));

        imageReader.read((char *)&maxVal, sizeof(float));
        imageReader.read((char *)&resolutionX, sizeof(float));
        imageReader.read((char *)&resolutionY, sizeof(float));
        imageReader.read((char *)&resolutionZ, sizeof(float));


        cout<< volumeFlag << " " << sliceWidth
            << " " << sliceHeight << " " << nbSlice
            << " " << maxVal  << endl;

        // VOLUME

        Volume *volume = new Volume(sliceWidth,sliceHeight,nbSlice);
        Mask3d *mask = new Mask3d(sliceWidth,sliceHeight,nbSlice);



        if (volumeFlag)
        {

            int w, h, d;
            imageReader.read((char *)&w, sizeof(int));
            imageReader.read((char *)&h, sizeof(int));
            imageReader.read((char *)&d, sizeof(int));

            int size = w * h *d;
            char *maskData = new char[size];
            imageReader.read((char *)maskData, sizeof(char) * size);
            mask->setData((bool*)maskData);

        }
cout << "mask ok" << endl;
        Skeleton *skeleton = new Skeleton();
        // SKELETON BRANCHES
        if (skeletonFlag)
        {


            // Nodes
            int nNode;
            imageReader.read((char *)&nNode, sizeof(int));
            for (int i=0 ; i < nNode ; i++)
            {
                float x, y, z;
                imageReader.read((char *)&x, sizeof(float));
                imageReader.read((char *)&y, sizeof(float));
                imageReader.read((char *)&z, sizeof(float));

                Node *node = new Node(x, y, z);

                imageReader.read((char *)&node->flagview, sizeof(bool));
                imageReader.read((char *)&node->parent, sizeof(int));

                int nChild;
                imageReader.read((char *)&nChild, sizeof(int));
                for (int j=0 ; j < nChild ; j++)
                {
                    int iChild;
                    imageReader.read((char *)&iChild, sizeof(int));
                    node->children.add(iChild);
                }

                skeleton->addNode(node);
            }

            // Branches
            int nBranch;
            imageReader.read((char *)&nBranch, sizeof(int));
            for (int i=0 ; i < nBranch ; i++)
            {
                Branch *branch = new Branch();

                imageReader.read((char *)&branch->flagview, sizeof(bool));
                imageReader.read((char *)&branch->parent, sizeof(int));
                imageReader.read((char *)&branch->generation, sizeof(int));
                imageReader.read((char *)&branch->length, sizeof(float));
                imageReader.read((char *)&branch->angle.rho, sizeof(double));
                imageReader.read((char *)&branch->angle.theta, sizeof(double));

                int size;
                imageReader.read((char *)&size, sizeof(int));
                char *cstr = new char[size];
                imageReader.read((char *)cstr, sizeof(char) * size);
                branch->name = string(cstr);
                delete []cstr;

                int nChild;
                imageReader.read((char *)&nChild, sizeof(int));
                for (int j=0 ; j < nChild ; j++)
                {
                    int iChild;
                    imageReader.read((char *)&iChild, sizeof(int));
                    branch->children.add(iChild);
                }

                int nNode;
                imageReader.read((char *)&nNode, sizeof(int));
                for (int j=0 ; j < nNode ; j++)
                {
                    int iNode;
                    imageReader.read((char *)&iNode, sizeof(int));
                    branch->nodes.add(iNode);
                }

                skeleton->addBranch(branch);
            }

            // SKELETON SLICES

            if (skeletonSlicesFlag)
            {
                for (int i=0 ; i < skeleton->getBranchesSize() ; i++)
                {
                    Branch *branch = skeleton->getBranch(i);

                    // Slices coord
                    int nSlice;
                    imageReader.read((char *)&nSlice, sizeof(int));
                    for (int j=0 ; j < nSlice ; j++)
                    {
                        SkeletonSlice *skelSlice = new SkeletonSlice();
                        int w, h;
                        imageReader.read((char *)&w, sizeof(int));
                        // Test : ajout de la résolution de l'image ancien / nouveau format bmi3d
                        if (w == -1)
                        {
                            float resx, resy;
                            imageReader.read((char *)&resx, sizeof(float));
                            skelSlice->resolution.x = resx;
                            imageReader.read((char *)&resy, sizeof(float));
                            skelSlice->resolution.y = resy;

                            imageReader.read((char *)&w, sizeof(int));
                        }
                        imageReader.read((char *)&h, sizeof(int));

                        //skelSlice->coord = new Image<Point3D_t<int> >(w, h);

                        for (int k=0 ; k < w * h ; k++)
                        {
                            int x, y, z;
                            imageReader.read((char *)&x, sizeof(int));
                            imageReader.read((char *)&y, sizeof(int));
                            imageReader.read((char *)&z, sizeof(int));

                            //skelSlice->coord->set(k, Point3D_t<int>(x, y, z));
                        }

                        branch->slices.add(skelSlice);
                    }

                    // Slices image
                    imageReader.read((char *)&nSlice, sizeof(int));
                    for (int j=0 ; j < nSlice ; j++)
                    {
                        SkeletonSlice *skelSlice = branch->slices.get(j);

                        int w, h;
                        int flag, slope, intercept;
                        imageReader.read((char *)&flag, sizeof(int));
                        // Test : ajout du slope / intercept de l'image ancien / nouveau format bmi3d
                        if (flag == -1)
                        {
                            imageReader.read((char *)&slope, sizeof(int));
                            imageReader.read((char *)&intercept, sizeof(int));
                            imageReader.read((char *)&w, sizeof(int));
                        }
                        else
                            w = flag;
                        imageReader.read((char *)&h, sizeof(int));

                        //skelSlice->image = new ImageFloat(w, h);
                        if (flag == -1)
                        {
                            //skelSlice->image->setSlope(slope);
                            //skelSlice->image->setIntercept(intercept);
                        }

                        // image
                        float *floatPtrVal = new float[w * h];
                        imageReader.read((char *)floatPtrVal, sizeof(float) * w * h);
                        //  skelSlice->image->setSrc(floatPtrVal);

                        // mask
                        char *charPtrVal = new char[w * h];
                        imageReader.read((char *)charPtrVal, sizeof(char) * w * h);
                        //skelSlice->image->getMask()->setSrc(charPtrVal);
                    }



                }
            }

        }


cout << "skeleton ok" << endl;
        // SLICE        

        ExamenParams* params;
        bool Paramsaffect=false;

        imageReader.read((char *)&nbSlice, sizeof(int));
/*
cout << "NBSLICE :"<<nbSlice << endl;
        for (int c=0 ; c <  nbSlice; c++)
        {
            cout << "Recopie des image :"<<c << endl;
            int w, h, slope, intercept;
            float maxVal;

            // infos
            imageReader.read((char *)&w, sizeof(int));
            imageReader.read((char *)&h, sizeof(int));
            imageReader.read((char *)&slope, sizeof(int));
            imageReader.read((char *)&intercept, sizeof(int));
            imageReader.read((char *)&maxVal, sizeof(float));
            if(!Paramsaffect){
                cout << "Image ok" << endl;
                //string fullpath = filename;
                //GrayTranslationFunction gtf(slope, intercept);
                //params = new ExamenParams(gtf,fullpath);
                //params->getGrayViewWindow().setLuminosity(Wcenter);
                //params->getGrayViewWindow().setContrast(Wwidth);
                Paramsaffect=true;

            }
            int size = w * h;
            cout << "size image 2D: " <<size<< endl;
            // image
            float *sliceImage = new float[size];
            imageReader.read((char *)sliceImage, sizeof(float) * size);
            cout << "Image ok" << endl;
            volume->setSlice(sliceImage,c);

            char *sliceMask = new char[size];
            imageReader.read((char *)sliceMask, sizeof(char) * size);
            delete sliceMask;
            cout << "Image ok" << endl;
        }
*/

cout << "Image ok" << endl;




       // Examen *examen = new Examen(volume,params,mask);
        examen = new Examen(volume);
        cout << "examen ok" << endl;
        examen->setMask(mask);
        cout << "setmask ok" << endl;
        examen->setSkeleton(skeleton);

        cout << "setSkeleton" << endl;

        imageReader.close();


    }
    return examen;
}

bool
ParserMi3DBinary::saveFile(string filename, Examen* examen, MiList<bool>)
{
    ofstream imageWriter;
    imageWriter.open(filename.c_str(), ios::out | ios::binary);

    if (imageWriter) {
        int intVal;
        const Image3d<float>& img = examen->getImageRef();
        int globalSize = img.getGlobalSize();

        //------------------------------
        // IMAGE
        //------------------------------
        intVal = img.getWidth();
        imageWriter.write((char*)&intVal, sizeof(intVal));
        intVal = img.getHeight();
        imageWriter.write((char*)&intVal, sizeof(intVal));
        intVal = img.getDepth();
        imageWriter.write((char*)&intVal, sizeof(intVal));

        const float& dataImg = img.getDataRef();
        imageWriter.write((char*)&dataImg, globalSize * sizeof(dataImg));

        //-------------------------------
        // MASK
        //-------------------------------
        const bool& dataMask = examen->getMaskRef().getDataRef();
        imageWriter.write((char*)&dataMask, globalSize * sizeof(dataMask));

        //-------------------------------
        // MAX
        //-------------------------------
        /*
        intVal = img.getDepth();
        float tabMax[intVal];
        for (int i=0; i<intVal; ++i) {
            Image<float>* slice = img.getSlice(i, CORONAL);
            tabMax[i] = slice->getMax();
            delete slice;
        }
        imageWriter.write((char*)tabMax, intVal * sizeof(*tabMax));
        */


        imageWriter.close();
        return true;
    }
    return false;
}
