#include "morphology.hpp"
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
#define SMALL_COMBOBOX_WIDTH 70

Morphology::Morphology(QWidget *parent) : QVBoxLayout()
{
    font.setBold(true);

    connexity = new QLabel("Connexity");
    type = new QLabel("Type Elt.");
    size = new QLabel("Size Elt.");
    iteration = new QLabel("Iteration");
    morphology = new QLabel("Morphology NVG");
    morphology->setFont(font);

    comboBox = new QComboBox();
    comboBox->setFixedWidth(COMBOBOX_WIDTH);
    comboBox->addItem("Morphology 1");
    comboBox->addItem("Morphology 2");

    spinBox1 = new QDoubleSpinBox();
    spinBox1->setRange(0, 1000);
    spinBox1->setSingleStep(1);
    spinBox1->setValue(0);
    spinBox1->setFixedWidth(SPINBOX_WIDTH);

    spinBox2 = new QDoubleSpinBox();
    spinBox2->setRange(0, 1000);
    spinBox2->setSingleStep(1);
    spinBox2->setValue(0);
    spinBox2->setFixedWidth(SPINBOX_WIDTH);

    comboBox1 = new QComboBox();
    comboBox1->setFixedWidth(SMALL_COMBOBOX_WIDTH);
    comboBox1->addItem("0");
    comboBox1->addItem("1");
    comboBox1->addItem("2");
    comboBox1->addItem("3");
    comboBox1->addItem("4");

    comboBox2 = new QComboBox();
    comboBox2->setFixedWidth(SMALL_COMBOBOX_WIDTH);
    comboBox2->addItem("0");
    comboBox2->addItem("1");
    comboBox2->addItem("2");

    hbox1 = new QHBoxLayout();
    hbox1->addWidget(iteration, 0, Qt::AlignLeft);
    hbox1->addWidget(spinBox1, 10, Qt::AlignLeft);
    hbox1->addWidget(size, 0, Qt::AlignLeft);
    hbox1->addWidget(spinBox2, 10, Qt::AlignLeft);

    hbox2 = new QHBoxLayout();
    hbox2->addWidget(connexity, 0, Qt::AlignLeft);
    hbox2->addWidget(comboBox1, 10, Qt::AlignLeft);
    hbox2->addWidget(type, 0, Qt::AlignLeft);
    hbox2->addWidget(comboBox2, 10, Qt::AlignLeft);

    button = new QPushButton("Add", parent);
    button->setFixedWidth(ADDBUTTON_WIDTH);

    this->addWidget(morphology);
    this->addWidget(comboBox);
    this->addLayout(hbox1);
    this->addLayout(hbox2);
    this->addWidget(button, 0, Qt::AlignRight);
}

void Morphology::retranslateUi(const QString &lang)
{
    if (lang == "fr") {
        connexity->setText(tr("Connexité"));
        type->setText(tr("Type Elt."));
        size->setText(tr("Taille Elt."));
        iteration->setText(tr("Itération"));
        morphology->setText(tr("Morphologie NVG"));
        comboBox->setItemText(0,"Morphologie 1");
        comboBox->setItemText(1,"Morphologie 2");
        button->setText(tr("Ajouter"));
    }
    else if (lang == "es") {
        connexity->setText(tr("Conexidad"));
        type->setText(tr("Tipo Elt."));
        size->setText(tr("Tamaño Elt."));
        iteration->setText(tr("Iteración"));
        morphology->setText(tr("Morfología NVG"));
        comboBox->setItemText(0,"Morfología 1");
        comboBox->setItemText(1,"Morfología 2");
        button->setText(tr("Añadir"));
    }
    else { // English
        connexity->setText(tr("Connexity"));
        type->setText(tr("Type Elt."));
        size->setText(tr("Size Elt."));
        iteration->setText(tr("Iteration"));
        morphology->setText(tr("Morphology NVG"));
        comboBox->setItemText(0,"Morphology 1");
        comboBox->setItemText(1,"Morphology 2");
        button->setText(tr("Add"));
    }
}