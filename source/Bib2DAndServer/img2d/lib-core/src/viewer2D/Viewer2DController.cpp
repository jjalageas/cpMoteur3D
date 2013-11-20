#include "Viewer2DController.h"
#include "Tools.h"

/*--------------------------------------------------------------------------------------------------------------------
             CONSTRUCT & DESCTRUCT
  --------------------------------------------------------------------------------------------------------------------*/

Viewer2DController::Viewer2DController(Examen* examen)//FormManager *form)
    : _model(ImageViewerModel(examen))
{
    //RessourceManager::GetInstance()->addRessource("Viewer2DController");

    //_formManager = form;
    _viewer = new ImageViewer();
    setupConnection();
}


Viewer2DController::~Viewer2DController()
{
    //RessourceManager::GetInstance()->deleteRessource("Viewer2DController");
}

/*--------------------------------------------------------------------------------------------------------------------
             PUBLIC METHODS
  --------------------------------------------------------------------------------------------------------------------*/

void Viewer2DController::updateImageViewer()
{
    ImageMask2d* slice = _model.getCurrentSlice();
    if (slice != NULL)
    {
        // image viewer
        //Image<float> *image = slice->getImageRef();
        /*float wCenter = Tools::FromHU(slice, _windowingCenter);
        float wWidth = Tools::FromHU(slice, _windowingWidth);*/

        Image<int>* imageView = InterfaceTranscriber::FromImage(slice, slice->getParams().getGrayViewWindow(),
                                                                _imageFlag, _maskFlag);
        _viewer->setImage(imageView);

        delete imageView;
    }
}

/*void Viewer2DController::updateInformationViewer()
{
    ImageMask2d *slice = _model.getCurrentSlice();
    if (slice != NULL)
        InterfaceManager::GetInstance()->getInformationViewer()->setSliceInformation(slice->getInformations());
}*/

int Viewer2DController::getWindowingCenter()
{
    return _windowingCenter;
}

int Viewer2DController::getWindowingWidth()
{
    return _windowingWidth;
}

/*--------------------------------------------------------------------------------------------------------------------
             PRIVATE METHODS
  --------------------------------------------------------------------------------------------------------------------*/

void Viewer2DController::setupConnection()
{
    // examen changed
    //connect (_formManager, SIGNAL(examenChanged()), this, SLOT(examenChanged()));
    // image view
    /*InterfaceManager *interfaceManager = InterfaceManager::GetInstance();
    connect (interfaceManager->getSliceQSB(), SIGNAL(valueChanged(int)), this, SLOT(sliceChanged(int)));
    connect (interfaceManager, SIGNAL(showMask(bool)), this, SLOT(showMask(bool)));
    connect (interfaceManager, SIGNAL(showImage(bool)), this, SLOT(showImage(bool)));
    connect (interfaceManager, SIGNAL(windowingAuto()), this, SLOT(windowingAuto()));
    connect (interfaceManager, SIGNAL(windowingCenterChanged(int)), this, SLOT(windowingCenter(int)));
    connect (interfaceManager, SIGNAL(windowingWidthChanged(int)), this, SLOT(windowingWidth(int)));
    // mask edit
    connect (interfaceManager, SIGNAL(maskEdit(int)), this, SLOT(maskEditTypeChanged(int)));
    connect (interfaceManager, SIGNAL(maskEditType(int)), this, SLOT(maskEditStyleChanged(int)));
    connect (interfaceManager, SIGNAL(maskEditSizeChanged(int)), this, SLOT(maskEditSizeChanged(int)));
    // region growing seed
    connect (interfaceManager, SIGNAL(selectRGSeed(int ,int)), this, SLOT(selectRGSeed(int, int)));
*/
    // image viewer in main interface
    //ImageViewer *imageViewer = interfaceManager->getImageViewer();

    connect (_viewer, SIGNAL(mouseMove(int,int)), this, SLOT(viewedPixel(int, int)));
    connect (_viewer, SIGNAL(mouseMovePress(int,int)), this, SLOT(selectedPixel(int,int)));
    connect (_viewer, SIGNAL(mousePress(int,int,int,int,int)), this, SLOT(mouseClick(int, int, int, int, int)));
    /*connect (_viewer, SIGNAL(mouseWheelDown()), this, SLOT(sliceDown()));
    connect (_viewer, SIGNAL(mouseWheelUp()), this, SLOT(sliceUp()));*/

    // filter controller
    /*FilterController *filterController = _formManager->getFilterController();
    connect(filterController, SIGNAL(filterRoutine(MiList<Filter_t *> *)), this,
            SLOT(filterRoutine(MiList<Filter_t *> *)));*/

    // MultiVolumeControler  controller
    /*MultiVolumeControler *multiVolumeController = _formManager->getMultiVolumeController();
    connect(multiVolumeController, SIGNAL(applyRoutineMultiVolume(MiList<float>)), this,
           SLOT(applyRoutineBalacey(MiList<float>)));*/


    //Expiration controler
    //ExpiControler *ExpiController = _formManager->getExpiControler();

    //connect(ExpiController, SIGNAL(applyRoutineExpiration(MiList<float>)), this,
    //        SLOT(applyRoutineExpi(MiList<float>)));
}

/*void Viewer2DController::modifiyMask(int x, int y)
{
    ImageMask2d *slice = _model.getCurrentSlice();
    if (_maskFlag && (slice != NULL) )
    {
        Image<bool> *mask = slice->getMaskRef();
        Tools::ModifyMask(mask, x, y, _maskEditSize, (_maskEditType % 2), _maskEditStyle);
    }
}*/

/*--------------------------------------------------------------------------------------------------------------------
             PUBLIC SLOTS
  --------------------------------------------------------------------------------------------------------------------*/

void Viewer2DController::examenChanged()
{
    Examen *examen = _model.getCurrentExamen();
    if (examen != NULL)
    {
        //ExamenParams &params = examen->getParams();
        //int windowingMin = params.getWindowingMin();
        //int windowingMax = params.getWindowingMax();

        //InterfaceManager *interface = InterfaceManager::GetInstance();
        //interface->setWindowingRange(windowingMin, windowingMax);
        //int wCenter = (windowingMin + windowingMax) / 2;
        //int wWidth = windowingMax - windowingMin;
        //interface->setWindowing(wCenter, wWidth);

        //int examSize = _model.getCurrentExamen()->getDepth(); // TODO : depth? I think it's the max of the current slice mode that is asked.
        //QLabel *examQL = interface->getExamenSizeQL();
        //examQL->setText(QString::number(examSize));

        //QSpinBox *sliceQSB = interface->getSliceQSB();
        /*if (sliceQSB->value() == 0)
            interface->getSliceQSB()->setValue(0);
        sliceQSB->setRange(0, examSize);*/
    }
    else
    {
        //InterfaceManager *interface = InterfaceManager::GetInstance();
        /*interface->getExamenSizeQL()->setText(tr("0"));
        interface->getSliceQSB()->setRange(0, 0);
        interface->getSliceQSB()->setValue(0);*/
        _imageFlag = _maskFlag = true;
        _windowingCenter = _windowingWidth = 0;
        _maskEditType = _maskEditStyle = 0;
        _maskEditSize = 4;
    }
}

void Viewer2DController::sliceChanged(int)
{
    updateImageViewer();
    //updateInformationViewer();
}

// image view

/*void Viewer2DController::sliceUp()
{
    InterfaceManager * interface = InterfaceManager::GetInstance();
    interface->getSliceQSB()->stepUp();
}

void Viewer2DController::sliceDown()
{
    InterfaceManager * interface = InterfaceManager::GetInstance();
    interface->getSliceQSB()->stepDown();
}*/

void Viewer2DController::showMask(bool flag)
{
    _maskFlag = flag;
    updateImageViewer();
}

void Viewer2DController::showImage(bool flag)
{
    _imageFlag = flag;
    updateImageViewer();
}

// windowing

void Viewer2DController::windowingAuto()
{
    ImageMask2d *slice = _model.getCurrentSlice();
    if (slice != NULL)
    {
        Image<float> *image = slice->getImageRef();
        GrayViewWindow *window = slice->getParams().getGrayViewWindow();
        window->set
        //Image<float> *module = image->getImageRef();
        //ExamenParams &params = slice->getParams();
        float min = image->getMin();
        float max = image->getMax();

        int width  = (int) max - min;
        int center  = (int) ( min + (width / 2));
        center = Tools::ToHU(slice, center);
        width = Tools::ToHU(slice, width);

        if ( (_windowingCenter != center) || (_windowingWidth != width) )
        {
            _windowingCenter = center;
            _windowingWidth = width;
            // TODO : this method is incompatible with the current sources?
            //InterfaceManager::GetInstance()->setWindowing(_windowingCenter, _windowingWidth);
            updateImageViewer();
        }

        //delete module;
        //module = NULL;
    }
}

void Viewer2DController::windowingCenter(int center)
{
    if (_windowingCenter != center)
    {
        _windowingCenter = center;
        updateImageViewer();
    }
}

void Viewer2DController::windowingWidth(int width)
{
    if (_windowingWidth != width)
    {
        _windowingWidth = width;
        updateImageViewer();
    }
}

// mask edit

void Viewer2DController::maskEditTypeChanged(int val)
{
    _maskEditType = val;
}

void Viewer2DController::maskEditStyleChanged(int val)
{
    _maskEditStyle = val;
}

void Viewer2DController::maskEditSizeChanged(int val)
{
    _maskEditSize = val;
}

// image viewer

void Viewer2DController::viewedPixel(int x, int y)
{
    ImageMask2d *slice = _model.getCurrentSlice();
    if (slice != NULL)
    {
        Image<float> *image = slice->getImageRef();
        int width = image->getWidth();
        int height = image->getHeight();

        if  ( (x >= 0) && (x < width) && (y >=0) && (y < height) )
        {
            float val = image->get(x, y);
            val = Tools::ToHU(slice, val);
            ostringstream pixelValue;
            pixelValue << "(" << x << ", " << y << ") : " << val;

            //InterfaceManager::GetInstance()->setStatusBarMessage(pixelValue.str());
        }
    }
}

void Viewer2DController::mouseClick(int x, int y, int, int, int button)
{
    /* left click & mask edit (pen / gum) */
    if ( (button == 0) && (_maskEditType != 0) )
    {
        //modifiyMask(x, y);
        updateImageViewer();
    }
}

void Viewer2DController::selectedPixel(int x, int y)
{
    /* mask edit (pen / gum) */
    if (_maskEditType != 0)
    {
        //modifiyMask(x, y);
        updateImageViewer();
    }
}

ImageViewerModel& Viewer2DController::getModel() {
    return _model;
}

/* RG seed */
/*
void Viewer2DController::selectRGSeed(int x, int y)
{
    Examen *examen = _model.getCurrentExamen();
    if (examen != NULL)
    {
        InterfaceManager *interface = InterfaceManager::GetInstance();
        examen->setSeed(x, y, interface->getSliceQSB()->value() - 1);
        _formManager->getViewer3DController()->updateControlViewer();
    }
}*/

/* filter routine */

/*void Viewer2DController::filterRoutine(MiList<Filter_t *> *routine)
{
    int totalSize = 0;
    DataManager *dataManager = DataManager::GetInstance();
    InterfaceManager *interfaceManager = InterfaceManager::GetInstance();

    int dataManagerSize = dataManager->getSize();

    for (int i=0 ; i < dataManagerSize ; i++)
        totalSize += dataManager->getExamen(i)->getSize();
    float progressRatio = (float)100/totalSize;
    float progressValue = 0.0;

    MiTimer timer;
    timer.start();
    interfaceManager->setStatusBarMessage("Applying filters");

    for (int e=0 ; e < dataManagerSize ; e++)
    {
        int examenSize = dataManager->getExamen(e)->getSize();

        for (int s=0 ; s < examenSize ; s++)
        {
            Filter::ApplyRoutine(dataManager->getSlice(e, s)->getImage(), routine);
            cout<<"            nb Point image["<<s<<"]="<<dataManager->getSlice(e, s)->getImage()->getMask()->getNbPt()<<endl;

            progressValue += progressRatio;
            interfaceManager->setProgressBarValue(progressValue);
        }
    }

    timer.stop("Filters have been applied in ");

    interfaceManager->setProgressBarValue(100);
    interfaceManager->setStatusBarMessage(string("Filters have been applied correctly"));

    for (int i=0 ; i < routine->size() ; i++)
        delete routine ->get(i);
    delete routine;

    updateImageViewer();
}
*/

