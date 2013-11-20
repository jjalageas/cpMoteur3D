#ifndef WPROCESSING_H
#define WPROCESSING_H
#include <QWidget>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QPushButton>
#include "filter.hpp"
#include "edgedetection.hpp"
#include "morphology.hpp"

class WProcessing : public QWidget {

public:
    WProcessing(QWidget* widget);
    void retranslateUi(const QString& lang);

private:
    QWidget *widget;
    QWidget *operations;
    Filter *filters;
    Morphology *morphology;
    EdgeDetection *edgeDetection;
    QVBoxLayout *vbox1;
    QHBoxLayout *hbox;
    QVBoxLayout *mainLayout;
    QTableWidget *tableWidget;
    QPushButton *buttonApply;
    QPushButton *buttonUndo;
    QPushButton *buttonRemove;
    QPushButton *buttonExport;
};

#endif // WPROCESSING_H
