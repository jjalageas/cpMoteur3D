#ifndef HISTOGRAMME_H
#define HISTOGRAMME_H

#include <QPainter>

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 */

class Histogramme{

public:
    Histogramme(const QImage);
    int valeurMax();

    float tab[256][4];
};



#endif // HISTOGRAMME_H
