#ifndef PANELHISTO_H
#define PANELHISTO_H

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Panel contenant l'histogramme
 */

#include <QVBoxLayout>
#include <QPushButton>
#include <QCheckBox>
#include <QPainter>
#include <QWidget>
#include <vector>
#include <string>
#include <qimage.h>
#include <iostream>

#include "histogram.hpp"

class PanelHisto : public QWidget
{
    Q_OBJECT

public:
    PanelHisto(QString pFile);
    Histogram * h;
    void afficheNdG(QPainter * painter,int size);
    void afficheRed(QPainter * painter,int size);
    void afficheGreen(QPainter * painter,int size);
    void afficheBlue(QPainter * painter,int size);

    /* 0: ndg, 1: red, 2:green, 3: blue (RGB)*/
    std::vector<std::string> color;
    const QImage m_oImg;
    void setImage(char *pFile);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // PANELHISTO_H
