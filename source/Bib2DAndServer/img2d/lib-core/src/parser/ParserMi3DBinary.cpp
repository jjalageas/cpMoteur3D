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
        int width, height, depth, globalSize;

        //------------------------------
        // IMAGE
        //------------------------------
        imageReader.read((char*)&width, sizeof(width));
        imageReader.read((char*)&height, sizeof(height));
        imageReader.read((char*)&depth, sizeof(depth));

        globalSize = width * height * depth;
        float* dataImg = new float[globalSize];
        imageReader.read((char*)dataImg, globalSize * sizeof(*dataImg));

        Image3d<float>* img = new Image3d<float>(dataImg, width, height, depth);

        //-------------------------------
        // MASK
        //-------------------------------
        bool* dataMask = new bool[globalSize];
        imageReader.read((char*)dataMask, globalSize * sizeof(*dataMask));

        Image3d<bool>* mask = new Image3d<bool>(dataMask, width, height, 1);

        //-------------------------------
        // MAX
        //-------------------------------
        /*
        float* tabMax = new float[depth];
        imageReader.read((char*)tabMax, depth * sizeof(*tabMax));
        */

        examen = new Examen(img, NULL, mask);
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
