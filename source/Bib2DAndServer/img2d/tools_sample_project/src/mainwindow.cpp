#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtGui>
#include <debug.h> // DO NOT INCLUDE ASSERT.H (no test support)
#include <iostream>

using namespace std;

/**
  \param parent Parent widget in Qt QObject hierarchy
  */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    for(int i = 1; i < 20; ++i) {
        ui->list->addItem(QString::number(factorielle(i)));
    }
}

int MainWindow::factorielle(int n) {
    eassert(n < 20);
    eassert(n >= 1);

    int res = 1;
    for (int i = 2; i < n+1; ++i)
        res *= i;
    return res;
}

MainWindow::~MainWindow()
{
    delete ui;
}
