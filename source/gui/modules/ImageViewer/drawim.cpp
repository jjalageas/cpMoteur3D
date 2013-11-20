#include "drawim.h"


DrawIm::DrawIm(QWidget* parent)
    : QWidget(parent)
{
    if (QFile::exists("lena.jpg"))
    {
        qimg = QImage("lena.jpg");
        qimg = qimg.convertToFormat(QImage::Format_Indexed8, Qt::MonoOnly);
        setMinimumSize(qimg.width(),qimg.height());
        qimgo = qimg;

    }
    else
        cout << "Image not found" << endl;
}

void DrawIm::updateImage(QColorRampEditor* colorramp)
{
    //QVector<QPair<qreal, QColor> > ramp = colorramp->getRamp();
    QVector<QRgb> ctable = colorramp->getColorTable();
    qimg.setColorTable(ctable);
    update();
}

void DrawIm::onRampChanged()
{
    updateImage(reinterpret_cast<QColorRampEditor*>(sender()));
}

void DrawIm::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.fillRect(rect(), QColor(0, 0, 0));
    p.drawImage(0,0,qimg);
}

QImage* DrawIm::getImage()
{
    return &qimg;
}

QImage* DrawIm::getImageOriginal()
{
    return &qimgo;
}

void DrawIm::setImage(QImage i)
{
    qimg = i;
}

void DrawIm::getImageOriginal(QImage i)
{
    qimgo = i;
}
