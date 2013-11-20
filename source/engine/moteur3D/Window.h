#ifndef WINDOW_H
#define WINDOW_H

#include "glwidget.h"
#include "myqlabel.h"
#include "QPushButton"
#include "../View/ImageTranscriber.h"
#include "../Algo/AlgoVolume.h"
#include "../Parser/ParserManager.h"

class GLWidget;

class Window : public QWidget
{
    Q_OBJECT

    public:
    Window(int argc, char** argv);
    GLWidget *getWidgetVolume();
    GLWidget *getWidgetCoupes();

    QPushButton *next;
    QPushButton *previous;

    //pour les acces a l'examen
    Examen *getExamen();
    void *setExamen(Examen *exam);
    //pour les acces a l'index
    int getIndex();
    void setIndex(int i);

    void refreshImage();
    void clearList();

    //Le ParserManager et les list servant à la recuperation
    //des liste de points pour l'affichage 3D
    ParserManager * parsMan;
    MiList<Point3D_Color_t<float> *> * pointsListTrans;
    MiList<Point3D_Color_t<float> *> * pointsListFront;
    MiList<Point3D_Color_t<float> *> * pointsListSagit;
    MiList<Point3D_Color_t<float> *> * pointsListCoupes;

    MiList<Point3D_Color_t<float> *> * pointsListVolume;

    private slots:
    void on_Previous_clicked();
    void on_Next_clicked();
    void on_Press(int x, int y);

    private:
    GLWidget *glWidgetVolume; //pour affichage du volume
    GLWidget *glWidgetCoupes; //pour affichage des coupes dans un plan 3D
    MyQlabel *image2D;        //pour affichage d'une coupe en 2D

    Examen *examen;
    int index;
};

#endif // WINDOW_H
