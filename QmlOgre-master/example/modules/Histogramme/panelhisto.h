#ifndef FENETRE_H
#define FENETRE_H

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Panel contenant l'histogramme
 */

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <string>
#include <vector>
#include "histogramme.h"
#include <qimage.h>

class PanelHisto : public QWidget
{
    Q_OBJECT
public:
    PanelHisto(char* pFile);
    Histogramme * h;
    void afficheNdG(QPainter * painter,int size);
    void afficheRed(QPainter * painter,int size);
    void afficheGreen(QPainter * painter,int size);
    void afficheBlue(QPainter * painter,int size);

    /* 0: ndg, 1: red, 2:green, 3: blue (RGB)*/
    int couleur;
    std::vector<std::string> color;
    const QImage m_oImg;
    void setImage(char *pFile);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // FENETRE_H
