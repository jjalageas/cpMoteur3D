#include <QTabWidget>

#include "widgetHisto.hpp"

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Widget contenant les panels histogramme et boutons
 */

WidgetHisto::WidgetHisto(QString pFile, QWidget *parent)
    : QWidget(parent)
{
    ph = new PanelHisto(pFile);
    pb = new PanelButtons(this, ph);
    layout = new QVBoxLayout();
}

void WidgetHisto::paintEvent(QPaintEvent *)
{
    layout->addWidget(ph);
    layout->addWidget(pb);

    setLayout(layout);
}
