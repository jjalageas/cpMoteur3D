#include <ParserDicom.h>
#include <Examen.h>
#include <ExamenParams.h>
#include <Image3d.hpp>
#include <GrayValue.h>
#include <Information.h>

#include <dcdeftag.h>
#include <didocu.h>
#include <dimo2img.h>

#undef PATH_SEPARATOR
#if defined(WIN32) || defined(_WIN32)
#define PATH_SEPARATOR "\\"
#else
#define PATH_SEPARATOR "/"
#endif

using namespace std;


ParserDicom::ParserDicom()
    : Parser(string("dcm"))
{}

/*
ParserDicom::~ParserDicom()
{}
*/

bool
ParserDicom::isValidFile(string filename)
{
    DcmFileFormat dcm;
    OFCondition cond = dcm.loadFile(filename.c_str());
    return cond.good();
}

bool
ParserDicom::saveFile(string, Examen*, MiList<bool>)
{
    cout << "Not implemented yet" << endl;
    return false;
}

MiList<Examen*>*
ParserDicom::loadExamen(DicomDir dir)
{
    MiList<Examen*>* exams = new MiList<Examen*>();
    for (int i=0; i<dir.subdir.size(); ++i) {
        exams->add(loadFile(dir.subdir.get(i)->dirName));
    }
    return exams;
}

int
ParserDicom::nbFiles(DIR* dir)
{
    int nb = 0;
    struct dirent* file;
    rewinddir(dir);
    while ((file = readdir(dir)) != NULL)
        nb++;
    return nb > 0 ? nb-2 : 0;
}

Examen*
ParserDicom::loadFile(string dirName)
{
    // Open directory
    DIR* dir = opendir(dirName.c_str());
    if (dir == NULL) {
        return NULL;
    }

    // Get examen informations
    ExamenParams* params = getInfos(dir, dirName);
    if (params == NULL) {
        return NULL;
    }

    // Create struct examen
    Volume* img = new Volume(params->width, params->height, params->depth);
    Examen* exam = new Examen(img, params);

    // Read data
    int index = 0;
    struct dirent* file;
    rewinddir(dir);
    string pathDirectory = dirName + PATH_SEPARATOR;
    int tabSize = params->width * params->height;
    float tab[tabSize];
    while ((file = readdir(dir)) != NULL) {
        if (strcmp(file->d_name, ".") != 0 &&
                strcmp(file->d_name, "..") != 0) {
            string fullpath = pathDirectory + file->d_name;
            DcmFileFormat dcm;
            OFCondition cond = dcm.loadFile(fullpath.c_str());
            if (cond.bad()) {
                delete img;
                delete params;
                return NULL;
            }
            DiDocument* didoc = new DiDocument(fullpath.c_str());
            DiMono2Image* dimg = new DiMono2Image(didoc, EIS_Normal);
            OFString s;
            dcm.getDataset()->findAndGetOFString(DCM_BitsStored, s);
            int bitsStored = atoi(s.c_str());

            short* slice = (short*) dimg->getOutputData(0, bitsStored, 0);
            for(int i=0; i<tabSize; ++i) {
                tab[i] = (float) slice[i];
            }
            img->setSlice(tab, index++);
            delete dimg;
            delete didoc;
        }
    }
    closedir(dir);
    return exam;
}

struct dirent*
        ParserDicom::getOneFile(DIR* dir)
{
    struct dirent* file;
    do {
        file = readdir(dir);
    } while ((strcmp(file->d_name, ".") == 0 ||
              strcmp(file->d_name, "..") == 0) &&
             file != NULL);
    return file;
}

MiList<std::string> ParserDicom::getInformations(std::string) {
    eassert(false); // not implemented... folder ?
    return MiList<std::string>();
}


ExamenParams*
ParserDicom::getInfos(DIR* dir, string dirName)
{
    struct dirent* file = getOneFile(dir);
    if (file == NULL) {
        return NULL;
    }
    string fullpath = dirName + PATH_SEPARATOR + file->d_name;
    DcmFileFormat dcm;
    OFCondition cond = dcm.loadFile(fullpath.c_str());
    if (cond.bad()) {
        return NULL;
    }

    Information* generalInfos = new Information();
    OFString s;
    dcm.getDataset()->findAndGetOFString(DCM_PatientName, s);
    generalInfos->addInformation("Patient name", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_PatientID, s);
    generalInfos->addInformation("Patient ID", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_PatientBirthDate, s);
    generalInfos->addInformation("Patient birthday", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_PatientAge, s);
    generalInfos->addInformation("Patient age", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_PatientSex, s);
    generalInfos->addInformation("Patient sex", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_PatientSize, s);
    generalInfos->addInformation("Patient size", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_PatientWeight, s);
    generalInfos->addInformation("Patient weight", s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_ImagePositionPatient, s);
    generalInfos->addInformation("Image position patient", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_ImageOrientationPatient, s);
    generalInfos->addInformation("Image orientation patient", s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_StudyID, s);
    generalInfos->addInformation("Study data", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_StudyDate, s);
    generalInfos->addInformation("Study date", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_StudyTime, s);
    generalInfos->addInformation("Study time", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_StudyDescription, s);
    generalInfos->addInformation("Study description", s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_BitsAllocated, s);
    generalInfos->addInformation("Bits allocated", s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_BitsStored, s);
    generalInfos->addInformation("Bits stored", s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_HighBit, s);
    generalInfos->addInformation("High bit", s.c_str());

    generalInfos->addInformation("Intercept", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_RescaleIntercept, s);
    int intercept = atoi(s.c_str());
    generalInfos->addInformation("Slope", s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_RescaleSlope, s);

    int slope = atoi(s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_WindowCenter, s);
    generalInfos->addInformation("Window center", s.c_str());
    int Wcenter=atoi(s.c_str());
    dcm.getDataset()->findAndGetOFString(DCM_WindowWidth, s);
    generalInfos->addInformation("Window width", s.c_str());
    int Wwidth=atoi(s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_SliceThickness, s);
    generalInfos->addInformation("Slice thickness", s.c_str());
    float Sthickness = atof(s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_WindowCenterWidthExplanation, s);
    generalInfos->addInformation("WindowCenterWidthExplanation", s.c_str());

    dcm.getDataset()->findAndGetOFString(DCM_Manufacturer, s);
    generalInfos->addInformation("Manufacturer", s.c_str());

    //---------------------------------------------
    // Affectation des parametres de l'examen
    //---------------------------------------------
    GrayTranslationFunction gtf(slope, intercept);
    ExamenParams* params = new ExamenParams(gtf, fullpath, generalInfos);

    params->getGrayViewWindow().setLuminosity(Wcenter);
    params->getGrayViewWindow().setContrast(Wwidth);
    //params->getGrayViewWindow().setMin(HundsfieldValue::min()); // Must choose !
    //params->getGrayViewWindow().setMax(HundsfieldValue::max());
    //params->setParametersSI(Sthickness);

    //---------------------------------------------
    // Examen size informations
    //---------------------------------------------
    DiDocument* didoc = new DiDocument(fullpath.c_str());
    DiMono2Image* dimg = new DiMono2Image(didoc, EIS_Normal);

    params->width = dimg->getColumns();
    params->height = dimg->getRows();
    params->depth = nbFiles(dir);

    params->resolutionX = dimg->getPixelWidth();;
    params->resolutionY = dimg->getPixelHeight();;
    params->resolutionZ = Sthickness; // check

    ostringstream sNbSlice, sSize, sResX, sResY;
    sResX << params->resolutionX;
    sResY << params->resolutionY;
    sNbSlice << params->depth + 1;
    sSize << params->width << " " << params->height;

    generalInfos->addInformation("Slice number", sNbSlice.str());
    generalInfos->addInformation("Scan resolution (x, y)", sSize.str());
    generalInfos->addInformation("Pixel resolution X", sResX.str());
    generalInfos->addInformation("Pixel resolution Y", sResY.str());

    delete dimg;
    delete didoc;

    return params;
}
