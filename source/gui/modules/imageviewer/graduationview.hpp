#ifndef GRADUATIONVIEW_H
#define GRADUATIONVIEW_H

#include <QFrame>
#include <QPainter>

#include "drawim.hpp"

class GraduationView: public QWidget
{
    Q_OBJECT

public:
    GraduationView(QWidget *parent = 0);
    ~GraduationView();

    void paintEvent(QPaintEvent *);
    void drawMillimeter(QPainter *painter);
    void setRampEditor(QColorRampEditor* r);
    void drawNumber(QPainter *painter);
    DrawIm *getDimg();
    QColorRampEditor *getRampEditor();

    static const int MILI = 5;
    static const int SIZE_MILI = 5;
    static const int MARGIN = 25;
    static const int NB = 10;
    static const int MARGIN_TXT = 10;
    static const int ADJUSTEMENT = 50;

private:
    DrawIm* dimg;
    QColorRampEditor* rampEditor;
};

#endif // GRADUATIONVIEW_H
