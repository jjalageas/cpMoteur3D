#ifndef IMAGEVIEWER_H
#define IMAGEVIEWER_H

#include <QWidget>
#include <qcolorrampeditor.h>
#include "drawim.h"
#include "graduationview.h"

class ImageViewer : public QWidget
{
    Q_OBJECT

private :
    static const int SIZE_PAL = 60;
    QColorRampEditor* rampEditor;
    GraduationView *graduation;
    QHBoxLayout* lay;

public:
    ImageViewer(QWidget *parent = 0);
    void resizeEvent(QResizeEvent *event);
    ~ImageViewer();


};


#endif // IMAGEVIEWER_H
