#ifndef PARSER_H
#define PARSER_H

#include <Struct.hpp>

class Examen;


class Parser
{
public:
    Parser(std::string extension);
    virtual ~Parser();

    virtual Examen* loadFile(std::string filename) = 0;
    virtual bool saveFile(std::string filename, Examen* examen, MiList<bool> options) = 0;

    std::string getExtension() const;


private:
    std::string _extension;

};

#endif // PARSER_H
