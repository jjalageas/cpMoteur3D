#ifndef FILTER_CONTROLLER_H
#define FILTER_CONTROLLER_H

#include <QObject>

#include <FilterDialog.h>
//#include <Viewer2DController.h>

#include <Struct.hpp>
#include <Filters.h>
//#include "Viewer2DController.h"
#include "GrayViewWindow.h"

/**
  * @class FilterController
  * @brief Permet la gestion du FilterDialog
  *
  * Cette classe gère les différents traitements sélectionnés dans FilterDialog en
  * faisant appel à la classe Filter.
  * En outre, elle garde en mémoire la liste des traitements effectuer afin de pouvoir
  * revenir en arrière, à travers un bouton dans l'interface et au raccourci clavier CTRL+Z.
  */
class FilterController : public QObject
{
       Q_OBJECT

public:

       FilterController(FilterDialog *dialog);
       ~FilterController();

public slots:

       void start(ImageMask2d *slice); // TODO : replace with SliceViewer ?
       void init();
       void undo();
       void quit();
       void applyRoutine();

       void showImage(bool);
       void showMask(bool);

       void preTraitorAdd(int, float, float);
       void traitorAdd(int, int, float);
       //void bisseuillageSelect(int, int);
       void bisseuillageModeSelect(int typeBiseuillage, int coeff,double pourcent);
       void morphologyAdd(int, float, int,int type,int size,int typeBiseuillage,int coeff, double pourcent);

signals:

       void filterRoutine(MiList<Filter_t *> *);

private:

       void setupConnection();
       void updateImageViewer();
       void updateFiltersList();
       void updateHistogram();
       void applyFilters();
       void initImage();
       void initFilters();

       FilterDialog *_filterDialog;
       ImageMask2d *_defaultImage;
       ImageMask2d *_image;
       MiList<Filter_t *> *_thresholdFilters;
       MiList<Filter_t *> *_preTraitorFilters;
       MiList<Filter_t *> *_traitorFilters;
       MiList<Filter_t *> *_morphologyFilters;
       float _bisseuillageMin;
       float _bisseuillageMax;

       bool _imageFlag;
       bool _maskFlag;
       GrayViewWindow* _window;
       //GrayValue* _windowingCenter;
       //GrayValue* _windowingWidth;
       MiList<int> _undoFlag;
};

#endif
