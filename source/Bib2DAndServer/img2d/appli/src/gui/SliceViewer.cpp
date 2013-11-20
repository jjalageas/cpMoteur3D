#include "SliceViewer.h"
#include "ui_SliceViewer.h"
#include <Tools.h>

#include <InterfaceTranscriber.h>
#include <iostream>
#include <QtCore>

using namespace std;



SliceViewer::SliceViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SliceViewer),
    _exam(NULL),
    _imgMask(NULL),
    _sliceIndex(0),
    _window(NULL),
    _type(CORONAL),
    _predefinedWindows(vector<PredefinedWindow>())
{
    ui->setupUi(this);

    // cf Dr. Grover Ronald Pardo Holzwarth
    addPredefinedWindow("Custom", 0, 0);
    addPredefinedWindowCW("Abdomen", 50, 250);
    addPredefinedWindowCW("Head", 50, 150);
    addPredefinedWindowCW("Lung", -550, 2000);
    addPredefinedWindowCW("Mediastinum", 50, 450);
    addPredefinedWindowCW("Soft Tissue", 200, 100);
    addPredefinedWindowCW("Spine", 40, 300);
    addPredefinedWindowCW("Vertebrae", 530, 450);

    connect(ui->imageViewer, SIGNAL(mouseWheelUp()), this, SLOT(mouseWheelUp()));
    connect(ui->imageViewer, SIGNAL(mouseWheelDown()), this, SLOT(mouseWheelDown()));
    connect(ui->luminositySlider, SIGNAL(valueChanged(int)), this, SLOT(luminositySlideValueChanged(int)));
    connect(ui->contrastSlider, SIGNAL(valueChanged(int)),  this, SLOT(contrastSlideValueChanged(int)));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(selectMode()));
    connect(ui->sliceType_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(selectSliceType(int)));

    updateIHM(true);
}

SliceViewer::~SliceViewer()
{
    delete ui; ui = NULL;
    delete _imgMask; _imgMask = NULL;
}

void SliceViewer::addPredefinedWindowCW(string name, int center, int width) {
    _predefinedWindows.push_back(PredefinedWindow(center - width /2, center + width /2));
    ui->comboBox->insertItem(ui->comboBox->count(), QString::fromStdString(name));
}

void SliceViewer::addPredefinedWindow(string name, int min, int max) {
    _predefinedWindows.push_back(PredefinedWindow(min, max));
    ui->comboBox->insertItem(ui->comboBox->count(), QString::fromStdString(name));
}

void
SliceViewer::setExamen(Examen *exam)
{
    eassert(exam != NULL);
    _exam = exam;
    delete _window;
    _window = new GrayViewWindow(_exam->getParams().getGrayViewWindow());
    _window->setContrast(ui->contrastSlider->value());
    _window->setLuminosity( - ui->luminositySlider->value());

    _sliceIndex = 0;
    delete _imgMask;
    _imgMask = _exam->getImageMask2d(_sliceIndex, _type);
    updateIHM(false);
}

void
SliceViewer::mouseWheelDown()
{
    if (_exam != NULL && _sliceIndex > 0) {
        delete _imgMask;
        _imgMask = _exam->getImageMask2d(--_sliceIndex, _type);
        updateImage();
    }
}

void
SliceViewer::mouseWheelUp()
{
    //cout << "UP!" << endl;
    if (_exam != NULL && _sliceIndex < Tools::lastSliceId(*_exam, _type) -1) {
        delete _imgMask;
        _imgMask = _exam->getImageMask2d(++_sliceIndex, _type);
        updateImage();
    }
}

void
SliceViewer::luminositySlideValueChanged(int lum)
{
    //cout << "BLOP!!!" << endl;
    _window->setLuminosity( - lum);
    //cout << "min : " << _window->getMin()->getHundsfieldValue() << endl;
    //cout << "max : " << _window->getMax()->getHundsfieldValue() << endl;

    updateIHM(true);
}

void
SliceViewer::contrastSlideValueChanged(int contrast)
{
    //cout << "Zim..." << endl;
    _window->setContrast(contrast);
    updateIHM(true);
}

void
SliceViewer::selectSliceType(int i) {
    SliceType types[] = { CORONAL, FRONTAL, SAGITAL };
    _type = types[i];
    _sliceIndex = 0;
    delete _imgMask;
    _imgMask = _exam->getImageMask2d(_sliceIndex, _type);
    updateImage();
}

void
SliceViewer::updateIHM(bool loosePredefinedInterval)
{
    ui->Lumino->setText(QString::number(ui->luminositySlider->value()));
    ui->Contrast->setText(QString::number(ui->contrastSlider->value()));
    if (loosePredefinedInterval == true)
        ui->comboBox->setCurrentIndex(0);
    if (_exam != NULL) {
        if (_exam->getImageRef().getDepth() > 1)
            ui->sliceType_combo->setVisible(true);
        else
            ui->sliceType_combo->setVisible(false);
    }
    updateImage();
}

void
SliceViewer::updateImage()
{
    if (_exam != NULL) {
        ui->sliceNbLabel->setText(QString("slice : " + QString::number(_sliceIndex + 1) +
                                          " / " + QString::number(Tools::lastSliceId(*_exam, _type))));
        Image<int> *displayableImage = InterfaceTranscriber::FromImage(
                    _imgMask, *_window, true, false);
        ui->imageViewer->setImage(displayableImage);
        delete displayableImage; displayableImage = NULL;
    }
}

//int SliceViewer::lastSliceId(Examen* e, SliceType type); // see Tools class


void
SliceViewer::selectMode()
{
    int i = ui->comboBox->currentIndex();
    if (i == 0)
        return;
    eassert(i < (int)_predefinedWindows.size());
    PredefinedWindow win = _predefinedWindows[i];
    _window->setMin(win.min);
    _window->setMax(win.max);

    bool old = ui->luminositySlider->blockSignals(true);
    GrayValue *val = _window->getLuminosity();
    ui->luminositySlider->setValue(val->getHundsfieldValue());
    delete val;
    ui->luminositySlider->blockSignals(old);

    old = ui->contrastSlider->blockSignals(true);
    val = _window->getContrast();
    ui->contrastSlider->setValue(val->getHundsfieldValue());
    delete val; val = NULL;
    ui->contrastSlider->blockSignals(old);

    updateIHM(false);
}
