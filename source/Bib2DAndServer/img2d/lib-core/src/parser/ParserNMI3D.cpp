#include <ParserNMI3D.h>
#include <Examen.h>
#include <Skeleton.h>
#include <ImageMask2d.h>
#include <Information.h>

#include <fstream>

#define MAX_STRING 255

using namespace std;


ParserNMi3D::ParserNMi3D()
    : Parser(string("nmi3d"))
{}

Examen*
ParserNMi3D::loadFile(string filename)
{
    Examen* examen = NULL;
    ifstream imageReader;
    imageReader.open(filename.c_str(), ios::in | ios::binary);
    cout << "load3DFile NMI3D: " << filename << endl;

    if (imageReader) {
        // ENTETE

        bool boolValue;
        MiList<bool> options;
        imageReader.read((char*)&boolValue, sizeof(boolValue));
        options.add(boolValue);
        imageReader.read((char*)&boolValue, sizeof(boolValue));
        options.add(boolValue);
        imageReader.read((char*)&boolValue, sizeof(boolValue));
        options.add(boolValue);
        imageReader.read((char*)&boolValue, sizeof(boolValue));
        options.add(boolValue);

        int width, height, depth;
        imageReader.read((char*)&width, sizeof(width));
        imageReader.read((char*)&height, sizeof(height));
        imageReader.read((char*)&depth, sizeof(depth));

        float resolutionX, resolutionY, resolutionZ;
        imageReader.read((char*)&resolutionX, sizeof(resolutionX));
        imageReader.read((char*)&resolutionY, sizeof(resolutionY));
        imageReader.read((char*)&resolutionZ, sizeof(resolutionZ));

        int globalSize = width * height * depth;

        // DATA

        Volume* img = NULL;
        if (options.get(0)) {
            float* data = new float[globalSize];
            imageReader.read((char*)data, globalSize * sizeof(*data));
            img = new Volume(data, width, height, depth);
        }

        // MASK

        Mask3d* mask = NULL;
        if (options.get(1)) {
            bool* data = new bool[globalSize];
            imageReader.read((char*)data, globalSize * sizeof(*data));
            mask = new Mask3d(data, width, height, 1);
        }

        // SKELETON

        if (options.get(2)) {
            cerr << "Option not yet implemented" << endl;
        }

        // INFORMATIONS

        ExamenParams* params = NULL;
        if (options.get(3)) {
            int size;
            imageReader.read((char*)&size, sizeof(size));
            int length;
            char title[MAX_STRING];
            char description[MAX_STRING];
            Information* infos = new Information();
            for (int i=0; i<size; ++i) {
                imageReader.read((char*)&length, sizeof(length));
                imageReader.read((char*)title, length * sizeof(*title));
                imageReader.read((char*)&length, sizeof(length));
                imageReader.read((char*)description, length * sizeof(*description));
                infos->addInformation(title, description);
            }
            int slope, intercept;
            imageReader.read((char*)&slope, sizeof(slope));
            imageReader.read((char*)&intercept, sizeof(intercept));
            GrayTranslationFunction gtf(slope, intercept);
            params = new ExamenParams(gtf, filename, infos);
            params->width = width;
            params->height = height;
            params->depth = depth;
            params->resolutionX = resolutionX;
            params->resolutionY = resolutionY;
            params->resolutionZ = resolutionZ;
        }

        examen = new Examen(img, params, mask);
    }
    imageReader.close();
    return examen;
}

bool
ParserNMi3D::saveFile(string filename, Examen* examen, MiList<bool> options)
{
    ofstream imageWriter;
    imageWriter.open(filename.c_str(), ios::out | ios::binary);
    cout << "save3DFile NMI3D: " << filename << endl;

    if (imageWriter && options.size() == 4) {
        bool boolVal;
        int intVal, intVal2;
        float floatVal;
        bool* boolPtrVal;
        float* floatPtrVal;
        int size3D = examen->getImage()->getWidth() *
                examen->getImage()->getHeight() *
                examen->getImage()->getDepth();

        // ENTETE

        boolVal = options.get(0);
        imageWriter.write((char*)&boolVal, sizeof(bool));
        boolVal = options.get(1);
        imageWriter.write((char*)&boolVal, sizeof(bool));
        boolVal = options.get(2);
        imageWriter.write((char*)&boolVal, sizeof(bool));
        boolVal = options.get(3);
        imageWriter.write((char*)&boolVal, sizeof(bool));

        intVal = examen->getImage()->getWidth();
        imageWriter.write((char*)&intVal, sizeof(int));
        intVal = examen->getImage()->getHeight();
        imageWriter.write((char*)&intVal, sizeof(int));
        intVal = examen->getImage()->getDepth();
        imageWriter.write((char*)&intVal, sizeof(int));

        floatVal = examen->getParams().resolutionX;
        imageWriter.write((char*)&floatVal, sizeof(float));
        floatVal = examen->getParams().resolutionY;
        imageWriter.write((char*)&floatVal, sizeof(float));
        floatVal = examen->getParams().resolutionZ;
        imageWriter.write((char*)&floatVal, sizeof(float));

        // DATA

        if (options.get(0)) {
            floatPtrVal = examen->getImage()->getData();
            imageWriter.write((char*)floatPtrVal, size3D * sizeof(float));
        }

        // VOLUME

        if (options.get(1)) {
            boolPtrVal = examen->getMask()->getData();
            imageWriter.write((char*)boolPtrVal, size3D * sizeof(bool));
        }

        // SKELETON

        if (options.get(2)) {
            Skeleton* skeleton = examen->getSkeleton();

            // Nodes
            intVal = skeleton->getNodesSize();
            imageWriter.write((char*)&intVal, sizeof(int));
            for (int i=0; i < intVal; ++i) {
                Node* node = skeleton->getNode(i);

                imageWriter.write((char*)&node->x, sizeof(float));
                imageWriter.write((char*)&node->y, sizeof(float));
                imageWriter.write((char*)&node->z, sizeof(float));
                imageWriter.write((char*)&node->flagview, sizeof(bool));
                imageWriter.write((char*)&node->parent, sizeof(int));

                intVal2 = node->children.size();
                imageWriter.write((char*)&intVal2, sizeof(int));
                for (int j=0; j < node->children.size(); ++j) {
                    intVal2 = node->children.get(j);
                    imageWriter.write((char*)&intVal2, sizeof(int));
                }
            }

            // Branches
            intVal = skeleton->getBranchesSize();
            imageWriter.write((char*)&intVal, sizeof(int));
            for (int i=0; i < intVal; ++i) {
                Branch* branch = skeleton->getBranch(i);

                imageWriter.write((char*)&branch->flagview, sizeof(bool));
                imageWriter.write((char*)&branch->parent, sizeof(int));
                imageWriter.write((char*)&branch->generation, sizeof(int));
                imageWriter.write((char*)&branch->length, sizeof(float));
                imageWriter.write((char*)&branch->angle.rho, sizeof(double));
                imageWriter.write((char*)&branch->angle.theta, sizeof(double));

                intVal2 = (int)branch->name.size() + 1;
                imageWriter.write((char*)&intVal2, sizeof(int));
                imageWriter.write((char*)branch->name.c_str(), intVal2 * sizeof(char));

                intVal2 = branch->children.size();
                imageWriter.write((char*)&intVal2, sizeof(int));
                for (int j=0; j < branch->children.size(); ++j) {
                    intVal2 = branch->children.get(j);
                    imageWriter.write((char*)&intVal2, sizeof(int));
                }

                intVal2 = branch->nodes.size();
                imageWriter.write((char*)&intVal2, sizeof(int));
                for (int j=0; j < branch->nodes.size(); ++j) {
                    intVal2 = branch->nodes.get(j);
                    imageWriter.write((char*)&intVal2, sizeof(int));
                }
            }

            // Skeleton slices
            for (int i=0; i < skeleton->getBranchesSize(); ++i) {
                Branch* branch = skeleton->getBranch(i);

                // Slices coord
                intVal = branch->slices.size();

                SkeletonSlice* skelSlice = branch->slices.getFirst();
                int w = skelSlice->exam2d->getWidth();
                int h = skelSlice->exam2d->getHeight();
                float resxy = skelSlice->resolution.x;
                float resz = skelSlice->resolution.y;

                imageWriter.write((char*)&intVal, sizeof(int));
                imageWriter.write((char*)&w, sizeof(int));
                imageWriter.write((char*)&h, sizeof(int));
                imageWriter.write((char*)&resxy, sizeof(float));
                imageWriter.write((char*)&resz, sizeof(float));

                /*
                for (int j=0; j < intVal; ++j) {
                    SkeletonSlice* skelSlice = branch->slices.get(j);
                    int size = skelSlice->exam2d->getWidth() * skelSlice->exam2d->getHeight();
                    int sizeCoord = size * 3;

                    // Slices coordonnée
                    int* intPtrVal = skelSlice->exam2d->GetTabCoord()->getDataRef();
                    imageWriter.write((char*)intPtrVal, sizeCoord * sizeof(int));

                    // Slices image
                    float* floatPtrVal = skelSlice->exam2d->GetTabValue()->getDataRef();
                    imageWriter.write((char*)floatPtrVal, size * sizeof(float));

                    // Slices mask
                    char* charPtrVal = skelSlice->exam2d->GetTabmask()->getDataRef();
                    imageWriter.write((char*)charPtrVal, size * sizeof(char));
                }
                */
            }
        }

        // INFORMATIONS

        if (options.get(3)) {
            Information* infos = examen->getParams().getContentInformations();
            intVal = infos->getSize();
            imageWriter.write((char*)&intVal, sizeof(int));
            int length;
            for (int i=0; i<intVal; ++i) {
                string title = infos->getTitle(i);
                length = title.size() + 1;
                imageWriter.write((char*)&length, sizeof(int));
                imageWriter.write((char*)title.c_str(), length * sizeof(char));
                string description = infos->getDescription(i);
                length = description.size() + 1;
                imageWriter.write((char*)&length, sizeof(int));
                imageWriter.write((char*)description.c_str(), length * sizeof(char));
            }

            // SLOPE, INTERCEPT
            // TODO: effectuer l'écriture de ces deux données en entête

            intVal = examen->getParams().getGrayTranslationFunction().getSlope();
            imageWriter.write((char*)&intVal, sizeof(int));
            intVal = examen->getParams().getGrayTranslationFunction().getIntercept();
            imageWriter.write((char*)&intVal, sizeof(int));
        }

        imageWriter.close();
        return true;
    }
    return false;
}
