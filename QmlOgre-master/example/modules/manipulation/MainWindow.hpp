#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

/**
 * @class MainWindow
 * @brief Fenetre principale contenant le widget Manipulation2D3D.
 */
class MainWindow : public QMainWindow
{
public:
    /**
     * @brief Constructeur de la classe MainWindow.
     * C'est une fenêtre contenant le widget Manipulation2D3D.
     * @param pas de paramètres.
     * @return .
    */
    MainWindow();
    /**
     * @brief Construit et affiche le module Manipulation2D3D.
     * @param MainWindow* const m -> Fenêtre dans laquelle on affiche le widget.
     * @return .
    */
    void displayWidgetManipulation2D3D(QWidget* w);
    /**
     * @brief Permet de créer un style à notre widget, à l'aide du language css.
     * @param pas de paramètres.
     * @return .
    */
    QString style();
private:

};

#endif // MAINWINDOW_H
