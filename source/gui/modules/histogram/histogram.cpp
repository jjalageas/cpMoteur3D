#include <cstring>
#include <QPainter>
#include <qimage.h>
#include <iostream>

#include "histogram.hpp"

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 */

using namespace std;

Histogram::Histogram(const QImage image)
{
    for(int j = 0; j < 4; j++)
        for (int i = 0; i < 256; i++)
            tab[i][j] = 0;

    int iX = 0;
    int iY = 0;

    int width = image.width();
    int height = image.height();

    // variable to hold the graylevel value
    int iGraylevel;

    while (iY < height)
    {
        while (iX < width)
        {
            // return a pointer to the pixel data at "y" scan line
            uint *p = (uint *)image.scanLine(iY) + iX;
            // calculate graylevel for each pixel

            iGraylevel =(int)(0.299 * qRed(*p) + 0.587 * qGreen(*p)  + 0.114 * qBlue(*p) + 0.5);
            tab[iGraylevel][0]++;
            tab[qGreen(*p)][2]++;
            tab[qBlue(*p)][3]++;
            tab[qRed(*p)][1]++;
            iX++;
        }
        iX = 0;
        iY++;
    }
}

int Histogram::valeurMax()
{
    int heightMax = 1;
    for(int j=0;j<4;++j){
        for( int i=0; i<255; ++i ){
            if( this->tab[i][j]>heightMax ){
                heightMax = this->tab[i][j];
            }
        }
    }
    return heightMax;
}
