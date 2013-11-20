#include "FilterDialog.h"

/* -------------------------------------------------------------------------------------------------
     CONSTRUCT & DESTRUCT
   -------------------------------------------------------------------------------------------------*/

FilterDialog::FilterDialog(QWidget *parent) : QDialog(parent)
{
    //RessourceManager::GetInstance()->addRessource("FilterDialog");
    //_histogram = NULL;

    setupInterface();
    setupAction();

    setWindowTitle(tr("Medical Imaging - Filter"));
    setModal(true);
    hide();
}

FilterDialog::~FilterDialog()
{
    //RessourceManager::GetInstance()->deleteRessource("FilterDialog");

    delete _imageViewer; _imageViewer = NULL;
    //delete _histogram; _histogram = NULL;
}

/* -------------------------------------------------------------------------------------------------
     PUBLIC METHODS
   -------------------------------------------------------------------------------------------------*/

void FilterDialog::start()
{
    _imageViewer->defaultSize();
    _showImage->setChecked(true);
    _showMask->setChecked(true);

    init();
    show();
}

void FilterDialog::init()
{
    _undoButton->setDisabled(true);
    _initButton->setDisabled(true);
    _okButton->setDisabled(true);

    _filtersTreeWidget->clear();

    _preTraitorComboBox->setCurrentIndex(0);
    preTraitorChanged(0);
    _traitorComboBox->setCurrentIndex(0);
    traitorChanged(0);
    _morphoComboBox->setCurrentIndex(0);
    morphologyChanged(0);

    _minSeuillageSlider->setValue(0);
    _maxSeuillageSlider->setValue(0);
}

void FilterDialog::setBiseuillageRange(int min, int max)
{
    max = 2000;
    min = -max;
    _minSeuillageSlider->setRange(min, max);
    _minSeuillageSpinBox->setRange(min, max);
    _maxSeuillageSlider->setRange(min, max);
    _maxSeuillageSpinBox->setRange(min, max);
}

void FilterDialog::setFilterDescription(MiList<MiList<std::string> > *filters)
{
    _filtersTreeWidget->clear();

    for (int i=0 ; i < filters->size() ; i++)
    {
        MiList<std::string> filter = filters->get(i);
        if (filter.size() == 3)
        {
            QStringList itemData;
            itemData << QString::fromStdString(filter.get(0))
                    << QString::fromStdString(filter.get(1))
                    << QString::fromStdString(filter.get(2));
            _filtersTreeWidget->addTopLevelItem(new QTreeWidgetItem(itemData));
        }
    }

    _undoButton->setEnabled(filters->size() != 0);

}

ImageViewer *FilterDialog::getImageViewer()
{
    return _imageViewer;
}

/*CurveViewer *FilterDialog::getHistogram()
{
    return _histogram;
}*/

/* -------------------------------------------------------------------------------------------------
     PRIVATE METHODS
   -------------------------------------------------------------------------------------------------*/

void FilterDialog::setupInterface()
{


    QString iconsPath = "../trunk/View/Icons/";

    /* MAIN LAYOUT */
    QGridLayout *mainLayout = new QGridLayout(this);
    setLayout(mainLayout);

    /* IMAGE VIEWER */
    _imageViewer = new ImageViewer();
    _imageArea = new QScrollArea(this);
    _imageArea->setAlignment(Qt::AlignCenter);
    _imageArea->setMinimumSize(275, 300);
    _imageArea->setWidget(_imageViewer);

    mainLayout->addWidget(_imageArea, 1, 0);

    /* MAIN TAB */
    QTabWidget *mainTab= new QTabWidget(this);
    mainTab->setMinimumWidth(450);
    mainTab->setMinimumHeight(500);
    mainLayout->addWidget(mainTab, 1, 1, Qt::AlignCenter);


    /* FILTERS TAB */
    QWidget *filterTabWidget = new QWidget(mainTab);
    QVBoxLayout *filterTabLayout = new QVBoxLayout(filterTabWidget);
    filterTabWidget->setLayout(filterTabLayout);
    mainTab->addTab(filterTabWidget, tr("Filters"));

    /* PRE-TRAITEMENT GROUP */
    QGroupBox *preTraitorGroupBox = new QGroupBox(tr("Pre-traitement"), filterTabWidget);
    QGridLayout *preTraitorLayout = new QGridLayout(preTraitorGroupBox);
    preTraitorLayout->setColumnMinimumWidth(1, 300);
    preTraitorGroupBox->setLayout(preTraitorLayout);
    filterTabLayout->addWidget(preTraitorGroupBox);

    _preTraitorComboBox = new QComboBox(preTraitorGroupBox);
    _preTraitorComboBox->addItem(tr("None"), QVariant(-1));
    _preTraitorComboBox->addItem(tr("Spatial gaussian"), QVariant(0));
    _preTraitorComboBox->addItem(tr("Sigma"), QVariant(1));
    _preTraitorComboBox->addItem(tr("Low Pass"), QVariant(2));
    _preTraitorComboBox->addItem(tr("High pass"), QVariant(3));
    preTraitorLayout->addWidget(_preTraitorComboBox, 0, 0, 1, 0);

    QLabel *pitchLabel= new QLabel(tr("Pitch"), preTraitorGroupBox);
    preTraitorLayout->addWidget(pitchLabel, 1, 0);
    _pitchSpinBox = new QDoubleSpinBox(preTraitorGroupBox);
    _pitchSpinBox->setFixedWidth(90);
    _pitchSpinBox->setRange((double)0, (double)1000);
    _pitchSpinBox->setSingleStep(0.01);
    _pitchSpinBox->setAlignment(Qt::AlignRight);
    preTraitorLayout->addWidget(_pitchSpinBox, 1, 1);

    QLabel *orderLabel= new QLabel(tr("Order"), preTraitorGroupBox);
    preTraitorLayout->addWidget(orderLabel, 1, 2);
    _orderSpinBox = new QDoubleSpinBox(preTraitorGroupBox);
    _orderSpinBox->setFixedWidth(90);
    _orderSpinBox->setRange((double)0, (double)1000);
    _orderSpinBox->setSingleStep(0.01);
    _orderSpinBox->setAlignment(Qt::AlignRight);
    preTraitorLayout->addWidget(_orderSpinBox, 1, 3);

    _preTraitorPushButton = new QPushButton(QIcon(iconsPath+"add.png"), tr("Add"), preTraitorGroupBox);
    _preTraitorPushButton->setFixedWidth(80);
    preTraitorLayout->addWidget(_preTraitorPushButton, 2, 4);

    /* TRAITEMENT GROUP */
    QGroupBox *traitorGroupBox = new QGroupBox(tr("Traitement"), filterTabWidget);
    QGridLayout *traitorLayout = new QGridLayout(traitorGroupBox);
    traitorGroupBox->setLayout(traitorLayout);
    filterTabLayout->addWidget(traitorGroupBox);

    _traitorComboBox = new QComboBox(traitorGroupBox);
    _traitorComboBox->addItem(tr("None"), QVariant(-1));
    _traitorComboBox->addItem(tr("Prewitt"), QVariant(4));
    _traitorComboBox->addItem(tr("Sobel"), QVariant(5));
    _traitorComboBox->addItem(tr("Laplacian"), QVariant(6));
    _traitorComboBox->addItem(tr("GVF"), QVariant(8));
    _traitorComboBox->addItem(tr("Inversion"), QVariant(9));
    _traitorComboBox->addItem(tr("Fermeture de contour"), QVariant(10));
    traitorLayout->addWidget(_traitorComboBox, 0, 0, 1, 0);

    traitorLayout->addWidget(new QLabel(tr("Iteration : "), traitorGroupBox), 1, 0);
    _traitorIterationSpinBox = new QSpinBox(traitorGroupBox);
    _traitorIterationSpinBox->setRange(1, 1000);
    traitorLayout->addWidget(_traitorIterationSpinBox, 1, 1);

    traitorLayout->addWidget(new QLabel(tr("Order : "), traitorGroupBox), 1, 2, Qt::AlignRight);
    _traitorOrderSpinBox = new QDoubleSpinBox(traitorGroupBox);
    _traitorOrderSpinBox->setRange(0.001, 10.0);
    _traitorOrderSpinBox->setSingleStep(0.01);
    traitorLayout->addWidget(_traitorOrderSpinBox, 1, 3);

    _traitorPushButton = new QPushButton(QIcon(iconsPath+"add.png"), tr("Add"), traitorGroupBox);
    _traitorPushButton->setFixedWidth(80);
    traitorLayout->addWidget(_traitorPushButton, 2, 4, Qt::AlignRight);


    /* BISSEUILLAGE GROUP */
    QGroupBox *bisseuillageGroupBox = new QGroupBox(tr("Biseuillage"), filterTabWidget);
    QGridLayout *bisseuillageLayout = new QGridLayout(bisseuillageGroupBox);
    bisseuillageGroupBox->setLayout(bisseuillageLayout);
    filterTabLayout->addWidget(bisseuillageGroupBox);

    QLabel *minSeuillageLabel = new QLabel(tr("Min"), bisseuillageGroupBox);
    bisseuillageLayout->addWidget(minSeuillageLabel, 0, 0);
    _minSeuillageSlider = new QSlider(Qt::Horizontal, bisseuillageGroupBox);
    bisseuillageLayout->addWidget(_minSeuillageSlider, 0, 1);
    _minSeuillageSpinBox = new QSpinBox(bisseuillageGroupBox);
    _minSeuillageSpinBox->setFixedWidth(70);
    bisseuillageLayout->addWidget(_minSeuillageSpinBox, 0, 3);

    QLabel *maxSeuillageLabel = new QLabel(tr("Max"), bisseuillageGroupBox);
    bisseuillageLayout->addWidget(maxSeuillageLabel, 1, 0);
    _maxSeuillageSlider = new QSlider(Qt::Horizontal, bisseuillageGroupBox);
    bisseuillageLayout->addWidget(_maxSeuillageSlider, 1, 1);
    _maxSeuillageSpinBox = new QSpinBox(bisseuillageGroupBox);
    _maxSeuillageSpinBox->setFixedWidth(70);
     bisseuillageLayout->addWidget(_maxSeuillageSpinBox, 1, 3);

    _ThresholdComboBox = new QComboBox(bisseuillageGroupBox);
    _ThresholdComboBox->addItem(tr("Manuelle"), QVariant(7));
    _ThresholdComboBox->addItem(tr("Max entropie"), QVariant(29));
    _ThresholdComboBox->addItem(tr("Largeur mi-hauteur"), QVariant(30));
    _ThresholdComboBox->addItem(tr("Otsu"), QVariant(31));
    _ThresholdComboBox->addItem(tr("Pourcentage"), QVariant(32));
    _ThresholdComboBox->addItem(tr("Joh"), QVariant(33));
    _ThresholdComboBox->addItem(tr("Min error"), QVariant(34));
    _ThresholdComboBox->addItem(tr("Fuzzy"), QVariant(35));
    _ThresholdComboBox->addItem(tr("Fischer"), QVariant(36));
    _ThresholdComboBox->addItem(tr("Two peaks"), QVariant(37));

    bisseuillageLayout->addWidget(_ThresholdComboBox,2,0);

    bisseuillageLayout->addWidget(new QLabel(tr("Coeff : "),bisseuillageGroupBox ), 2, 1);
    _ThresholdSpinBox = new QSpinBox(bisseuillageGroupBox);
    _ThresholdSpinBox->setRange(1, 1000);
    bisseuillageLayout->addWidget(_ThresholdSpinBox, 2, 2);

    bisseuillageLayout->addWidget(new QLabel(tr("% : "),bisseuillageGroupBox ), 2, 3);
    _CoeffSpinBox = new QDoubleSpinBox(bisseuillageGroupBox);
    _CoeffSpinBox->setRange(0.001, 10.0);
    _CoeffSpinBox->setSingleStep(0.01);
    bisseuillageLayout->addWidget(_CoeffSpinBox, 2, 4);



    /* MORPHOLOGY GROUP */
    QGroupBox *morphoGroupBox = new QGroupBox(tr("Morphology"), filterTabWidget);
    QGridLayout *morphoLayout = new QGridLayout(morphoGroupBox);
    morphoLayout->setColumnMinimumWidth(1, 300);
    morphoGroupBox->setLayout(morphoLayout);
    filterTabLayout->addWidget(morphoGroupBox);

    _morphoComboBox = new QComboBox(morphoGroupBox);
    _morphoComboBox->addItem(tr("None"), QVariant(-1));
    _morphoComboBox->addItem(tr("Erosion Binaire"), QVariant(11));
    _morphoComboBox->addItem(tr("Dilatation Binaire"), QVariant(12));
    _morphoComboBox->addItem(tr("Fermeture Binaire"), QVariant(13));
    _morphoComboBox->addItem(tr("Ouverture Binaire"), QVariant(14));
    _morphoComboBox->addItem(tr("n x D et n x E"), QVariant(15));
    _morphoComboBox->addItem(tr("Erosion NDG"), QVariant(16));
    _morphoComboBox->addItem(tr("Dilatation NDG"), QVariant(17));
    _morphoComboBox->addItem(tr("Fermeture NDG"), QVariant(18));
    _morphoComboBox->addItem(tr("Ouverture NDG"), QVariant(19));
    _morphoComboBox->addItem(tr("Erosion Geodesique"), QVariant(20));
    _morphoComboBox->addItem(tr("Dilatation Geodesique"), QVariant(21));
    _morphoComboBox->addItem(tr("Fermeture Geodesique"), QVariant(22));
    _morphoComboBox->addItem(tr("Ouverture Geodesique"), QVariant(23));
    _morphoComboBox->addItem(tr("Reconstruction par erosion"), QVariant(24));
    _morphoComboBox->addItem(tr("Reconstruction par dilatation"), QVariant(25));
    _morphoComboBox->addItem(tr("Maxima regionnaux"), QVariant(26));
    _morphoComboBox->addItem(tr("Minima regionnaux"), QVariant(27));
    _morphoComboBox->addItem(tr("amincissement"), QVariant(28));

    morphoLayout->addWidget(_morphoComboBox, 0, 0, 1, 0);


   morphoLayout->addWidget(new QLabel(tr("Iteration: "), morphoGroupBox), 1, 0, Qt::AlignRight);
    _morphoSpinBox = new QSpinBox(morphoGroupBox);
    _morphoSpinBox->setFixedWidth(60);
    _morphoSpinBox->setAlignment(Qt::AlignRight);
    morphoLayout->addWidget(_morphoSpinBox, 1, 1, Qt::AlignLeft);

    morphoLayout->addWidget(new QLabel(tr("Taille Elt : "), morphoGroupBox), 1, 2, Qt::AlignRight);
    _morphoTypeStrucSpinBox = new QSpinBox(morphoGroupBox);
    _morphoTypeStrucSpinBox->setSingleStep(0);
    morphoLayout->addWidget(_morphoTypeStrucSpinBox, 1, 3);

    morphoLayout->addWidget(new QLabel(tr("Connexity "), morphoGroupBox), 2, 0, Qt::AlignRight);
    _morphoConnexityComboBox = new QComboBox(morphoGroupBox);
    _morphoConnexityComboBox->addItem(tr("4"), QVariant(4));
    _morphoConnexityComboBox->addItem(tr("8"), QVariant(8));
    morphoLayout->addWidget(_morphoConnexityComboBox, 2, 1, Qt::AlignLeft);

    morphoLayout->addWidget(new QLabel(tr("Type Elt "), morphoGroupBox), 2, 2, Qt::AlignRight);
    _morphoTypeComboBox = new QComboBox(morphoGroupBox);
    _morphoTypeComboBox->addItem(tr("0"), QVariant(0));
   _morphoTypeComboBox ->addItem(tr("1"), QVariant(1));
   _morphoTypeComboBox ->addItem(tr("2"), QVariant(2));
    morphoLayout->addWidget(_morphoTypeComboBox, 2, 3, Qt::AlignLeft);


    _morphoPushButton = new QPushButton(QIcon(iconsPath+"add.png"), tr("Add"), morphoGroupBox);
    _morphoPushButton->setFixedWidth(80);
    morphoLayout->addWidget(_morphoPushButton, 2, 4, Qt::AlignRight);


    /* FITLERS DESCRIPTION LIST */
    _filtersTreeWidget = new QTreeWidget(this);
    _filtersTreeWidget->setRootIsDecorated(false);
    _filtersTreeWidget->setAlternatingRowColors(true);
    _filtersTreeWidget->setColumnCount(3);

    QStringList headers;
    headers << QString("Type") << QString("Name") << QString("Parameters");
    _filtersTreeWidget->setHeaderLabels(headers);
    filterTabLayout->addWidget(_filtersTreeWidget);


    /* HISTOGRAM TAB */
    /*QWidget *histoTabWidget = new QWidget(mainTab);
    QGridLayout *histoTabLayout = new QGridLayout(histoTabWidget);
    histoTabWidget->setLayout(histoTabLayout);
    mainTab->addTab(histoTabWidget, tr("Histogramme"));*/

    /* HISTOGRAM */
    /*_histogram = new CurveViewer(600, 600);
    _histogram->setMargin(50, 50);
    histoTabLayout->addWidget(_histogram, 0, 0, Qt::AlignCenter);
    _saveHistogramButton = new QPushButton(QIcon(iconsPath+"save.png"), tr("Save Histogram"));
    _saveHistogramButton->setFixedWidth(200);
    histoTabLayout->addWidget(_saveHistogramButton, 1, 0, Qt::AlignCenter);*/


    /* IMAGE VIEWER CONTROL */
    QWidget *controlIVWidget = new QWidget(this);
    QGridLayout *controlIVLayout = new QGridLayout(controlIVWidget);
    controlIVWidget->setLayout(controlIVLayout);
    mainLayout->addWidget(controlIVWidget, 2, 0);

    _saveImageButton = new QPushButton(QIcon(iconsPath+"save.png"), tr("Save Image"), this);
    _saveImageButton->setFixedWidth(150);

    QWidget *controlIV2Widget = new QWidget(controlIVWidget);
    QHBoxLayout *controlIV2Layout = new QHBoxLayout(controlIV2Widget);
    controlIV2Widget->setLayout(controlIV2Layout);
    controlIV2Widget->setFixedWidth(250);

    controlIV2Layout->addWidget(new QLabel(tr("Show : "), controlIVWidget));
    _showImage = new QCheckBox(tr(" image"), controlIVWidget);
    controlIV2Layout->addWidget(_showImage);
    _showMask = new QCheckBox(tr(" mask"), controlIVWidget);
    controlIV2Layout->addWidget(_showMask);

    controlIVLayout->addWidget(_saveImageButton, 0, 0, Qt::AlignLeft);
    controlIVLayout->addWidget(controlIV2Widget, 0, 1, Qt::AlignRight);

    /* BUTTONS */
    _okButton = new QPushButton(QIcon(iconsPath+"ok.png"), tr("Ok"), this);
    _closeButton = new QPushButton(QIcon(iconsPath+"close.png"), tr("Close"), this);
    _initButton = new QPushButton(tr("Init"), this);
    _initButton->setFixedHeight(35);
    _undoButton = new QPushButton(QIcon(iconsPath+"undo.png"), tr("Undo"), this);
    _undoButton->setShortcut(QKeySequence::Undo);

    mainLayout->addWidget(_closeButton, 3, 0, Qt::AlignLeft);
    mainLayout->addWidget(_initButton, 3, 0, Qt::AlignRight);
    mainLayout->addWidget(_undoButton, 3, 1, Qt::AlignLeft);
    mainLayout->addWidget(_okButton, 3, 1, Qt::AlignRight);

    resize(720, 800);
}

void FilterDialog::setupAction()
{
    /* PRE-TRAITEMENT */
    connect(_preTraitorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(preTraitorChanged(int)));
    connect(_preTraitorPushButton, SIGNAL(clicked()), this, SLOT(slotPreTraitorAdded()));

    /* TRAITEMENT */
    connect(_traitorComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(traitorChanged(int)));
    connect(_traitorPushButton, SIGNAL(clicked()), this, SLOT(slotTraitorAdded()));

    /* BISSEUILLAGE */
    connect(_minSeuillageSlider, SIGNAL(valueChanged(int)), this, SLOT(minSeuilSliderChanged(int)));
    connect(_minSeuillageSpinBox, SIGNAL(valueChanged(int)), this, SLOT(minSeuilSpinBoxChanged(int)));
    connect(_maxSeuillageSlider, SIGNAL(valueChanged(int)), this, SLOT(maxSeuilSliderChanged(int)));
    connect(_maxSeuillageSpinBox, SIGNAL(valueChanged(int)), this, SLOT(maxSeuilSpinBoxChanged(int)));
    connect(_ThresholdComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(BiseuillageChanged(int)));

    /* MORPHOLOGY */
    connect(_morphoComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(morphologyChanged(int)));
    connect(_morphoPushButton, SIGNAL(clicked()), this, SLOT(slotMorphologyAdded()));

    /* IMAGE VIEWER CONTROL */
    connect(_saveImageButton, SIGNAL(clicked()), this, SLOT(saveImage()));
    connect(_showImage, SIGNAL(clicked()), this, SLOT(showImage()));
    connect(_showMask, SIGNAL(clicked()), this, SLOT(showMask()));

    /* BUTTONS */
    connect(_okButton, SIGNAL(clicked()), this, SLOT(validRoutine()));
    connect(_initButton, SIGNAL(clicked()), this, SLOT(slotInit()));
    connect(_undoButton, SIGNAL(clicked()), this, SLOT(slotUndo()));
    connect(_closeButton, SIGNAL(clicked()), this, SLOT(slotQuit()));
    connect(this, SIGNAL(finished(int)), this, SLOT(quit(int)));
    //connect(_saveHistogramButton, SIGNAL(clicked()), this, SLOT(saveHistogram()));
}

/* -------------------------------------------------------------------------------------------------
     PROTECTED METHODS
   -------------------------------------------------------------------------------------------------*/

void FilterDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
    emit quit();
}

/* -------------------------------------------------------------------------------------------------
     PUBLIC SLOTS
   -------------------------------------------------------------------------------------------------*/

/* BUTTONS */

void FilterDialog::slotInit()
{
    emit reset();
}

void FilterDialog::slotUndo()
{
    emit undo();
}

void FilterDialog::slotQuit()
{
    close();
}

void FilterDialog::quit(int)
{
    close();
}

void FilterDialog::validRoutine()
{
    emit applyRoutine();
}

/*void FilterDialog::saveHistogram()
{
    QString fileName =
            QFileDialog::getSaveFileName(this,"Save As ",  tr("histogram.png"), tr("Images (*.png)"));
    if ( !fileName.isEmpty() )
    {
        QPixmap picture(*_histogram->pixmap());
        picture.save(fileName);
    }
}*/

void FilterDialog::saveImage()
{
    QString fileName =
            QFileDialog::getSaveFileName(this,"Save As ",  tr("image.png"), tr("Images (*.png)"));
    if ( !fileName.isEmpty() )
    {
        QPixmap picture = _imageViewer->getPixmap();
        picture.save(fileName);
    }
}

/* IMAGE VIEWER CONTROL */

void FilterDialog::showImage()
{
    emit showImage(_showImage->isChecked());
}

void FilterDialog::showMask()
{
    emit showMask(_showMask->isChecked());
}

/* PRE-TRAITEMENT */

void FilterDialog::preTraitorChanged(int item)
{
    int preTraitorFilter = _preTraitorComboBox->itemData(item).toInt();
    bool pitch = true, order = true;
    if (preTraitorFilter < 0)
    {
        pitch = false;
        order = false;
    }
    else if (preTraitorFilter < 2)
    {
        //order = false;
    }
    _pitchSpinBox->setEnabled(pitch);
    _orderSpinBox->setEnabled(order);
    if (pitch || order)
        _preTraitorPushButton->setEnabled(true);
    else
        _preTraitorPushButton->setEnabled(false);
}

void FilterDialog::slotPreTraitorAdded()
{
    int item = _preTraitorComboBox->itemData(_preTraitorComboBox->currentIndex()).toInt();
    float pitch = (float)_pitchSpinBox->value();
    float order = (float)_orderSpinBox->value();
    //stocke la valeur dans l'examen

    emit preTraitorAdded(item, pitch, order);

    _undoButton->setEnabled(true);
    _initButton->setEnabled(true);
    _okButton->setEnabled(true);
    _preTraitorComboBox->setCurrentIndex(0);
}

/* TRAITEMENT */

void FilterDialog::traitorChanged(int item)
{
    int traitorFilter = _traitorComboBox->itemData(item).toInt();
    bool addFlag = false, paramsFlag = false;
    if (traitorFilter > 0)
    {
        addFlag = true;
        if (traitorFilter == 12)
            paramsFlag = true;
    }

    _traitorPushButton->setEnabled(addFlag);
    _traitorIterationSpinBox->setEnabled(paramsFlag);
    _traitorOrderSpinBox->setEnabled(paramsFlag);
}

void FilterDialog::slotTraitorAdded()
{
    int item = _traitorComboBox->itemData(_traitorComboBox->currentIndex()).toInt();
    int iteration = _traitorIterationSpinBox->value();
    float order = (float)_traitorOrderSpinBox->value();

    emit traitorAdded(item, iteration, order);

    _undoButton->setEnabled(true);
    _initButton->setEnabled(true);
    _okButton->setEnabled(true);
    _traitorComboBox->setCurrentIndex(0);
}

/* BISSEUILLAGE */

void FilterDialog::BiseuillageChanged(int i){
    int item = _ThresholdComboBox->itemData(i).toInt();



    int coeff=_ThresholdSpinBox->value();
    double pourcent= _CoeffSpinBox->value();
    emit ThresholdAdded(item, coeff,pourcent);



}



        //cahngement par seuillage manuelle par le slider ou les spinbox
void FilterDialog::minSeuilSliderChanged(int val)
{
    _minSeuillageSpinBox->setValue(val);

    if (val > _maxSeuillageSlider->value())
        _maxSeuillageSlider->setValue(val);
}

void FilterDialog::minSeuilSpinBoxChanged(int val)
{
    _minSeuillageSlider->setValue(val);

    if (val > _maxSeuillageSlider->value())
        _maxSeuillageSlider->setValue(val);
    emit bisseuillageChanged(_minSeuillageSlider->value(), _maxSeuillageSlider->value());
    _initButton->setEnabled(true);
    _okButton->setEnabled(true);
}

void FilterDialog::maxSeuilSliderChanged(int val)
{
    _maxSeuillageSpinBox->setValue(val);

    if (val < _minSeuillageSlider->value())
        _minSeuillageSlider->setValue(val);
}

void FilterDialog::maxSeuilSpinBoxChanged(int val)
{
    _maxSeuillageSlider->setValue(val);
    if (val < _minSeuillageSlider->value())
        _minSeuillageSlider->setValue(val);

    emit bisseuillageChanged(_minSeuillageSlider->value(), _maxSeuillageSlider->value());
    _initButton->setEnabled(true);
    _okButton->setEnabled(true);
}

/* MORPHOLOGY */

void FilterDialog::morphologyChanged(int item)
{
    int morphoFilter = _morphoComboBox->itemData(item).toInt();
    int val = 1;
    bool flag = true, orderFlag = true;
    if (morphoFilter < 0)
    {
        val = 0;
        flag = orderFlag = false;
    }
    _morphoSpinBox->setValue(val);
    _morphoSpinBox->setEnabled(flag);
    _morphoConnexityComboBox->setEnabled(flag);
    _morphoTypeComboBox->setEnabled(flag);
    _morphoTypeStrucSpinBox->setEnabled(flag);
    _morphoPushButton->setEnabled(flag || orderFlag);
}

void FilterDialog::slotMorphologyAdded()
{
    int item = _morphoComboBox->itemData(_morphoComboBox->currentIndex()).toInt();
    int iteration = _morphoSpinBox->value();
    int connexity=_morphoConnexityComboBox
                  ->itemData(_morphoConnexityComboBox->currentIndex()).toInt();
    int type=_morphoTypeComboBox->itemData(_morphoTypeComboBox->currentIndex()).toInt();
    int size= _morphoTypeStrucSpinBox->value();
    int ModeThreshold=_ThresholdComboBox->itemData(_ThresholdComboBox->currentIndex()).toInt();
    int coeff=_ThresholdSpinBox->value();
    double pourcent=_CoeffSpinBox->value();

    emit morphologyAdded(item, iteration, connexity,type,size,ModeThreshold,coeff,pourcent);

    _morphoComboBox->setCurrentIndex(0);
    _undoButton->setEnabled(true);
    _initButton->setEnabled(true);
    _okButton->setEnabled(true);
}

