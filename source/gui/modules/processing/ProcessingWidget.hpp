#ifndef PROCESSINGWIDGET_H
#define PROCESSINGWIDGET_H
#include <QWidget>
#include <QMainWindow>

class ProcessingWidget : public QWidget {

public:
    ProcessingWidget(QWidget* widget);

private:
    QWidget* widget;
};

#endif // PROCESSINGWIDGET_H
