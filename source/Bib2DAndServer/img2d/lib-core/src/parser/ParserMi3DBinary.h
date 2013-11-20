#ifndef PARSER_MI_3D_BINARY_H
#define PARSER_MI_3D_BINARY_H

#include "Parser.h"


class ParserMi3DBinary
        : public Parser
{
public:
    ParserMi3DBinary();


public:
    Examen* loadFile(std::string filename);
    bool saveFile(std::string filename, Examen* examen, MiList<bool> options);

};

#endif // PARSER_MI_3D_BINARY_H
