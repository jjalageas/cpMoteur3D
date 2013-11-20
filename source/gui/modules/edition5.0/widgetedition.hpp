#ifndef WIDGETEDITION_H
#define WIDGETEDITION_H

#include <QWidget>

namespace Ui {
class WidgetEdition;
}

class WidgetEdition : public QWidget
{
    Q_OBJECT

public:
    explicit WidgetEdition(QWidget *parent = 0);
    ~WidgetEdition();

private:
    Ui::WidgetEdition *ui;
};

#endif // WIDGETEDITION_H
