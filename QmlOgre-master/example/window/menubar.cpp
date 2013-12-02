#include <QApplication>
#include <QDesktopWidget>

#include "../coral.hpp"
#include "menubar.hpp"
#include "view4boxes.hpp"
#include "../modules/dicomdialog/dicomBrowser.h"
#include "../modules/dicomdialog/previewExamen.h"

MenuBar::MenuBar(QMenuBar *parent) :
    QMenuBar(parent)
{
    createActions();
    createMenus();
}

void MenuBar::createActions()
{

    // Open action
    actionBrowse = new QAction(QIcon(":resources/images/open.png"), tr("&Browse"), this);
    //actionBrowse->setShortcut(QKeySequence::Browse);
    actionBrowse->setIconVisibleInMenu(true);
    actionBrowse->setStatusTip(tr("Browse a directory"));
    connect(actionBrowse, SIGNAL(triggered()), this, SLOT(slotBrowse()));

    // Open action
    actionOpen = new QAction(QIcon(":resources/images/open.png"), tr("&Open"), this);
    actionOpen->setShortcut(QKeySequence::Open);
    actionOpen->setIconVisibleInMenu(true);
    actionOpen->setStatusTip(tr("Open an existing file"));
    connect(actionOpen, SIGNAL(triggered()), this, SLOT(slotOpen()));

    // Save action
    actionSave = new QAction(QIcon(":resources/images/save.png"), tr("&Save"), this);
    actionSave->setShortcuts(QKeySequence::Save);
    actionSave->setIconVisibleInMenu(true);
    actionSave->setStatusTip(tr("Save a file"));
    connect(actionSave, SIGNAL(triggered()), this, SLOT(slotSave()));

    // Exit action
    actionExit = new QAction(QIcon(":/resources/images/exit.png"), tr("&Exit"), this);
    actionExit->setShortcuts(QKeySequence::Quit);
    actionExit->setIconVisibleInMenu(true);
    actionExit->setStatusTip(tr("Close the application"));
    connect(actionExit, SIGNAL(triggered()), parent()->parent(), SLOT(close()));

    // Dual screen action
    actionDualScreen = new QAction("Dual Screen", this); //QIcon(":/resources/images/dualscreen.png"), tr("&Dual Screen"), this);
    actionDualScreen->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_D));
    actionDualScreen->setIconVisibleInMenu(true);
    actionDualScreen->setStatusTip(tr("Separate 3D panel of the main window"));
    actionDualScreen->setCheckable(true);
    actionDualScreen->setChecked(false);
    actionDualScreen->setEnabled(true);
    connect(actionDualScreen, SIGNAL(triggered()), this, SLOT(slotDualScreen()));

    // Actions to change language
    actionFrench = new QAction(QIcon(":/resources/images/france.png"), tr("&French"), this);
    actionFrench->setIconVisibleInMenu(true);
    actionFrench->setStatusTip(tr("Change the language to French"));
    connect(actionFrench, SIGNAL(triggered()), this, SLOT(slotChangeLanguageToFrench()));

    actionEnglish = new QAction(QIcon(":/resources/images/usa.png"), tr("&English"), this);
    actionEnglish->setIconVisibleInMenu(true);
    actionFrench->setStatusTip(tr("Change the language to English"));
    connect(actionEnglish, SIGNAL(triggered()), this, SLOT(slotChangeLanguageToEnglish()));

    actionSpanish = new QAction(QIcon(":/resources/images/spain.png"), tr("&Spanish"), this);
    actionSpanish->setIconVisibleInMenu(true);
    actionFrench->setStatusTip(tr("Change the language to Spanish"));
    connect(actionSpanish, SIGNAL(triggered()), this, SLOT(slotChangeLanguageToSpanish()));

    // Actions to change window style
    actionStyleDefault = new QAction(QIcon(":/resources/images/skins.png"), tr("&Default"), this);
    actionStyleDefault->setIconVisibleInMenu(true);
    connect(actionStyleDefault, SIGNAL(triggered()), this, SLOT(slotStyleDefault()));

    actionStyle1 = new QAction(QIcon(":/resources/images/skins.png"), tr("&Global"), this);
    actionStyle1->setIconVisibleInMenu(true);
    connect(actionStyle1, SIGNAL(triggered()), this, SLOT(slotStyleGlobal()));

    actionStyle2 = new QAction(QIcon(":/resources/images/skins.png"), tr("&Windows 8"), this);
    actionStyle2->setIconVisibleInMenu(true);
    connect(actionStyle2, SIGNAL(triggered()), this, SLOT(slotStyleWindows8()));

    // Actions to change view modes
    actionView1 = new QAction(trUtf8("&View N°1"), this);
    actionView2 = new QAction(trUtf8("&View N°2"), this);
}

void MenuBar::createMenus() {
    fileMenu = addMenu(tr("&File"));
    fileMenu->addAction(actionBrowse);
    fileMenu->addAction(actionOpen);
    fileMenu->addAction(actionSave);
    fileMenu->addSeparator();
    fileMenu->addAction(actionExit);

    optionMenu = addMenu(tr("&Option"));
    optionMenu->addAction(actionDualScreen);

    viewMenu = addMenu(tr("&View"));
    viewMenu->addAction(actionView1);
    viewMenu->addAction(actionView2);

    language = optionMenu->addMenu(tr("Language"));
    language->setIcon(QIcon(":/resources/images/language.png"));
    language->addAction(actionFrench);
    language->addAction(actionEnglish);
    language->addAction(actionSpanish);

    skin = optionMenu->addMenu(tr("Skin"));
    skin->setIcon(QIcon(":/resources/images/skins.png"));
    skin->addAction(actionStyleDefault);
    skin->addAction(actionStyle1);
    skin->addAction(actionStyle2);
}


void MenuBar::slotBrowse()
{
    DicomBrowser * dicomBrowser = new DicomBrowser(this);

    dicomBrowser->show();
}



void MenuBar::slotOpen()
{
    PreviewExamen * previewExamen = new PreviewExamen(this);
    previewExamen->show();
}

void MenuBar::slotSave()
{
    QString fileName;
    fileName = QFileDialog::getSaveFileName(this, tr("Save"),
                                            QDir::currentPath (),
                                            tr("All files (*.*)"));
    if (fileName.isNull())
        return;

    m_projectFile = fileName;

    // Set current directory as the last one used.
    QFileInfo file(m_projectFile);
    QDir::setCurrent (file.path ());
    Coral::instance()->window()->setWindowTitle(file.fileName());
}

void MenuBar::slotDualScreen()
{
    View4Boxes *v = Coral::instance()->window()->getView4Boxes();

    if (!actionDualScreen->isChecked()) {
        if (qApp->desktop()->numScreens() == 2)
            v->remove8Boxes();
        else
            Coral::instance()->window()->closeSecondWindow();
        return;
    }

    if(qApp->desktop()->numScreens() == 2) {
        v->setup8Boxes();

        QRect w;
        w.setTopLeft(qApp->desktop()->availableGeometry(0).topLeft());
        w.setBottomRight(qApp->desktop()->availableGeometry(1).bottomRight());
        Coral::instance()->window()->setGeometry(w);
    } else {
        Coral::instance()->window()->createSecondWindow();
    }
}

QAction *MenuBar::getView1()
{
    return actionView1;
}

QAction *MenuBar::getView2()
{
    return actionView2;
}

void MenuBar::slotStyleDefault()

{
    // Set the current style in the host operative system
    Coral::instance()->window()->setStyleSheet(styleSheet());
}

void MenuBar::slotStyleGlobal()
{
    Coral::instance()->window()->putStyle1();
}

void MenuBar::slotStyleWindows8()
{
    Coral::instance()->window()->putStyle2();
}

void MenuBar::slotChangeLanguageToFrench()
{
    Coral::instance()->window()->changeLanguage("fr");
}

void MenuBar::slotChangeLanguageToEnglish()
{
    Coral::instance()->window()->changeLanguage("en");
}

void MenuBar::slotChangeLanguageToSpanish()
{
    Coral::instance()->window()->changeLanguage("es");
}

void MenuBar::retranslateUi(const QString &lang)
{
    if (lang == "fr") {
        fileMenu->menuAction()->setText(tr("&Fichier"));
        optionMenu->menuAction()->setText(tr("&Option"));
        viewMenu->menuAction()->setText(tr("&Affichage"));
        skin->menuAction()->setText(tr("Apparence"));
        language->menuAction()->setText(tr("Langues"));
        actionDualScreen->setText(tr("Double Ecran"));
        actionOpen->setText(tr("Ouvrir"));
        actionSave->setText(tr("Enregistrer"));
        actionExit->setText(tr("Quitter"));
        actionFrench->setText(tr("Francais"));
        actionEnglish->setText(tr("Anglais"));
        actionSpanish->setText(tr("Espagnol"));
        actionView1->setText(tr("Mode 1"));
        actionView2->setText(tr("Mode 2"));
        actionStyleDefault->setText(trUtf8("Par défaut"));
    }
    else if (lang == "es") {
        fileMenu->menuAction()->setText(tr("&Archivo"));
        optionMenu->menuAction()->setText(trUtf8("&Opción"));
        viewMenu->menuAction()->setText(tr("&Visualización"));
        skin->menuAction()->setText(tr("&Apariencia"));
        language->menuAction()->setText(tr("Idioma"));
        actionDualScreen->setText(tr("Pantalla doble"));
        actionOpen->setText(tr("&Abrir"));
        actionSave->setText(tr("&Guardar"));
        actionExit->setText(tr("&Salir"));
        actionFrench->setText(trUtf8("Francés"));
        actionEnglish->setText(tr("Ingles"));
        actionSpanish->setText(trUtf8("Español"));
        actionView1->setText(tr("Modo 1"));
        actionView2->setText(tr("Modo 2"));
        actionStyleDefault->setText(tr("Por defecto"));
    }

    else {  // English
        fileMenu->menuAction()->setText(tr("&File"));
        optionMenu->menuAction()->setText(tr("&Option"));
        viewMenu->menuAction()->setText(tr("&View"));
        skin->menuAction()->setText(tr("Skin"));
        language->menuAction()->setText(tr("Language"));
        actionDualScreen->setText(tr("Dual Screen"));
        actionOpen->setText(tr("Open"));
        actionSave->setText(tr("Save"));
        actionExit->setText(tr("Exit"));
        actionFrench->setText(tr("French"));
        actionEnglish->setText(tr("English"));
        actionSpanish->setText(tr("Spanish"));
        actionView1->setText(tr("View 1"));
        actionView2->setText(tr("View 2"));
        actionStyleDefault->setText(tr("Default"));
    }
}
