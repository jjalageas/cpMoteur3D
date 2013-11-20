#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include <QPainter>

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 */

class Histogram
{

public:
    Histogram(const QImage);
    int valeurMax();

    float tab[256][4];
};

#endif // HISTOGRAM_H
