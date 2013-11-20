#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidget>

namespace Ui {
class MainWindow;
}

/**
\class MainWindow
\brief The graphical user interface of the program

This class displays the list of a few facto numbers
\author Nicolas Moreaud
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
    int factorielle(int n);

    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
