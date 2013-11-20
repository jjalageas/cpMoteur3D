#include "edgedetection.hpp"
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

EdgeDetection::EdgeDetection(QWidget *parent) : QVBoxLayout()
{
    font.setBold(true);

    iteration = new QLabel("Iteration");
    order = new QLabel("Order");
    label = new QLabel("Edge Detection");
    label->setFont(font);

    comboBox = new QComboBox();
    comboBox->setFixedWidth(COMBOBOX_WIDTH);
    comboBox->addItem("Edge Detection 1");
    comboBox->addItem("Edge Detection 2");

    spinBox1 = new QSpinBox();
    spinBox1->setRange(0, 1000);
    spinBox1->setSingleStep(0);
    spinBox1->setValue(1);
    spinBox1->setFixedWidth(SPINBOX_WIDTH);

    spinBox2 = new QDoubleSpinBox();
    spinBox2->setRange(0, 1000);
    spinBox2->setSingleStep(0.05);
    spinBox2->setValue(0);
    spinBox2->setFixedWidth(SPINBOX_WIDTH);

    hbox = new QHBoxLayout();
    hbox->addWidget(iteration, 0, Qt::AlignLeft);
    hbox->addWidget(spinBox1, 10, Qt::AlignLeft);
    hbox->addWidget(order, 0, Qt::AlignLeft);
    hbox->addWidget(spinBox2, 10, Qt::AlignLeft);

    button = new QPushButton("Add", parent);
    button->setFixedWidth(ADDBUTTON_WIDTH);

    this->addWidget(label);
    this->addWidget(comboBox);
    this->addLayout(hbox);
    this->addWidget(button, 0, Qt::AlignRight);
}

void EdgeDetection::retranslateUi(const QString &lang)
{
    if (lang == "fr"){
        button->setText(tr("Ajouter"));
        iteration->setText(tr("Itération"));
        order->setText(tr("Ordre"));
        label->setText(tr("Détection de contours"));
        comboBox->setItemText(0,"Détection de contours 1");
        comboBox->setItemText(1,"Détection de contours 2");
    }
    else if (lang == "es"){
        button->setText(tr("Añadir"));
        iteration->setText(tr("Iteración"));
        order->setText(tr("Orden"));
        label->setText(tr("Detección de bordes"));
        comboBox->setItemText(0,"Detección de bordes 1");
        comboBox->setItemText(1,"Detección de bordes 2");
    }
    else { // English
        button->setText(tr("Add"));
        iteration->setText(tr("Iteration"));
        order->setText(tr("Order"));
        label->setText(tr("Edge Detection"));
        comboBox->setItemText(0,"Edge Detection 1");
        comboBox->setItemText(1,"Edge Detection 2");
    }
}