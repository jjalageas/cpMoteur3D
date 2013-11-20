#ifndef PARSER_MANAGER_H
#define PARSER_MANAGER_H

#include <Struct.hpp>

class Examen;
class Parser;
class ParserDicom;


class ParserManager
{
public:
    ParserManager();
    ~ParserManager();


public:
    /**
      * Special functions for openning Dicom
      */
    void analyzeDicomDir(DicomDir*, ParserDicom*);
    MiList<DicomDir*>& getDicomsInfos(std::string directory);
    int loadDicoms(MiList<std::string>& ilenames);

    /**
      * Global functions for openning and saving mi3D / bmi3D / csv formats
      */
    bool loadFile(std::string filename, /*DataManager *dataManager, */std::string ext);
    bool saveFile(std::string filename, Examen* examen, MiList<bool> options, std::string ext);

    /**
      * Special function for load/save data in temporary file
      */
    bool loadData(Examen* examen);
    bool saveData(Examen* examen);


private:
    Parser* searchParser(std::string filename, std::string extension);


private:
    MiList<Parser*> _parsers;
    std::string _tmpDataFilename;

};

#endif // PARSER_MANAGER_H
