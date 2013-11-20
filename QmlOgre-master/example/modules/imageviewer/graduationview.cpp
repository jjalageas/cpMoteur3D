#include "graduationview.hpp"

GraduationView::GraduationView(QWidget *parent)
    : QWidget(parent)
{
    dimg = new DrawIm();
}


void GraduationView::drawMillimeter(QPainter *painter)
{
    int heightM =  dimg->getImage()->height()+ADJUSTEMENT;
    int widthM = dimg->getImage()->width()+ADJUSTEMENT;

    painter->drawLine(MARGIN,heightM-MARGIN,MARGIN,MARGIN);
    for(int i = MARGIN; i<=heightM-MARGIN; i+=MILI)
        painter->drawLine(MARGIN-(SIZE_MILI/2), heightM-i, MARGIN+(SIZE_MILI/2), heightM-i );

    painter->drawLine(widthM-MARGIN,heightM-MARGIN,MARGIN,heightM-MARGIN);
    for(int i = MARGIN; i<=widthM-MARGIN; i+=MILI)
        painter->drawLine(i, heightM-(MARGIN-(SIZE_MILI/2)), i ,  heightM-(MARGIN+(SIZE_MILI/2)));

}

void GraduationView::drawNumber(QPainter *painter)
{
    int heightM =  dimg->getImage()->height()+ADJUSTEMENT;
    int widthM = dimg->getImage()->width()+ADJUSTEMENT;

    int PAS = MILI*NB;

    QFont font;
    font.setPixelSize(6);
    painter->setFont(font);
    for(int i = 0; i <=heightM-(MARGIN*2); i+=PAS){
        painter->drawText(MARGIN_TXT, heightM-MARGIN-i, QString::number(i/MILI));
    }

    for(int i = 0; i <=widthM-(MARGIN*2); i+=PAS){
        painter->drawText(i+MARGIN, heightM-MARGIN_TXT, QString::number(i/MILI));
    }
}

void GraduationView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    dimg->setImage(dimg->getImageOriginal()->scaled(this->width()-ADJUSTEMENT,this->height()-ADJUSTEMENT));
    dimg->updateImage(rampEditor);
    painter.drawImage(MARGIN+1,MARGIN,*dimg->getImage());
    drawMillimeter(&painter);
    drawNumber(&painter);
}

GraduationView::~GraduationView()
{
}

DrawIm *GraduationView::getDimg()
{
    return dimg;
}

QColorRampEditor *GraduationView::getRampEditor()
{
    return rampEditor;
}

void GraduationView::setRampEditor(QColorRampEditor* r)
{
    rampEditor = r;
    QObject::connect(rampEditor, SIGNAL(rampChanged()), dimg, SLOT(onRampChanged()));
}
