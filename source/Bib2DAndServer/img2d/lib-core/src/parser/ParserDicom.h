#ifndef PARSER_DICOM_H
#define PARSER_DICOM_H

#include "Parser.h"

#include <dirent.h>
#include <list>

class ExamenParams;


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

    MiList<std::string> getInformations(std::string filename);


private:
    int nbFiles(DIR* dir);
    ExamenParams* getInfos(DIR* dir, std::string dirName);
    struct dirent* getOneFile(DIR* dir);

};

#endif // PARSER_DICOM_H
