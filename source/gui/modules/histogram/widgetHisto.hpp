#ifndef WIDGETHISTO_H
#define WIDGETHISTO_H

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Widget contenant les panels histogramme et boutons
 */

#include <QHBoxLayout>
#include <QWidget>

#include "panelButtons.hpp"
#include "panelHisto.hpp"

class WidgetHisto: public QWidget
{
    Q_OBJECT

public:
    WidgetHisto(QString pFile, QWidget *parent=0);

    PanelHisto *ph;
    PanelButtons *pb;
    QVBoxLayout *layout;

protected:
    void paintEvent(QPaintEvent *);
};

#endif // WIDGETHISTO_H
