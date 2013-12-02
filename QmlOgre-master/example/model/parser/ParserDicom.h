#ifndef PARSER_DICOM_H
#define PARSER_DICOM_H

#include "../model/Information.h"
#include "Parser.h"

#include <dirent.h>
#include <list>

class ExamenParams;

class Information;
#include "Image.hpp"
class DicomPreview;





class ParserDicom
        : public Parser
{
public:
    ParserDicom();


public:
    Examen* loadFile(std::string dirName);
    bool saveFile(std::string, Examen*, MiList<bool>);

    bool isValidFile(std::string filename);

    MiList<Examen*>* loadExamen(DicomDir dir);
    MiList<Examen*>* loadExamen(std::string dir_name);
    //get all the subDir of dir_name that contain a Dicom File (to get Exam)
    MiList<std::string> getSubDir(std::string dir_name);

    MiList<std::string> getInformations(std::string filename);
    ExamenParams * getInfos(DIR* dir, std::string dirName);
    DicomPreview * getMinimalInfo(std::string dirName);

 //   Information * getInfos(std::string dirName, std::string fileName);

private:
    int nbFiles(DIR* dir);

    struct dirent* getOneFile(DIR* dir);

};


class DicomPreview
{
    public :
        DicomPreview(Information * infos, Image<float> * img);
        ~DicomPreview();
        Image<float> * getPreview();
        Information * getInfos();


    private :
        Information * minimalInfos;
        Image<float> * preview;
};



#endif // PARSER_DICOM_H
