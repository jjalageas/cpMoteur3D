#ifndef GENERAL_H
#define GENERAL_H

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Widget contenant les panels histogramme et boutons
 */

#include "panelButtons.h"
#include "panelhisto.h"
#include <QHBoxLayout>
#include <QWidget>

class WidgetHisto: public QWidget
{
    Q_OBJECT

    PanelHisto *ph;
    PanelButtons *pb;
    QVBoxLayout *layout;

public:
    WidgetHisto(char *pFile);

protected:
    void paintEvent(QPaintEvent *);
};

#endif // GENERAL_H
