#include "panelhisto.h"
#include <QPolygon>
#include <QLinearGradient>
#include <stdio.h>

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Panel contenant l'histogramme
 */

PanelHisto::PanelHisto(char*pFile):m_oImg(pFile)
{
    QWidget();
    couleur = -1;

    // read original image as input
    h = new Histogramme(m_oImg);

}

void PanelHisto::paintEvent(QPaintEvent *){

    int VAL =255;

    QPainter painter(this);
    painter.setWindow(-10,-10,300,300);

    QLineF axe_horiz(0,VAL,VAL,VAL);
    QLineF axe_verti(0, 0, 0, VAL);

    painter.setFont(QFont("Calibri", 5));
    painter.drawText(-8,VAL+6,"0");
    painter.drawText(VAL-50,VAL+10,"Valeur Moyenne du pixel");
    painter.drawText(0,-2,"Nombre de pixels");

    painter.save();
    painter.drawLine(axe_horiz);
    //Absysse
    for(int i=0; i<26; i++){
        painter.drawLine(i*10, VAL-2, i*10, VAL+1);
    }

    //Ordonnée
    for(int i=0; i<26; i++){
        painter.drawLine(-1,i*10,2, i*10);
    }
    painter.restore();

    painter.save();
    painter.drawLine(axe_verti);
    painter.restore();

    if(std::find(color.begin(), color.end(), "NDG") != color.end()){
        painter.setPen( Qt::black );
        afficheNdG(&painter,VAL);
    }

    if(std::find(color.begin(), color.end(), "red") != color.end()){
        painter.setPen( Qt::red );
        afficheRed(&painter,VAL) ;
    }
    if(std::find(color.begin(), color.end(), "green") != color.end()){
        painter.setPen( Qt::green );
        afficheGreen(&painter,VAL) ;
    }
    if(std::find(color.begin(), color.end(), "blue") != color.end()){
        painter.setPen( Qt::blue );
        afficheBlue(&painter,VAL);
    }

    painter.end();
}

void PanelHisto::afficheNdG(QPainter * painter,int size){

    int heightMax = h->valeurMax();

    QLinearGradient linearGradient(0, 0, 0, 255);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(1.0, "#747C7B");
    painter->setBrush(linearGradient);
    QPolygon polygonCourbe;
    polygonCourbe << QPoint(0,255);
    for (int i = 0; i < 256; i++)
    {
        polygonCourbe << QPoint(0.5+i,size-(uint)((float)h->tab[i][0] * size / heightMax + 0.5));

    }
    polygonCourbe << QPoint(255, 255);
    painter->drawPolygon(polygonCourbe);
}

void PanelHisto::afficheRed(QPainter * painter,int size){
    int heightMax = h->valeurMax();
    QLinearGradient linearGradient(0, 0, 0, 255);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(1.0, "#C70208");
    painter->setBrush(linearGradient);
    painter->setOpacity(0.8);
    QPolygon polygonCourbe;

    polygonCourbe << QPoint(0,255);
    for (int i = 0; i < 256; i++)
    {
        polygonCourbe << QPoint(0.5+i,size-(uint)((float)h->tab[i][1] * size / heightMax + 0.5));
    }
    polygonCourbe << QPoint(255, 255);

    painter->drawPolygon(polygonCourbe);
}

void PanelHisto::afficheGreen(QPainter * painter,int size){
    int heightMax = h->valeurMax();
    QLinearGradient linearGradient(0, 0, 0, 255);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(1.0, "#077512");
    painter->setBrush(linearGradient);
    painter->setOpacity(0.6);
    QPolygon polygonCourbe;

    polygonCourbe << QPoint(0,255);
    for (int i = 0; i < 256; i++)
    {
        polygonCourbe << QPoint(0.5+i,size-(uint)((float)h->tab[i][2] * size / heightMax + 0.5));

    }
    polygonCourbe << QPoint(255, 255);
    painter->drawPolygon(polygonCourbe);
}

void PanelHisto::afficheBlue(QPainter * painter,int size){

    int heightMax = h->valeurMax();

    QLinearGradient linearGradient(0, 0, 0, 255);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(1.0, "#2A58D5");
    painter->setBrush(linearGradient);
    painter->setOpacity(0.4);
    QPolygon polygonCourbe;

    polygonCourbe << QPoint(0,255);
    for (int i = 0; i < 256; i++)
    {
        polygonCourbe << QPoint(0.5+i,size-(uint)((float)h->tab[i][3] * size / heightMax + 0.5));

    }
    polygonCourbe << QPoint(255, 255);
    painter->drawPolygon(polygonCourbe);
}
