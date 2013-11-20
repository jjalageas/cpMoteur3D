#include "color.h"



void Color::setColor(int R, int G, int B, int A){
    this->R = R;
    this->G = G;
    this->B = B;
    this->A = A;
}

std::list<int> Color::getColor(){
    std::list<int> color;
    color.push_back(this->R.copy());
    color.push_back(this->G.copy());
    color.push_back(this->B.copy());
    color.push_back(this->A.copy());
    return color;
}
