#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <qcolorrampeditor.h>

#include "drawim.hpp"
#include "graduationview.hpp"

class ImageViewer : public QWidget
{
    Q_OBJECT

public:
    ImageViewer(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *);
    ~ImageViewer();

private :
    static const int SIZE_PAL = 60;
    QColorRampEditor* rampEditor;
    GraduationView *graduation;
    QHBoxLayout* lay;
};

#endif // IMAGEVIEWER_H
