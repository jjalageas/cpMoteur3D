#include <QDebug>

#include "imageviewer.hpp"

ImageViewer::ImageViewer(QWidget *parent)
    : QWidget(parent)
{
    graduation = new GraduationView(this);
    graduation->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    QVector<QPair<qreal, QColor> > initramp;
    initramp.push_back(QPair<qreal, QColor>(-100.0,QColor(255,0,0)));
    initramp.push_back(QPair<qreal, QColor>(0.0,QColor(255,255,0)));

    rampEditor = new QColorRampEditor(NULL, Qt::Vertical);
    rampEditor->setSlideUpdate(true);
    rampEditor->setMappingTextVisualize(true);
    rampEditor->setMappingTextColor(Qt::black);
    rampEditor->setMappingTextAccuracy(1);
    rampEditor->setRamp(initramp);
    rampEditor->setFixedWidth(SIZE_PAL);

    graduation->setRampEditor(rampEditor);

    QObject::connect(rampEditor, SIGNAL(rampChanged()), graduation, SLOT(update()));

    lay = new QHBoxLayout();
    lay->addWidget(graduation);
    lay->addWidget(rampEditor);

    this->setLayout(lay);
}

void ImageViewer::resizeEvent(QResizeEvent *)
{
    graduation->setMinimumSize((this->width()-rampEditor->width()), this->height() );
}

ImageViewer::~ImageViewer()
{
    delete rampEditor;
    delete graduation;
    delete lay;
}
