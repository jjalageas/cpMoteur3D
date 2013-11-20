#include "mainwindow.h"
#include "pannelButtons.h"
#include "ui_mainwindow.h"
#include "general.h"
#include "fenetre.h"

#include <QPainter>
#include <QHBoxLayout>
#include <iostream>
#include <QTabWidget>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


   QWidget *g = new General();
   QWidget *g2 = new QWidget();

   tabWidget = new QTabWidget();

   tabWidget->addTab(g,"Histogramme");
   tabWidget->addTab(g2,"Courbe de contraste");

   setCentralWidget(tabWidget);
}


MainWindow::~MainWindow()
{
    delete ui;
}


