#include "zone.hpp"

int Zone::compteur = 0;

Zone::Zone() :
    id(++compteur)
{
}

void Zone::setName(std::string &name){
    this->name = name;
}

std::string Zone::getName(){
    return this->name;
}

void Zone::setColor(QColor &color){
    this->color = color;
}

QColor Zone::getColor(){
    return this->color;
}

int Zone::getId(){
    return this->id;
}
