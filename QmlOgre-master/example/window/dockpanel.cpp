#include "dockpanel.hpp"
#include "wprocessing.hpp"
#include "wedition.hpp"
#include "wmanipulation.hpp"

using namespace std;

DockPanel::DockPanel(QWidget *parent, ExampleApp *_a) : QWidget(parent)
{
    _mainLayout = new QGridLayout(this);
    _mainLayout->setSpacing(6);
    _mainLayout->setContentsMargins(11, 11, 11, 11);
    a = _a;
}

DockPanel::~DockPanel()
{
}

void DockPanel::enterEvent(QEvent * event)
{
    setOpaque(true);
}
void DockPanel::leaveEvent(QEvent * event)
{
    setOpaque(false);
}

void DockPanel::setOpaque(bool opaque)
{
    _opaque = opaque;
    QGraphicsOpacityEffect * effect = new QGraphicsOpacityEffect(this);
    if (!opaque){
        effect->setOpacity(0.5);
    }else{
        effect->setOpacity(1);
    }
    this->setGraphicsEffect(effect);
}

void DockPanel::setup()
{
    setupTabUp();
    setupTabDown();
}

bool DockPanel::isOpaque(){
    return _opaque;
}

void DockPanel::retranslateUi(const QString &lang)
{
    if (lang == "fr") {
        _tabUp->setTabText(0, "Histogramme");
        _tabUp->setTabText(1, "Contraste");
        _tabUp->setTabText(2, "Algorithmes");
        _tabDown->setTabText(2, "Editeur");
    }
    else if (lang == "es") {
        _tabUp->setTabText(0, "Histograma");
        _tabUp->setTabText(1, "Contraste");
        _tabUp->setTabText(2, "Algoritmos");
        _tabDown->setTabText(2, "Editor");
    }
    else {  // English
        _tabUp->setTabText(0, "Histogram");
        _tabUp->setTabText(1, "Contrast");
        _tabUp->setTabText(2, "Algorithms");
        _tabDown->setTabText(2, "Editor");
    }

//    histoWidget->retranslateUi(lang);
//    contrasteWidget->retranslateUi(lang);
    _wProcessing->retranslateUi(lang);
    _wManipulation->retranslateUi(lang);
    _wEdition->retranslateUi(lang);
}

void DockPanel::setupTabUp()
{
    // Create main tab
    _tabUp = new QTabWidget(this);

    // Create each single tab
    _contrastWidget = new QWidget(_tabUp);
    QWidget *algoWidget = new QWidget(_tabUp);

    // Create single widgets
    _histoWidget = new WidgetHisto(":/test/pictures/lena.jpg", _tabUp);
    //new ContrastWidget(contrastWidget);
    _wProcessing = new WProcessing(algoWidget);

    // Add each tab in the main tab widget
    _tabUp->addTab(_histoWidget,     tr("Histogram"));
    _tabUp->addTab(_contrastWidget, tr("Contrast"));
    _tabUp->addTab(algoWidget,      tr("Algorithms"));

    // Add first tab to main widget in dock panel
    _mainLayout->addWidget(_tabUp, 0, 0, 1, 1);
}

void DockPanel::setupTabDown()
{
    // Create main tab
    _tabDown = new QTabWidget(this);

    // Create single widget
    QWidget *editorWidget = new QWidget(_tabDown);

    // Create tabs
    _wEdition = new WEdition(editorWidget);
    _wManipulation = new WManipulation(_tabDown, a);

    // Add each tab in the main tab widget
    _tabDown->addTab(editorWidget, tr("Editor"));

    // Add second tab to main widget in dock panel
    _mainLayout->addWidget(_tabDown, 1, 0, 1, 1);
}

