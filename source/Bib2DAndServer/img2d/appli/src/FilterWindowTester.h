#ifndef FILTERWINDOWTESTER_H
#define FILTERWINDOWTESTER_H

#include <QObject>
#include <FilterWindow.h>
#include <Examen.h>

class FilterWindowTester : public QObject {
    Q_OBJECT

public:
    FilterWindowTester(FilterWindow *w, Examen *exam) :
        _w(w),
        _exam(exam) {
        connect(_w, SIGNAL(accept()), this, SLOT(execFilter()));
    }

private slots:
    void execFilter();

private:
    FilterWindow *_w;
    Examen *_exam;
};

#endif // FILTERWINDOWTESTER_H
