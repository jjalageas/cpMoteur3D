#include "ProcessingWidget.hpp"
#include <QWidget>
#include <QLabel>
#include <QFont>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QTableWidget>
#include <QHeaderView>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#define MARGIN 12
#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 800
#define COMBOBOX_WIDTH 300
#define SMALL_COMBOBOX_WIDTH 70
#define SPINBOX_WIDTH 75
#define ADDBUTTON_WIDTH 50
#define BUTTON_WIDTH_MEDIUM 80
#define HLAYOUT_HEIGHT 50


ProcessingWidget::ProcessingWidget(QWidget* widget) {

    QVBoxLayout *mainLayout = new QVBoxLayout();

    QTabWidget *tab = new QTabWidget();
    tab->setGeometry(MARGIN, MARGIN, SCREEN_WIDTH - 2 * MARGIN, SCREEN_HEIGHT/2 - 2 * MARGIN);

    // Tabs placeholders
    QWidget *pretreatments = new QWidget();
    QWidget *segmentation = new QWidget();
    QWidget *posttreatments = new QWidget();
    QWidget *squeletization = new QWidget();

    // PreTreatments

    // Filtering
    QComboBox *comboBox1 = new QComboBox();
    comboBox1->setFixedWidth(COMBOBOX_WIDTH);
    comboBox1->addItem("Filter 1");
    comboBox1->addItem("Filter 2");

    QDoubleSpinBox *spinBox1_1 = new QDoubleSpinBox();
    spinBox1_1->setRange(0, 1000);
    spinBox1_1->setSingleStep(0.05);
    spinBox1_1->setValue(0);
    spinBox1_1->setFixedWidth(SPINBOX_WIDTH);

    QDoubleSpinBox *spinBox1_2 = new QDoubleSpinBox();
    spinBox1_2->setRange(0, 1000);
    spinBox1_2->setSingleStep(0.05);
    spinBox1_2->setValue(0);
    spinBox1_2->setFixedWidth(SPINBOX_WIDTH);

    QPushButton *button1 = new QPushButton("Add", this);
    button1->setFixedWidth(ADDBUTTON_WIDTH);

    // Edge Detection
    QComboBox *comboBox2 = new QComboBox();
    comboBox2->setFixedWidth(COMBOBOX_WIDTH);
    comboBox2->addItem("Edge Detection 1");
    comboBox2->addItem("Edge Detection 2");

    QSpinBox *spinBox2_1 = new QSpinBox();
    spinBox2_1->setRange(0, 1000);
    spinBox2_1->setSingleStep(0);
    spinBox2_1->setValue(1);
    spinBox2_1->setFixedWidth(SPINBOX_WIDTH);

    QDoubleSpinBox *spinBox2_2 = new QDoubleSpinBox();
    spinBox2_2->setRange(0, 1000);
    spinBox2_2->setSingleStep(0.05);
    spinBox2_2->setValue(0);
    spinBox2_2->setFixedWidth(SPINBOX_WIDTH);

    QPushButton *button2 = new QPushButton("Add", this);
    button2->setFixedWidth(ADDBUTTON_WIDTH);

    // Morphology
    QComboBox *comboBox3 = new QComboBox();
    comboBox3->setFixedWidth(COMBOBOX_WIDTH);
    comboBox3->addItem("Morphology 1");
    comboBox3->addItem("Morphology 2");

    QDoubleSpinBox *spinBox3_1 = new QDoubleSpinBox();
    spinBox3_1->setRange(0, 1000);
    spinBox3_1->setSingleStep(1);
    spinBox3_1->setValue(0);
    spinBox3_1->setFixedWidth(SPINBOX_WIDTH);

    QDoubleSpinBox *spinBox3_2 = new QDoubleSpinBox();
    spinBox3_2->setRange(0, 1000);
    spinBox3_2->setSingleStep(1);
    spinBox3_2->setValue(0);
    spinBox3_2->setFixedWidth(SPINBOX_WIDTH);

    QComboBox *comboBox4 = new QComboBox();
    comboBox4->setFixedWidth(SMALL_COMBOBOX_WIDTH);
    comboBox4->addItem("0");
    comboBox4->addItem("1");
    comboBox4->addItem("2");
    comboBox4->addItem("3");
    comboBox4->addItem("4");

    QComboBox *comboBox5 = new QComboBox();
    comboBox5->setFixedWidth(SMALL_COMBOBOX_WIDTH);
    comboBox5->addItem("0");
    comboBox5->addItem("1");
    comboBox5->addItem("2");

    QPushButton *button3 = new QPushButton("Add", this);
    button3->setFixedWidth(ADDBUTTON_WIDTH);

    // Font styling
    QFont font;
    font.setBold(true);

    // Labels
    QLabel *label1 = new QLabel("Filtering");
    QLabel *label2 = new QLabel("Edge Detection");
    QLabel *label3 = new QLabel("Morphology NVG");
    label1->setFont(font);
    label2->setFont(font);
    label3->setFont(font);

    QLabel *pitch = new QLabel("Pitch");
    QLabel *order1 = new QLabel("Order");
    QLabel *order2 = new QLabel("Order");
    QLabel *iteration1 = new QLabel("Iteration");
    QLabel *iteration2 = new QLabel("Iteration");
    QLabel *size = new QLabel("Size Elt.");
    QLabel *connexity = new QLabel("Connexity");
    QLabel *type = new QLabel("Type Elt.");

    // Layouts
    QHBoxLayout *hbox1 = new QHBoxLayout();
    hbox1->addWidget(pitch, 0, Qt::AlignLeft);
    hbox1->addWidget(spinBox1_1, 10, Qt::AlignLeft);
    hbox1->addWidget(order1, 0, Qt::AlignLeft);
    hbox1->addWidget(spinBox1_2, 10, Qt::AlignLeft);

    QHBoxLayout *hbox2 = new QHBoxLayout();
    hbox2->addWidget(iteration1, 0, Qt::AlignLeft);
    hbox2->addWidget(spinBox2_1, 10, Qt::AlignLeft);
    hbox2->addWidget(order2, 0, Qt::AlignLeft);
    hbox2->addWidget(spinBox2_2, 10, Qt::AlignLeft);

    QHBoxLayout *hbox3 = new QHBoxLayout();
    hbox3->addWidget(iteration2, 0, Qt::AlignLeft);
    hbox3->addWidget(spinBox3_1, 10, Qt::AlignLeft);
    hbox3->addWidget(size, 0, Qt::AlignLeft);
    hbox3->addWidget(spinBox3_2, 10, Qt::AlignLeft);

    QHBoxLayout *hbox4 = new QHBoxLayout();
    hbox4->addWidget(connexity, 0, Qt::AlignLeft);
    hbox4->addWidget(comboBox4, 10, Qt::AlignLeft);
    hbox4->addWidget(type, 0, Qt::AlignLeft);
    hbox4->addWidget(comboBox5, 10, Qt::AlignLeft);

    QVBoxLayout *vbox1 = new QVBoxLayout();
    // Filtering
    vbox1->addWidget(label1);
    vbox1->addWidget(comboBox1);
    vbox1->addLayout(hbox1);
    vbox1->addWidget(button1, 0, Qt::AlignRight);
    // Edge Detection
    vbox1->addWidget(label2);
    vbox1->addWidget(comboBox2);
    vbox1->addLayout(hbox2);
    vbox1->addWidget(button2, 0, Qt::AlignRight);
    // Morphology
    vbox1->addWidget(label3);
    vbox1->addWidget(comboBox3);
    vbox1->addLayout(hbox3);
    vbox1->addLayout(hbox4);
    hbox4->addWidget(button3, 0, Qt::AlignRight);

    pretreatments->setLayout(vbox1);

    tab->addTab(pretreatments, "Pre-treatments");
    tab->addTab(segmentation, "Segmentation");
    tab->addTab(posttreatments, "Post-treatments");
    tab->addTab(squeletization, "Squeletization");

    //list
    QTableWidget *tableWidget = new QTableWidget();
    tableWidget->setColumnCount(3);
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Type" << "Name" << "Parameters");
    tableWidget->setShowGrid(false);
    tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //insert QTableWidgetItems into tableWidget


    // Buttons
    QPushButton *buttonApply = new QPushButton("Apply", this);
    buttonApply->setFixedWidth(BUTTON_WIDTH_MEDIUM);
    QPushButton *buttonUndo = new QPushButton("Undo", this);
    buttonUndo->setFixedWidth(BUTTON_WIDTH_MEDIUM);
    QPushButton *buttonRemove = new QPushButton("Remove", this);
    buttonRemove->setFixedWidth(BUTTON_WIDTH_MEDIUM);
    QPushButton *buttonExport = new QPushButton("Export", this);
    buttonExport->setFixedWidth(BUTTON_WIDTH_MEDIUM);

    QHBoxLayout *hbox5 = new QHBoxLayout();
    hbox5->addWidget(buttonApply, 0, Qt::AlignCenter);
    hbox5->addWidget(buttonUndo, 0, Qt::AlignCenter);
    hbox5->addWidget(buttonRemove, 0, Qt::AlignCenter);
    hbox5->addWidget(buttonExport, 0, Qt::AlignCenter);

    mainLayout->addWidget(tab);
    mainLayout->addWidget(tableWidget);
    mainLayout->addLayout(hbox5);
    widget->setLayout(mainLayout);

}
