#include "widgethisto.h"
#include <QTabWidget>

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Widget contenant les panels histogramme et boutons
 */

WidgetHisto::WidgetHisto(char*pFile)
{
   QWidget();

   ph = new PanelHisto(pFile);
   pb = new PanelButtons(this, ph);
   layout = new QVBoxLayout();

}

void WidgetHisto::paintEvent(QPaintEvent *){

    layout->addWidget(ph);
    layout->addWidget(pb);

    setLayout(layout);
}
