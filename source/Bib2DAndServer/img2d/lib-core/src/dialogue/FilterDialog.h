#ifndef FILTER_DIALOG_H
#define FILTER_DIALOG_H

#include <QtGui>

//#include <CurveViewer.h>
#include <ImageViewer.h>
#include <Struct.hpp>
//#include <RessourceManager.h>
//#include <DataManager.h>
/**
  * @class FilterDialog
  * @brief Gère l'affichage de la fenêtre de filtre
  *
  * Classe présentant une fenêtre gérant l'affichage des filtres. Elle présente une zone avec l'Image
  * courante de l'application filtrée, la liste des filtre appliquées et un histogramme.
  * Elle permet aussi la sauvegarde de l'image filtrée et de l'histogramme.
  */
class FilterDialog : public QDialog
{
    Q_OBJECT

public:

    FilterDialog(QWidget *parent = 0);
    ~FilterDialog();

    void start();
    void init();
    void setBiseuillageRange(int min, int max);
    void setFilterDescription(MiList<MiList<std::string> > *filters);

    ImageViewer *getImageViewer();
    //CurveViewer *getHistogram();

public slots:

    /* PRE-TRAITEMENT */
    void preTraitorChanged(int);
    void slotPreTraitorAdded();

    /* TRAITEMENT */
    void traitorChanged(int);
    void slotTraitorAdded();

    /* BISSEUILLAGE */
    void minSeuilSliderChanged(int);
    void minSeuilSpinBoxChanged(int);
    void maxSeuilSliderChanged(int);
    void maxSeuilSpinBoxChanged(int);
    void BiseuillageChanged(int);

    /* MORPHOLOGY */
    void morphologyChanged(int);
    void slotMorphologyAdded();

    /* BUTTONS */
    void validRoutine();
    void slotInit();
    void slotUndo();
    void slotQuit();
    void quit(int);
    void saveImage();
    //void saveHistogram();

    /* IMAGE VIEWER CONTROL */
    void showImage();
    void showMask();

protected:

    void closeEvent(QCloseEvent *);

signals:

    void showImage(bool);
    void showMask(bool);

    void preTraitorAdded(int, float, float);
    void traitorAdded(int, int, float);
    void bisseuillageChanged(int, int);
    void ThresholdAdded(int, int,double);
    void morphologyAdded(int, float, int,int,int,int,int,double);

    void applyRoutine();
    void reset();
    void undo();
    void quit();

private:

    void setupInterface();
    void setupAction();

    QScrollArea *_imageArea;
    ImageViewer *_imageViewer;
    //CurveViewer *_histogram;

    /* PRE-TRAITEMENT */
    QComboBox *_preTraitorComboBox;
    QDoubleSpinBox *_pitchSpinBox;
    QDoubleSpinBox *_orderSpinBox;
    QPushButton *_preTraitorPushButton;

    /* TRAITEMENT */
    QComboBox *_traitorComboBox;
    QPushButton *_traitorPushButton;
    QSpinBox *_traitorIterationSpinBox;
    QDoubleSpinBox *_traitorOrderSpinBox;

    /* BISSEUILLAGE */
    QSlider *_minSeuillageSlider;
    QSpinBox *_minSeuillageSpinBox;
    QSlider *_maxSeuillageSlider;
    QSpinBox *_maxSeuillageSpinBox;
    QComboBox *_ThresholdComboBox;
    QSpinBox *_ThresholdSpinBox;
    QDoubleSpinBox *_CoeffSpinBox;

    /* MORPHOLOGY */
    QComboBox *_morphoComboBox;
    QSpinBox *_morphoTypeStrucSpinBox;
    QSpinBox *_morphoSpinBox;
    QPushButton *_morphoPushButton;
    QComboBox *_morphoConnexityComboBox,*_morphoTypeComboBox;

    /* FILTERS DESCRITPION TREE */
    QTreeWidget *_filtersTreeWidget;

    /* BUTTONS */
    QCheckBox *_showImage;
    QCheckBox *_showMask;
    QPushButton *_initButton;
    QPushButton *_undoButton;
    QPushButton *_okButton;
    QPushButton *_closeButton;
    //QPushButton *_saveHistogramButton;
    QPushButton *_saveImageButton;
};

#endif
