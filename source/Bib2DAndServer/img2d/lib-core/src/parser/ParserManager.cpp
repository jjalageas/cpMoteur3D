#include <ParserManager.h>
#include <Examen.h>
#include <Image3d.hpp>
#include <Parser.h>
#include <ParserDicom.h>
#include <ParserMi3DBinary.h>

#include <cstdio>
#include <dirent.h>
#include <fstream>

using namespace std;


ParserManager::ParserManager()
    : _tmpDataFilename("data.tmp")
{
    _parsers.add(new ParserDicom());
    _parsers.add(new ParserMi3DBinary());
}

ParserManager::~ParserManager()
{
    for (int i=0; i<_parsers.size(); ++i) {
        delete _parsers.get(i);
    }
    _parsers.empty();
    remove(_tmpDataFilename.c_str());
}

void
ParserManager::analyzeDicomDir(DicomDir* dir, ParserDicom* parser)
{
    // set dirname from path
    size_t slashPos = dir->path.find_last_of("/");
    dir->dirName = dir->path.substr(slashPos+1, dir->path.size()-slashPos-1);

    DIR* dicomsDir = opendir(dir->path.c_str());
    if (dicomsDir) {
        for (;;) {
            struct dirent* dicomFile = readdir(dicomsDir);
            if (!dicomFile) {
                break;
            }
            if (!strcmp(dicomFile->d_name, ".") || !strcmp(dicomFile->d_name, "..")) {
                continue;
            }
            if (dicomFile->d_type == DT_DIR) {
                stringstream sDir;
                sDir << dir->path << "/" << dicomFile->d_name;
                DicomDir* subDir = new DicomDir();
                subDir->path = sDir.str();
                dir->subdir.add(subDir);
                delete subDir;
            }
            if (dicomFile->d_type == DT_REG) {
                stringstream sFile;
                sFile << dir->path << "/" << dicomFile->d_name;
                if (dir->nbSlice == 0) {
                    if (parser->isValidFile(sFile.str())) {
                        MiList<string> infos = parser->getInformations(sFile.str());
                        dir->patientName = infos.get(0);
                        dir->patientSex = infos.get(1);
                        dir->studyDate= infos.get(2);
                    }
                }
                dir->nbSlice++;
            }
        }
        for (int i=0; i<dir->subdir.size(); ++i) {
            analyzeDicomDir(dir->subdir.get(i), parser);
        }
    }
}

MiList<DicomDir*>&
ParserManager::getDicomsInfos(string directory)
{
    MiList<DicomDir*>* infos = new MiList<DicomDir*>();
    ParserDicom* parser = (ParserDicom*)searchParser(string("filename.dcm"),
                                                     string("dcm"));
    if (parser != NULL) {
        DIR* dicomsDir = opendir(directory.c_str());
        if (dicomsDir) {
            DicomDir* dir = new DicomDir();
            dir->path = directory;
            infos->add(dir);
            closedir(dicomsDir);
            analyzeDicomDir(dir, parser);
        }
    }
    return *infos;
}

/*int
ParserManager::loadDicoms(MiList<string>& filesname)
{
    int flag = 0;
    Parser* parser = searchParser(string("filename.dcm"), string("dcm"));
    if (parser != NULL) {
        Examen* examen = new Examen(); // mem leak !
        int oldSize = examen->getImageRef().getDepth();
        for (int i=0; i<filesname.size(); ++i) {
            parser->loadFile(filesname.get(i), examen);
            int newSize = examen->getImageRef().getDepth();
            if (newSize > oldSize) {
                flag++;
                oldSize = newSize;
            }
        }
    }
    return flag;
}*/

/*bool
ParserManager::loadFile(string filename, DataManager *dataManager, string ext)
{
    Examen* examen = new Examen(); // mem leak !
    Parser* parser = searchParser(filename, ext);

    if (parser != NULL) {
        parser->loadFile(filename, examen);
        return examen->getImageRef().getWidth() != 0;
    }
    return false;
}*/

bool
ParserManager::saveFile(string filename, Examen* examen, MiList<bool> options, string ext)
{
    Parser* parser = searchParser(filename, ext);
    if (parser != NULL) {
        cout << "search parser ok" << endl;
        return parser->saveFile(filename, examen, options);
    }
    return false;
}

bool
ParserManager::loadData(Examen* examen)
{
    ifstream imageReader;
    imageReader.open(_tmpDataFilename.c_str(), ios::in | ios::binary);
    if (!imageReader) {
        return false;
    }
    int nSlice;
    imageReader.read((char *)&nSlice, sizeof(int));
    if (nSlice != examen->getImageRef().getDepth()) {
        return false;
    }
    for (int c=0; c<nSlice; ++c) {
        Image<float>* slice = examen->getImage()->getSlice(c, CORONAL);
        int width, height;
        imageReader.read((char *)&width, sizeof(int));
        imageReader.read((char *)&height, sizeof(int));
        if (width != slice->getWidth() || height != slice->getHeight()) {
            return false;
        }
        float* src = slice->getData();
        imageReader.read((char *)src, sizeof(float) * width * height);
        // strange...
        examen->getImage()->putSlice(*slice, c, CORONAL);
        delete slice;
    }
    imageReader.close();
    return true;
}

bool
ParserManager::saveData(Examen* examen)
{
    ofstream imageWriter;
    imageWriter.open(_tmpDataFilename.c_str(), ios::out | ios::binary);
    if (!imageWriter) {
        return false;
    }
    int nbSlice = examen->getImageRef().getDepth();
    imageWriter.write((char *)&nbSlice, sizeof(int));
    for (int c=0; c<nbSlice; ++c) {
        Image<float>* image = examen->getImage()->getSlice(c, CORONAL);
        // size
        int width = image->getWidth();
        imageWriter.write((char *)&width, sizeof(int));
        int height = image->getHeight();
        imageWriter.write((char *)&height, sizeof(int));
        // image
        float* src = image->getData();
        imageWriter.write((char *)src, sizeof(float) * width * height);
    }
    imageWriter.close();
    return true;
}

Parser*
ParserManager::searchParser(string filename, string extension)
{
    string fileExtension(filename, filename.find_last_of('.')+1);
    if (fileExtension.size() == extension.size() &&
            fileExtension.compare(extension) == 0) {
        for (int i=0; i<_parsers.size(); ++i) {
            string ext = _parsers.get(i)->getExtension();
            cout << "extension parser[" << i << "]=" << ext
                 << "   extension file: " << extension << endl;
            if (ext.size() == extension.size() && ext.compare(extension) == 0) {
                return _parsers.get(i);
            }
        }
    }
    else {
        cout << "[ParserManager::searchParser] Invalid file extension and parser extension : "
             << fileExtension << " / " << extension << endl;
    }
    return NULL;
}
