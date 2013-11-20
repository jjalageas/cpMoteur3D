#include <QApplication>
#include <QStackedWidget>
#include <QDockWidget>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextEdit>
#include <QLayout>
#include <QQueue>
#include <QDesktopWidget>

#include "mainwindow.hpp"
#include "modules/imageviewer/imageviewer.hpp"
#include "exampleapp.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Coral Project");
    setMinimumSize(400,600);
    setMouseTracking(true);
    _view = false;
    _translator = new QTranslator(this);
    _leftDock = new QDockWidget(this);
    _leftPanel = new DockPanel(_leftDock);

    // Trick to hide dock title bar
    QWidget* titleWidget = new QWidget(this);
    _leftDock->setTitleBarWidget(titleWidget);

    _menuBar = new MenuBar(this->menuBar());
    _view4Boxes = new View4Boxes(this);
    _leftPanel = new DockPanel;

    setMenuBar(_menuBar);
    _leftPanel->setup();
    setupLeftDock();
    setupCentralWidget();

    // Connect actions to change view modes
    connect(_menuBar->getView1(),SIGNAL(triggered()),this,SLOT(viewN1()));
    connect(_menuBar->getView2(),SIGNAL(triggered()),this,SLOT(viewN2()));
}

MainWindow::~MainWindow()
{
    delete _leftPanel;
    delete _leftDock;

    delete _view4Boxes;
    delete _centralWidgetLayout;
    delete _centralWidget;
    delete _menuBar;
}


void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if ((_leftPanel->pos().x() + event->pos().x())+100 > (_leftPanel->pos().x() + _leftPanel->width())){
        if (_view){
            if (_leftPanel->isOpaque()){
                _leftPanel->setOpaque(false);
            }
        }else{
            if (_leftPanel->isVisible()){
                //_leftPanel->setVisible(false);
            }
        }
    }else {
        if (_view){
            if (!_leftPanel->isOpaque()){
                _leftPanel->setOpaque(true);
            }
        }else{
            if (!_leftPanel->isVisible()){
                //_leftPanel->setVisible(true);
            }
        }
    }
}

void MainWindow::setupCentralWidget()
{
    ExampleApp *a = new ExampleApp();
    _centralWidget = QWidget::createWindowContainer(a);




    //new QWidget(this);
    /*_centralWidgetLayout = new QGridLayout(_centralWidget);
    _centralWidgetLayout->setSpacing(0);

    _view4Boxes = new View4Boxes(_centralWidget);


    QWidget *imageviwer2D_1 = new ImageViewer();
    QWidget *imageviwer2D_2 = new ImageViewer();
    QWidget *imageviwer2D_3 = new ImageViewer();




    QWidget *imageviwer3D  = QWidget::createWindowContainer(a);

    //
    //QWidget *imageviwer3D = new QWidget;         // 3D


    //    ---- ------just for testing -------------
    //    QWidget *widget1 = new QWidget(_view4Boxes);
    //    QWidget *widget2 = new QWidget(_view4Boxes);
    //    QWidget *widget3 = new QWidget(_view4Boxes);
    //    QWidget *widget4 = new QWidget(_view4Boxes);

    //    QGridLayout * l1 = new QGridLayout(widget1);
    //    QGridLayout * l2 = new QGridLayout(widget2);
    //    QGridLayout * l3 = new QGridLayout(widget3);
    //    QGridLayout * l4 = new QGridLayout(widget4);

    //    QTextEdit *t1 = new QTextEdit(widget1);
    //    QTextEdit *t2 = new QTextEdit(widget2);
    //    QTextEdit *t3 = new QTextEdit(widget3);
    //    QTextEdit *t4 = new QTextEdit(widget4);

    //    l1->addWidget(t1,0,0,1,1);
    //    l2->addWidget(t2,0,0,1,1);
    //    l3->addWidget(t3,0,0,1,1);
    //    l4->addWidget(t4,0,0,1,1);

    //    imageviwer2D_1->setObjectName("2D_1");
    //    imageviwer2D_2->setObjectName("2D_2");
    //    imageviwer2D_3->setObjectName("2D_3");
    //    imageviwer3D->setObjectName("3D");
    //    ---------------------------------------

    QQueue<QWidget *> queue;
    queue.enqueue(imageviwer2D_1);
    queue.enqueue(imageviwer2D_2);
    queue.enqueue(imageviwer2D_3);
    queue.enqueue(imageviwer3D);

    _view4Boxes->setVues(queue);
    _centralWidgetLayout->addWidget(_view4Boxes, 0, 0);*/
    this->setCentralWidget(_centralWidget);
}

void MainWindow::createSecondWindow()
{
    Qt::WindowFlags flags = 0;
    flags = Qt::Window;

    _secondWindow = new View4Boxes(*_view4Boxes, this);
    _secondWindow->setWindowFlags(flags);

    QPoint pos = _secondWindow->pos();
    if (pos.x() < 0)
        pos.setX(0);
    if (pos.y() < 0)
        pos.setY(0);

    _secondWindow->move(pos);
    _secondWindow->show();
}

void MainWindow::closeSecondWindow()
{
    _secondWindow->close();
}

View4Boxes *MainWindow::getView4Boxes()
{
    return _view4Boxes;
}

void MainWindow::setupLeftDock()
{
    _leftDock->setFeatures(QDockWidget::NoDockWidgetFeatures);
    _leftDock->setWidget(_leftPanel);
    this->addDockWidget(Qt::LeftDockWidgetArea,_leftDock);
}

void MainWindow::viewN1()
{
    _view = true;
    removeDockWidget(_leftDock);
    _leftPanel->setOpaque(false);
    _view4Boxes->setVues(_leftPanel);
}

void MainWindow::viewN2()
{
    _view = false;
    if (!_leftDock->isVisible()) {
        setupLeftDock();
        _leftPanel->setOpaque(true);
        _leftDock->show();
    }
}

void MainWindow::changeLanguage(const QString &lang)
{
    _currLang = lang;
    _translator->load(QString(":/resources/translations/coral_%1").arg(lang));
    qApp->installTranslator(_translator);
}

void MainWindow::retranslateUi(const QString &lang)
{
    if (lang == "fr")
        this->setWindowTitle(tr("Projet Coral"));
    else if (lang == "es")
        this->setWindowTitle(tr("Proyecto Coral"));
    else // English
        this->setWindowTitle(tr("Coral Project"));

    _menuBar->retranslateUi(lang);
    _leftPanel->retranslateUi(lang);
}

void MainWindow::switchTranslator(QTranslator& translator, const QString& filename)
{
    // remove the old translator
    qApp->removeTranslator(&translator);

    // load the new translator
    if(translator.load(filename))
        qApp->installTranslator(&translator);
}

void MainWindow::loadLanguage(const QString& lang)
{
    if(_currLang != lang)
    {
        _currLang = lang;
        QLocale locale = QLocale(_currLang);
        QLocale::setDefault(locale);
        switchTranslator(*_translator, QString(":resources/translations/coral_%1.qm").arg(lang));
    }
}

void MainWindow::changeEvent(QEvent* event)
{
    if(0 != event)
    {
        switch(event->type())
        {
        // this event is send if a translator is loaded
        case QEvent::LanguageChange:
            retranslateUi(_currLang);
            break;
            // this event is send, if the system language changes
        case QEvent::LocaleChange:
        {
            QString locale = QLocale::system().name();
            locale.truncate(locale.lastIndexOf('_'));
            loadLanguage(locale);
            break;
        }
        }
    }

    QMainWindow::changeEvent(event);
}

void MainWindow::putStyle1()
{
    QFile file(":resources/stylesheets/global.qss");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}

void MainWindow::putStyle2()
{
    QFile file(":resources/stylesheets/windows8.qss");

    if(file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QString style(file.readAll());
        this->setStyleSheet(style);
        file.close();
    }
}
