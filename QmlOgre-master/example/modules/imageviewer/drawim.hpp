#ifndef DRAWIM_H
#define DRAWIM_H

#include <QWidget>
#include <QFile>
#include <qcolorrampeditor.h>

class DrawIm : public QWidget
{
    Q_OBJECT

public:
    DrawIm(QWidget* parent=0);
    void updateImage(QColorRampEditor* colorramp);
    QImage* getImage();
    QImage* getImageOriginal();
    void setImage(QImage i);
    void getImageOriginal(QImage i);

public slots:
    void onRampChanged();

protected:
    void paintEvent(QPaintEvent *);

private:
    QImage qimg;
    QImage qimgo;
};
#endif // DRAWIM_H
