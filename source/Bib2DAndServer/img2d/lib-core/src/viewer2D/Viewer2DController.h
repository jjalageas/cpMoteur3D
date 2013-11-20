#ifndef VIEWER_2D_CONTROLLER_H
#define VIEWER_2D_CONTROLLER_H

#include <QtGui>

#include <InterfaceTranscriber.h>
#include <Struct.hpp>
#include <Examen.h>
#include <Image3d.hpp>
#include <ImageMask2d.h>
#include <Filter.h>
#include <AlgoVolume.h>
#include "ImageViewerModel.h"

#include <FilterController.h>

class FormManager;

// A revelation : QSB <=> QSpinBox. But we don't have a QSpinBox in the source windows...


class Viewer2DController : public QObject
{
    Q_OBJECT

public:

    Viewer2DController(Examen* examen);//FormManager *form);
    ~Viewer2DController();

    void updateImageViewer();
    void updateInformationViewer();
    int getWindowingCenter();
    int getWindowingWidth();
    ImageViewerModel& getModel();


public slots:

    void examenChanged();
    void sliceChanged(int);
    // image view
    void showMask(bool);
    void showImage(bool);
    //void sliceDown();
    //void sliceUp();
    // windowing
    void windowingAuto();
    void windowingCenter(int);
    void windowingWidth(int);
    // mask edit
    void maskEditTypeChanged(int);
    void maskEditStyleChanged(int);
    void maskEditSizeChanged(int);
    // image viewer
    void selectedPixel(int, int);
    void viewedPixel(int, int);
    void mouseClick(int, int, int, int, int);
    // RG seed
    //void selectRGSeed(int x, int y);
    // filter routine
    //void filterRoutine(MiList<Filter_t *> *);
    // filter Balacey routine



private:

    void setupConnection();
    void modifiyMask(int x, int y);

    //FormManager *_formManager;
    ImageViewer *_viewer;

    // image view
    //int _windowingCenter;
    //int _windowingWidth;
    bool _imageFlag;
    bool _maskFlag;

    // mask edit
    int _maskEditType;
    int _maskEditStyle;
    int _maskEditSize;
    ImageViewerModel _model;
};

#endif
