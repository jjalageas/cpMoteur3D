#include "MainWindow.hpp"

#define SCREEN_SIZE_W 500
#define SCREEN_SIZE_H 300

MainWindow::MainWindow() {
    this->setGeometry(0,0,SCREEN_SIZE_W,SCREEN_SIZE_H);
    this->setStyleSheet(style());
    displayWidgetManipulation2D3D(this);
}

void MainWindow::displayWidgetManipulation2D3D(QWidget* w) {

    // 1 : Créer le QTabWidget
    QTabWidget *tab = new QTabWidget(w);

    this->setCentralWidget(tab);

    // 2 : Créer les pages, en utilisant un widget parent pour contenir
    // chacune des pages
    QWidget *manip2D = new QWidget();
    QWidget *manip3D = new QWidget();

    // 3 : Créer le contenu des pages de widgets

    //page 1
    QSpinBox *spinx = new QSpinBox();
    QSpinBox *spiny = new QSpinBox();
    QSpinBox *spinz = new QSpinBox();

    QComboBox *combobox1 = new QComboBox();
    combobox1->addItem(tr("Toutes les vues 2D + moteur 3D"));
    combobox1->addItem(tr("Une vue 2D + moteur 3D"));
    combobox1->addItem(tr("Une vue 2D"));
    combobox1->addItem(tr("Moteur 3D"));

    QLabel *labelx = new QLabel(tr("x : "));
    QLabel *labely = new QLabel(tr("y : "));
    QLabel *labelz = new QLabel(tr("z : "));

    QVBoxLayout *vbox1 = new QVBoxLayout();
    QHBoxLayout *hbox1 = new QHBoxLayout();
    QHBoxLayout *hbox2 = new QHBoxLayout();
    QHBoxLayout *hbox3 = new QHBoxLayout();

    hbox1->addWidget(labelx);
    hbox1->addWidget(spinx);
    vbox1->addLayout(hbox1);

    hbox2->addWidget(labely);
    hbox2->addWidget(spiny);
    vbox1->addLayout(hbox2);

    hbox3->addWidget(labelz);
    hbox3->addWidget(spinz);
    vbox1->addLayout(hbox3);

    vbox1->addWidget(combobox1);

    manip2D->setLayout(vbox1);

    //page 2
    QSpinBox *spinTextureX = new QSpinBox();
    QSpinBox *spinTextureY = new QSpinBox();
    QSpinBox *spinTextureZ = new QSpinBox();

    QLabel *labelTextureX = new QLabel(tr("Texture x : "));
    QLabel *labelTextureY = new QLabel(tr("Texture y : "));
    QLabel *labelTextureZ = new QLabel(tr("Texture z : "));

    QVBoxLayout *vbox2 = new QVBoxLayout();
    QHBoxLayout *hbox4 = new QHBoxLayout();
    QHBoxLayout *hbox5 = new QHBoxLayout();
    QHBoxLayout *hbox6 = new QHBoxLayout();
    QHBoxLayout *hbox7 = new QHBoxLayout();

    hbox4->addWidget(labelTextureX);
    hbox4->addWidget(spinTextureX);
    vbox2->addLayout(hbox4);

    hbox5->addWidget(labelTextureY);
    hbox5->addWidget(spinTextureY);
    vbox2->addLayout(hbox5);

    hbox6->addWidget(labelTextureZ);
    hbox6->addWidget(spinTextureZ);
    vbox2->addLayout(hbox6);

    QCheckBox *image = new QCheckBox(tr("Image"));
    QCheckBox *mask = new QCheckBox(tr("Masque"));
    hbox7->addWidget(image);
    hbox7->addWidget(mask);

    vbox2->addLayout(hbox7);

    QComboBox *combobox2 = new QComboBox();
    combobox2->addItem(tr("Toutes les vues 2D + moteur 3D"));
    combobox2->addItem(tr("Une vue 2D + moteur 3D"));
    combobox2->addItem(tr("Une vue 2D"));
    combobox2->addItem(tr("Moteur 3D"));

    QComboBox *combobox3 = new QComboBox();
    combobox3->addItem(tr("Texture"));
    combobox3->addItem(tr("Volume"));
    combobox3->addItem(tr("Maillage"));
    combobox3->addItem(tr("Squelette"));

    vbox2->addWidget(combobox2);
    vbox2->addWidget(combobox3);

    manip3D->setLayout(vbox2);

    // 4 : ajouter les onglets au QTabWidget,
    // en indiquant la page qu'ils contiennent
    tab->addTab(manip2D,tr("Manipulations 2D"));
    tab->addTab(manip3D,tr("Manipulations 3D"));
}

QString MainWindow::style() {
    QString s = "QTabWidget::pane{border-top: 1px solid #000000;position: absolute;}QTabWidget::tab-bar{alignment: center;}} \
                       QTabBar::tab { \
                            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1, \
                                                        stop: 0 #E1E1E1, stop: 0.4 #DDDDDD, \
                                                        stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3); \
                            border: 2px solid #C4C4C3;\
                            border-bottom-color: #C2C7CB; /* same as the pane color */\
                            border-top-left-radius: 4px;\
                            border-top-right-radius: 4px;\
                            min-width: 8ex;\
                            padding: 2px;\
                        }\
                        QTabBar::tab:selected, QTabBar::tab:hover {\
                            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                        stop: 0 #fafafa, stop: 0.4 #f4f4f4,\
                                                        stop: 0.5 #e7e7e7, stop: 1.0 #fafafa);\
                        }\
                        QTabBar::tab:selected {\
                            border-color: #9B9B9B;\
                            border-bottom-color: #C2C7CB; /* same as pane color */\
                            text-decoration: none;\
                        }\
                        QComboBox {\
                            border: 1px solid gray;\
                            border-radius: 3px;\
                            padding: 1px 18px 1px 3px;\
                            min-width: 6em;\
                        }\
                        \
                        QComboBox:editable {\
                            background: white;\
                        }\
                        \
                        QComboBox:!editable, QComboBox::drop-down:editable {\
                             background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                         stop: 0 #E1E1E1, stop: 0.4 #DDDDDD,\
                                                         stop: 0.5 #D8D8D8, stop: 1.0 #D3D3D3);\
                        }\
                        \
                        QComboBox:!editable:on, QComboBox::drop-down:editable:on {\
                            background: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,\
                                                        stop: 0 #D3D3D3, stop: 0.4 #D8D8D8,\
                                                        stop: 0.5 #DDDDDD, stop: 1.0 #E1E1E1);\
                        }\
                        \
                        QComboBox:on { /* shift the text when the popup opens */\
                            padding-top: 3px;\
                            padding-left: 4px;\
                        }\
                        ";
   return s;
}
