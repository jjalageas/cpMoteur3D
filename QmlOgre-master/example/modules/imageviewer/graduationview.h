#ifndef GRADUATIONVIEW_H
#define GRADUATIONVIEW_H

#include <QFrame>
#include <QPainter>
#include "drawim.h"

class GraduationView: public QWidget
{
    Q_OBJECT
private:
    DrawIm* dimg;
    QColorRampEditor* rampEditor;
public:
    static const int MILI = 5;
    static const int SIZE_MILI = 5;
    static const int MARGIN = 25;
    static const int NB = 10;
    static const int MARGIN_TXT = 10;
    static const int ADJUSTEMENT = 50;

    void paintEvent(QPaintEvent *event);
    void drawMillimeter(QPainter *painter);
    void drawNumber(QPainter *painter);
    GraduationView(QWidget *parent = 0);
    ~GraduationView();

    DrawIm *getDimg();
    QColorRampEditor *getRampEditor();
    void setRampEditor(QColorRampEditor* r);

};

#endif // GRADUATIONVIEW_H
