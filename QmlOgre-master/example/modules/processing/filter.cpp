#include "filter.hpp"
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#define SPINBOX_WIDTH 75
#define COMBOBOX_WIDTH 300
#define ADDBUTTON_WIDTH 50

Filter::Filter(QWidget *parent) : QVBoxLayout()
{
    font.setBold(true);

    pitch = new QLabel("Pitch");
    order = new QLabel("Order");
    filtering = new QLabel("Filtering");
    filtering->setFont(font);

    comboBox = new QComboBox();
    comboBox->setFixedWidth(COMBOBOX_WIDTH);
    comboBox->addItem("Filter 1");
    comboBox->addItem("Filter 2");

    spinBox1 = new QDoubleSpinBox();
    spinBox1->setRange(0, 1000);
    spinBox1->setSingleStep(0.05);
    spinBox1->setValue(0);
    spinBox1->setFixedWidth(SPINBOX_WIDTH);

    spinBox2 = new QDoubleSpinBox();
    spinBox2->setRange(0, 1000);
    spinBox2->setSingleStep(0.05);
    spinBox2->setValue(0);
    spinBox2->setFixedWidth(SPINBOX_WIDTH);

    hbox = new QHBoxLayout();
    hbox->addWidget(pitch, 0, Qt::AlignLeft);
    hbox->addWidget(spinBox1, 10, Qt::AlignLeft);
    hbox->addWidget(order, 0, Qt::AlignLeft);
    hbox->addWidget(spinBox2, 10, Qt::AlignLeft);

    button = new QPushButton("Add", parent);
    button->setFixedWidth(ADDBUTTON_WIDTH);

    this->addWidget(filtering);
    this->addWidget(comboBox);
    this->addLayout(hbox);
    this->addWidget(button, 0, Qt::AlignRight);
}

void Filter::retranslateUi(const QString &lang)
{
    if (lang == "fr"){
        button->setText(tr("Ajouter"));
        pitch->setText(tr("Pas"));
        order->setText(tr("Ordre"));
        filtering->setText(tr("Filtrage"));
        comboBox->setItemText(0,"Filtre 1");
        comboBox->setItemText(1,"Filtre 2");
    }
    else if (lang == "es"){
        button->setText(tr("Añadir"));
        pitch->setText(tr("Modular"));
        order->setText(tr("Orden"));
        filtering->setText(tr("Filtración"));
        comboBox->setItemText(0,"Filtro 1");
        comboBox->setItemText(1,"Filtro 2");
    }
    else { // English
        button->setText(tr("Add"));
        pitch->setText(tr("Pitch"));
        order->setText(tr("Order"));
        filtering->setText(tr("Filtering"));
        comboBox->setItemText(0,"Filter 1");
        comboBox->setItemText(1,"Filter 2");
    }
}
