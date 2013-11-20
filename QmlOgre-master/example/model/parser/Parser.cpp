#include <Parser.h>


Parser::Parser(std::string extension)
    : _extension(extension)
{}

Parser::~Parser()
{}

std::string
Parser::getExtension() const
{
    return _extension;
}
