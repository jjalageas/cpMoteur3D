#include "widgetedition.hpp"
#include "widgetedition.ui"

WidgetEdition::WidgetEdition(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WidgetEdition)
{
    ui->setupUi(this);
}

WidgetEdition::~WidgetEdition()
{
    delete ui;
}
