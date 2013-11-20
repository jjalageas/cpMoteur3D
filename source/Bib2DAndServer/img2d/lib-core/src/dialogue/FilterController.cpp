#include "FilterController.h"
#include "InterfaceTranscriber.h"
#include "Tools.h"

#include <iostream>

using namespace std;

/*--------------------------------------------------------------------------------------------------------------------
             CONSTRUCT & DESCTRUCT
  --------------------------------------------------------------------------------------------------------------------*/

FilterController::FilterController(FilterDialog *dialog)
{
    ////RessourceManager::GetInstance()->addRessource("FilterController");

    //_filterDialog = InterfaceManager::GetInstance()->getFilterDialog();
    _filterDialog = dialog;
    _defaultImage = NULL;
    _image = NULL;
    _thresholdFilters = new MiList<Filter_t *>();
    _preTraitorFilters = new MiList<Filter_t *>();
    _traitorFilters = new MiList<Filter_t *>();
    _morphologyFilters = new MiList<Filter_t *>();
    _window = NULL;
    //_windowingCenter = NULL;
    //_windowingWidth = NULL;
    setupConnection();
}

FilterController::~FilterController()
{
    ////RessourceManager::GetInstance()->deleteRessource("FilterController");
}

/*--------------------------------------------------------------------------------------------------------------------
             PRIVATE METHODS
  --------------------------------------------------------------------------------------------------------------------*/

void FilterController::setupConnection()
{
    //connect(InterfaceManager::GetInstance(), SIGNAL(startFilterDialog()), this, SLOT(start()));
    connect(_filterDialog, SIGNAL(reset()), this, SLOT(init()));
    connect(_filterDialog, SIGNAL(undo()), this, SLOT(undo()));
    connect(_filterDialog, SIGNAL(quit()), this, SLOT(quit()));
    connect(_filterDialog, SIGNAL(applyRoutine()), this, SLOT(applyRoutine()));

    connect(_filterDialog, SIGNAL(showImage(bool)), this, SLOT(showImage(bool)));
    connect(_filterDialog, SIGNAL(showMask(bool)), this, SLOT(showMask(bool)));

    connect(_filterDialog, SIGNAL(preTraitorAdded(int, float, float)),
            this, SLOT(preTraitorAdd(int, float, float)));
    connect(_filterDialog, SIGNAL(traitorAdded(int, int, float)), this, SLOT(traitorAdd(int, int, float)));
    /*connect(_filterDialog, SIGNAL(bisseuillageChanged(int, int)),
            this, SLOT(bisseuillageSelect(int, int)));*/
    connect(_filterDialog, SIGNAL( ThresholdAdded(int, int,double)),
            this, SLOT(bisseuillageModeSelect(int, int,double)));
    connect(_filterDialog, SIGNAL(morphologyAdded(int, float, int,int,int,int,int,double)),
            this, SLOT(morphologyAdd(int, float, int,int,int,int,int,double)));
}

// mise à jour de l'image principale
void FilterController::updateImageViewer()
{
    if (_image != NULL) {
        Image<int> *imageView = InterfaceTranscriber::FromImage(_image, *_window,
                                                                _imageFlag, _maskFlag);
        _filterDialog->getImageViewer()->setImage(imageView);
        delete imageView; imageView = NULL;
    }
}

// mise à jour de la liste des filtres dans le QTreeWidget
void FilterController::updateFiltersList()
{
    MiList<MiList<string> > *res = new MiList<MiList<string> >();

    string type = "Pre-traitement";
    for (int i=0 ; i < _preTraitorFilters->size() ; i++)
    {
        Filter_t *f = _preTraitorFilters->get(i);
        string name = " ";
        string params = " ";
        ostringstream ss;
        ss << "Pitch : " << f->get(1) << " , Order : " << f->get(2);
        params = ss.str();
        switch((int)f->get(0))
        {
        case 0 : {
                name = "Spatial gaussian";
                ostringstream sss;
                sss << "Pitch : " << f->get(1);
                params = sss.str();
            }
            break;
        case 1: name = "Sigma";  break;
        case 2 : name = "Low Pass";  break;
        case 3 : name = "High pass"; break;
        }
        MiList<string> filter;
        filter.add(type);
        filter.add(name);
        filter.add(params);
        res->add(filter);
    }

    type = "Traitement";
    for (int i=0 ; i < _traitorFilters->size() ; i++)
    {
        Filter_t *f = _traitorFilters->get(i);
        string name = " ";
        string params = " ";
        switch((int)f->get(0))
        {
        case 4 : name = "Prewitt";  break;
        case 5 : name = "Sobel";  break;
        case 6 : name = "Laplacian";  break;
        case 8 :
            {
                name = "GVF";
                ostringstream ss;
                ss << "Iteration : " << f->get(1) << " , Order : " << f->get(2);
                params = ss.str();
            }
            break;
        case 9 : name = "Inversion";  break;
        case 10 :
            {
                name = "Fermeture contour";
                ostringstream ss;
                ss << "Angle : " << f->get(1) << " , taille : " << f->get(2);
                params = ss.str();

            }
            break;
        }

        MiList<string> filter;
        filter.add(type);
        filter.add(name);
        filter.add(params);
        res->add(filter);
    }

    type = "Morphology";
    for (int i=0 ; i < _morphologyFilters->size() ; i++)
    {
        Filter_t *f = _morphologyFilters->get(i);
        string name = " ";
        ostringstream ss;
        ss << "Iteration : " << f->get(1) << " , Connexity : " << f->get(2);
        string params = ss.str();
        switch((int)f->get(0))
        {
        case 11 : name = "Erosion";  break;
        case 12 : name = "Dilatation";  break;
        case 13 : name = "Close";  break;
        case 14 : name = "Open";  break;
        case 15 : name = "3 x D et 3 x E"; break;
        case 16 : name = "Erosion NDG";  break;
        case 17 : name = "Dilatation NDG";  break;
        case 18 : name = "Open NDG";  break;
        case 19 : name = "Close NDG";  break;
        case 20 : name = "Erosion Geodesique";  break;
        case 21 : name = "Dilatation Geodesique";  break;
        case 22 : name = "Open Geodesique";  break;
        case 23 : name = "Close Geodesique";  break;
        case 24 : name = "Reconstruction Erosion Geodesique";  break;
        case 25 : name = "Reconstruction Dilatation Geodesique";  break;
        case 26 : name = "Maxima regionnaux";  break;
        case 27 : name = "Minima regionnaux";  break;
        case 28 : name = "Thinning";  break;
        }

        MiList<string> filter;
        filter.add(type);
        filter.add(name);
        filter.add(params);
        res->add(filter);
    }

    _filterDialog->setFilterDescription(res);
    delete res;
}

// mise à jour de l'histogramme
/*void FilterController::updateHistogram()
{
    int *histogram = Tools::GetHistogram(_image);
    int width = _image->getMaxVal();
    int height = 0;
    for (int i=0 ; i < width ; i++)
        height = (histogram[i] > height) ? histogram[i] : height;
    _filterDialog->getHistogram()->drawCurve(histogram, width, height, -1);
    delete []histogram;
}*/

// application de la liste des différents filtres

void FilterController::applyFilters()
{
    initImage();
    // pre traitor
    Filters::ApplyRoutine(_image, _preTraitorFilters);
    // traitor
    Filters::ApplyRoutine(_image, _traitorFilters);
    // bisseuillage
    cout<<"APPLICATION filter :_bisseuillageMin: "<<_bisseuillageMin<<" _bisseuillageMax: "<<_bisseuillageMax<<endl;
    //FilterThreshold::Bisseuillage(_image, _bisseuillageMin, _bisseuillageMax); // TODO : REMOVED... but sure it's usefull
    // morphology
    Filters::ApplyRoutine(_image, _morphologyFilters);
}

// initialisation de la copie de l'image
void FilterController::initImage()
{
    ImageMask2d *newImage = new ImageMask2d(*_defaultImage);
    delete _image;
    _image = newImage;
}

void FilterController::initFilters()
{
    for (int i=0 ; i < _preTraitorFilters->size() ; i++)
        delete _preTraitorFilters->get(i);
    _preTraitorFilters->empty();

    for (int i=0 ; i < _traitorFilters->size() ; i++)
        delete _traitorFilters->get(i);
    _traitorFilters->empty();

    _bisseuillageMin = _bisseuillageMax = 0;

    for (int i=0 ; i < _morphologyFilters->size() ; i++)
        delete _morphologyFilters->get(i);
    _morphologyFilters->empty();

    updateFiltersList();
}

/*--------------------------------------------------------------------------------------------------------------------
             PUBLIC SLOT
  --------------------------------------------------------------------------------------------------------------------*/

// quand on clique sur le " PROCESS FILTER " ou CTRL+F
// TOTO : replace with SliceViewer !
void FilterController::start(ImageMask2d *slice)//Viewer2DController& viewer2DController)
{
    //Viewer2DController *viewer2DController = new Viewer2DController();//(this);
            //FormManager::GetInstance()->getViewer2DController();

    //ImageMask2d *slice = viewer2DController.getModel().getCurrentSlice();

    if (slice != NULL)
    {
        //_defaultImage = slice->getImage();
        delete _defaultImage;
        _defaultImage = new ImageMask2d(*slice);
        initImage();

        delete _window;
        _window = new GrayViewWindow(slice->getParams().getGrayViewWindow());
        /*delete _windowingCenter;
        _windowingCenter = window.getLuminosity();
        delete _windowingWidth;
        _windowingWidth = window.getContrast();*/
        //cout << _windowingWidth << endl;

        _imageFlag = true;
        _maskFlag = true;

        // initialisation des filtres
        _undoFlag.empty();
        initFilters();

        // initialisation de l'afficahge => FilterDialog
        _filterDialog->start();

        updateImageViewer();
        //updateHistogram();
    }
}

// quand on clique sur le bouton d'initialisation
void FilterController::init()
{
    _filterDialog->init();
    initImage();

    _undoFlag.empty();
    initFilters();

    updateImageViewer();
    //updateHistogram();
}

// quand on revient en arrière ou CTRL+Z
void FilterController::undo()
{
    if (_undoFlag.size() > 0)
    {
        int last = _undoFlag.getLast();
        /* pre traitor */
        if ( (last == 0) && (_preTraitorFilters->size() > 0) ) {
            delete _preTraitorFilters->get(_preTraitorFilters->size() - 1);
            _preTraitorFilters->erase(_preTraitorFilters->size() - 1);
        }
        /* traitor */
        else if ( (last == 1) && (_traitorFilters->size() > 0) ) {
            delete _traitorFilters->get(_traitorFilters->size() - 1);
            _traitorFilters->erase(_traitorFilters->size() - 1);
        }
        /* morphology */
        else if ( (last == 2) && (_morphologyFilters->size() > 0) ) {
            delete _morphologyFilters->get(_morphologyFilters->size() - 1);
            _morphologyFilters->erase(_morphologyFilters->size() - 1);
        }

        _undoFlag.erase(_undoFlag.size()-1);
        applyFilters();
        updateImageViewer();
        //updateHistogram();
        updateFiltersList();
    }
}

// on quitte l'application
void FilterController::quit()
{
    //delete _windowingCenter; _windowingCenter = NULL;
    //delete _windowingWidth;  _windowingWidth = NULL;
    delete _window; _window = NULL;

    _filterDialog->init();

    delete _image; _image = NULL;
    delete _defaultImage; _defaultImage = NULL;

    _undoFlag.empty();
    initFilters();

    _filterDialog->getImageViewer()->clear();
    _filterDialog->hide();
}

// on clique sur le bouton OK => application des filtres à l'ensemble des slices
void FilterController::applyRoutine()
{
    /* create general routine */
    MiList<Filter_t *> *routine = new MiList<Filter_t *>();
    for (int i=0 ; i  < _preTraitorFilters->size() ; i++)
    {
        Filter_t *filter = new Filter_t();
        filter->add(_preTraitorFilters->get(i)->get(0));
        filter->add(_preTraitorFilters->get(i)->get(1));
        filter->add(_preTraitorFilters->get(i)->get(2));
        routine->add(filter);
    }
    for (int i=0 ; i  < _traitorFilters->size() ; i++)
    {
        Filter_t *filter = new Filter_t();
        filter->add(_traitorFilters->get(i)->get(0));
        filter->add(_traitorFilters->get(i)->get(1));
        filter->add(_traitorFilters->get(i)->get(2));
        routine->add(filter);
    }
    for (int i=0 ; i  < _thresholdFilters->size() ; i++)
    {
        Filter_t *bisseuillage = new Filter_t();
        bisseuillage->add((float)_thresholdFilters->get(i)->get(0));
        bisseuillage->add((float)_thresholdFilters->get(i)->get(1));
        bisseuillage->add((float)_thresholdFilters->get(i)->get(2));
        bisseuillage->add((float)_thresholdFilters->get(i)->get(3));
        bisseuillage->add((float)_thresholdFilters->get(i)->get(4));
        routine->add(bisseuillage);
    }
    for (int i=0 ; i  < _morphologyFilters->size() ; i++)
    {
        Filter_t *filter = new Filter_t();
        filter->add(_morphologyFilters->get(i)->get(0));
        filter->add(_morphologyFilters->get(i)->get(1));
        filter->add(_morphologyFilters->get(i)->get(2));
        routine->add(filter);
    }

    /* quit dialog */
    //quit();

    /* emit filter routine */
    emit filterRoutine(routine);
}

void FilterController::showImage(bool flag)
{
    _imageFlag = flag;
    updateImageViewer();
}

void FilterController::showMask(bool flag)
{
    _maskFlag = flag;
    updateImageViewer();
}

void FilterController::preTraitorAdd(int item, float pitch, float order)
{
    Filter_t *filter = new Filter_t();
    filter->add((float)item);
    filter->add(pitch);
    filter->add(order);
    _preTraitorFilters->add(filter);

    _undoFlag.add(0);
    applyFilters();
    updateImageViewer();
    //updateHistogram();
    updateFiltersList();
}

void FilterController::traitorAdd(int item, int iteration, float order)
{
    Filter_t *filter = new Filter_t();
    filter->add((float)item);
    filter->add((float)iteration);
    filter->add((float)order);
    _traitorFilters->add(filter);

    _undoFlag.add(1);
    applyFilters();
    updateImageViewer();
    //updateHistogram();
    updateFiltersList();
}

/*void FilterController::bisseuillageSelect(int min, int max)
{
    _bisseuillageMin = Tools::FromHU(_image, min);
    _bisseuillageMax = Tools::FromHU(_image, max);


   // cout<<"Smin filter:"<<min<<"  Smax filter"<< max<<endl;
     //cout<<"_bisseuillageMinSmin filter:"<<_bisseuillageMin<<"  _bisseuillageMaxSmax filter"<<_bisseuillageMax <<endl;
    // bisseuillage
    FilterThreshold::Bisseuillage(_image, _bisseuillageMin, _bisseuillageMax);
    // morphology  au cas ou un filtre morpho serait deja en place
   bisseuillageModeSelect(7,0,0);
}*/

void FilterController::bisseuillageModeSelect(int typeBiseuillage, int coeff,double pourcent){

    //creer la liste pour les routines
    _thresholdFilters->empty();
    Filter_t *filter = new Filter_t();
    filter->add((float)typeBiseuillage);
    filter->add((float)_bisseuillageMin);
    filter->add((float)_bisseuillageMax);
    filter->add((float)coeff);
    filter->add((float)pourcent);
    _thresholdFilters->add(filter);
    //cout<<"bisseuillageModeSelectb _bisseuillageMinS :"<<filter->get(1)<<"  _bisseuillageMaxS"<<filter->get(2) <<endl;

    //applique la routine
    Filters::ApplyRoutine(_image, _thresholdFilters);
    /* morphology au cas ou un filtre morpho serait deja en place*/
    Filters::ApplyRoutine(_image, _morphologyFilters);

    //mise a jour
    updateImageViewer();
    updateFiltersList();

}

void FilterController::morphologyAdd(int item, float iteration, int connexity,int type,int size,int typeBiseuillage,int coeff,double pourcent)
{
    //biseuillage
   bisseuillageModeSelect( typeBiseuillage,  coeff, pourcent);

    /* morphology */
    Filter_t *filter = new Filter_t();
    filter->add((float)item);
    filter->add((float)iteration);
    filter->add((float)connexity);
    filter->add((float)size);
    filter->add((float)type);
    _morphologyFilters->add(filter);

    _undoFlag.add(2);
    Filters::ApplyRoutine(_image, _morphologyFilters);
    updateImageViewer();

    updateFiltersList();
}

