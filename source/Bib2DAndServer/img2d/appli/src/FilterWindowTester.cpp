#include "FilterWindowTester.h"
#include <Filter2d.h>
#include <iostream>
#include <typeinfo>
#include <SliceViewer.h>

using namespace std;

void
FilterWindowTester::execFilter() {
    if (_w->getFilter().canApply() == true) {
        cout << "Ok : je peux appliquer " << _w->getFilter().getName() << endl;
        cout << "Donc je le fais sur tout l'exam!!!! XD " << endl;
        try {
            Filter2D& f2d = dynamic_cast<Filter2D&>(_w->getFilter());
            cout << "C'est un filtre 2d." << endl;
            Examen *newExam = new Examen(*_exam);
            f2d.apply(*newExam, CORONAL);
            cout << "Je l'ai appliqué, la preuve en direct : " << endl;
            SliceViewer *viewer = new SliceViewer();
            viewer->setExamen(newExam);
            viewer->show();
        }
        catch(std::bad_cast exp) {
            cout << "C'est un filtre 3d. J'ai la flemme, je fais rien." << endl;
        }
    }
    else {
        cout << "Bouh, je sais pas appliquer " << _w->getFilter().getName() << endl;
    }
}
