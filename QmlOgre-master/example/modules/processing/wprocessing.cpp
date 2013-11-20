#include "wprocessing.hpp"
#include "filter.hpp"
#include "edgedetection.hpp"
#include "morphology.hpp"
#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QScrollArea>

#define BUTTON_WIDTH_MEDIUM 80

WProcessing::WProcessing(QWidget* widget)
{
    vbox1 = new QVBoxLayout();
    filters = new Filter(this);
    edgeDetection = new EdgeDetection(this);
    morphology = new Morphology(this);
    vbox1->addLayout(filters);
    vbox1->addLayout(edgeDetection);
    vbox1->addLayout(morphology);

    // Operations placeholder
    operations = new QWidget();
    operations->setLayout(vbox1);

    // List
    tableWidget = new QTableWidget();
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Type" << "Name" << "Parameters");
    tableWidget->setShowGrid(false);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // Insert QTableWidgetItems into TableWidget

    // Buttons
    buttonApply = new QPushButton("Apply", this);
    buttonApply->setFixedWidth(BUTTON_WIDTH_MEDIUM);
    buttonUndo = new QPushButton("Undo", this);
    buttonUndo->setFixedWidth(BUTTON_WIDTH_MEDIUM);
    buttonRemove = new QPushButton("Remove", this);
    buttonRemove->setFixedWidth(BUTTON_WIDTH_MEDIUM);
    buttonExport = new QPushButton("Export", this);
    buttonExport->setFixedWidth(BUTTON_WIDTH_MEDIUM);

    hbox = new QHBoxLayout();
    hbox->addWidget(buttonApply, 0, Qt::AlignCenter);
    hbox->addWidget(buttonUndo, 0, Qt::AlignCenter);
    hbox->addWidget(buttonRemove, 0, Qt::AlignCenter);
    hbox->addWidget(buttonExport, 0, Qt::AlignCenter);

    mainLayout = new QVBoxLayout();
    mainLayout->addWidget(operations);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(hbox);
    widget->setLayout(mainLayout);
}

void WProcessing::retranslateUi(const QString &lang)
{
    if (lang == "fr"){
        buttonApply->setText(tr("Appliquer"));
        buttonUndo->setText(tr("Annuler"));
        buttonRemove->setText(tr("Supprimer"));
        buttonExport->setText(tr("Exporter"));
        tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Type"));
        tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Nom"));
        tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Paramètres"));
    }
    else if (lang == "es"){
        buttonApply->setText(tr("Aplicar"));
        buttonUndo->setText(tr("Deshacer"));
        buttonRemove->setText(tr("Suprimir"));
        buttonExport->setText(tr("Exportar"));
        tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Tipo"));
        tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Nombre"));
        tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Parámetros"));
    }
    else { // English
        buttonApply->setText(tr("Apply"));
        buttonUndo->setText(tr("Undo"));
        buttonRemove->setText(tr("Remove"));
        buttonExport->setText(tr("Export"));
        tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem("Type"));
        tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem("Name"));
        tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem("Parameters"));
    }

    filters->retranslateUi(lang);
    morphology->retranslateUi(lang);
    edgeDetection->retranslateUi(lang);
}
