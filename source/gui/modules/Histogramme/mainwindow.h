#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "panelhisto.h"
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    PanelHisto f;
    QTabWidget* tabWidget;
public:
    explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
