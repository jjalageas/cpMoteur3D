#include <iostream>

#include "wmanipulation.hpp"
#include "exampleapp.h"

#include <QWidget>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QSpacerItem>
#include <QObject>

WManipulation::~WManipulation() {
    delete manip2D;
    delete spiny;
    delete spinz;
    delete viewType2D;

    delete manip3D;
    delete spinTextureY;
    delete spinTextureZ;
    delete picture;
    delete mask;
    delete viewType3D;
    delete transformationType;
}

void WManipulation::displayTransformationType(int index) {
    switch(index) {
    case 0:
        std::cout << "Texture" << std::endl;
        break;
    case 1:
        std::cout << "Volume" << std::endl;
        break;
    case 2:
        a->initializeMesh();
      //  a->initializeModel();
        // a   blabla
        std::cout << "Maillage" << std::endl;
        break;
    case 3:
        std::cout << "Squelette" << std::endl;
        break;
    default:
        break;
    }
}

void WManipulation::displayViewType(int index) {
    switch(index) {
    case 0:
        std::cout << "All views" << std::endl;
        break;
    case 1:
        std::cout << "one 2D + 3D engine" << std::endl;
        break;
    case 2:
        std::cout << "one 2D" << std::endl;
        break;
    case 3:
        std::cout << "3D engine" << std::endl;
        break;
    default:
        break;
    }
}

void WManipulation::displayPictureOrNot(bool active) {
    if(active)
        std::cout << "Afficher l'image" << std::endl;
    else
        std::cout << "Ne pas afficher l'image" << std::endl;
}

void WManipulation::displayMaskOrNot(bool active) {
    if(active)
        std::cout << "Afficher le masque" << std::endl;
    else
        std::cout << "Ne pas afficher le masque" << std::endl;
}

void WManipulation::retranslateUi(const QString &lang) {
    if (lang == "fr") {
        viewType2D->setItemText(0,"Toutes les vues 2D + Moteur 3D");
        viewType2D->setItemText(1,"Une vue 2D + Moteur 3D");
        viewType2D->setItemText(2,"Une vue 2D");
        viewType2D->setItemText(3,"Moteur 3D");
        labelTextureX->setText("Texture en x : ");
        labelTextureY->setText("Texture en y : ");
        labelTextureZ->setText("Texture en z : ");
        picture->setText("Image");
        mask->setText("Masque");
        viewType3D->setItemText(0,"Toutes les vues 2D + Moteur 3D");
        viewType3D->setItemText(1,"Une vue 2D + Moteur 3D");
        viewType3D->setItemText(2,"Une vue 2D");
        viewType3D->setItemText(3,"Moteur 3D");
        transformationType->setItemText(0,"Texture");
        transformationType->setItemText(1,"Volume");
        transformationType->setItemText(2,"Maillage");
        transformationType->setItemText(3,"Squelette");
    }
    else if (lang == "es") {
        viewType2D->setItemText(0,"Todas las Vistas 2D + Motor 3D");
        viewType2D->setItemText(1,"Una Vista 2D + Motor 3D");
        viewType2D->setItemText(2,"Una Vista 2D");
        viewType2D->setItemText(3,"Motor 3D");
        labelTextureX->setText("Textura en x : ");
        labelTextureY->setText("Textura en y : ");
        labelTextureZ->setText("Textura en z : ");
        picture->setText("Imagen");
        mask->setText("Máscara");
        viewType3D->setItemText(0,"Todas las Vistas 2D + Motor 3D");
        viewType3D->setItemText(1,"Una Vista 2D + Motor 3D");
        viewType3D->setItemText(2,"Una Vista 2D");
        viewType3D->setItemText(3,"Motor 3D");
        transformationType->setItemText(0,"Textura");
        transformationType->setItemText(1,"Volumen");
        transformationType->setItemText(2,"Malla");
        transformationType->setItemText(3,"Esqueleto");
    }
    else { // English
        viewType2D->setItemText(0,"All 2D Views & 3D Engine");
        viewType2D->setItemText(1,"One 2D View & 3D Engine");
        viewType2D->setItemText(2,"One 2D View");
        viewType2D->setItemText(3,"3D Engine");
        labelTextureX->setText("Texture in x : ");
        labelTextureX->setText("Texture in y : ");
        labelTextureX->setText("Texture in z : ");
        picture->setText("Picture");
        mask->setText("Mask");
        viewType3D->setItemText(0,"All 2D Views & 3D Engine");
        viewType3D->setItemText(1,"One 2D View & 3D Engine");
        viewType3D->setItemText(2,"One 2D View");
        viewType3D->setItemText(3,"3D Engine");
        transformationType->setItemText(0,"Texture");
        transformationType->setItemText(1,"Volume");
        transformationType->setItemText(2,"Mesh");
        transformationType->setItemText(3,"Skeleton");
    }
}

WManipulation::WManipulation(QTabWidget* widget, ExampleApp *_a)
{

    a = _a;
    //Création de nos deux onglets
    manip2D = new QWidget();
    manip3D = new QWidget();

    //Création du contenu de nos deux onglets
    //page 1
    spinx = new QSpinBox();
    spiny = new QSpinBox();
    spinz = new QSpinBox();

    viewType2D = new QComboBox();
    viewType2D->addItem(QComboBox::tr("All 2D Views & 3D Engine"));
    viewType2D->addItem(QComboBox::tr("One 2D View & 3D Engine"));
    viewType2D->addItem(QComboBox::tr("One 2D View"));
    viewType2D->addItem(QComboBox::tr("3D Engine"));
    QObject::connect(viewType2D,SIGNAL(currentIndexChanged(int)),this,SLOT(displayViewType(int)));

    QLabel *labelx = new QLabel(QLabel::tr("x : "));
    QLabel *labely = new QLabel(QLabel::tr("y : "));
    QLabel *labelz = new QLabel(QLabel::tr("z : "));

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

    vbox1->addWidget(viewType2D);

    manip2D->setLayout(vbox1);

    //page 2
    spinTextureX = new QSpinBox();
    spinTextureY = new QSpinBox();
    spinTextureZ = new QSpinBox();

    labelTextureX = new QLabel(QLabel::tr("Texture in x : "));
    labelTextureY = new QLabel(QLabel::tr("Texture in y : "));
    labelTextureZ = new QLabel(QLabel::tr("Texture in z : "));

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

    picture = new QCheckBox(QCheckBox::tr("Picture"));
    QObject::connect(picture,SIGNAL(clicked(bool)), this, SLOT(displayPictureOrNot(bool)));
    mask = new QCheckBox(QCheckBox::tr("Mask"));
    QObject::connect(mask,SIGNAL(clicked(bool)), this, SLOT(displayMaskOrNot(bool)));
    hbox7->addWidget(picture);
    hbox7->addWidget(mask);

    vbox2->addLayout(hbox7);

    viewType3D = new QComboBox();
    viewType3D->addItem(QComboBox::tr("All 2D Views & 3D Engine"));
    viewType3D->addItem(QComboBox::tr("One 2D View & 3D Engine"));
    viewType3D->addItem(QComboBox::tr("One 2D View"));
    viewType3D->addItem(QComboBox::tr("3D Engine"));
    QObject::connect(viewType3D,SIGNAL(currentIndexChanged(int)),this,SLOT(displayViewType(int)));

    transformationType = new QComboBox();
    transformationType->addItem(QComboBox::tr("Texture"));
    transformationType->addItem(QComboBox::tr("Volume"));
    transformationType->addItem(QComboBox::tr("Mesh"));
    transformationType->addItem(QComboBox::tr("Skeleton"));
    QObject::connect(transformationType,SIGNAL(currentIndexChanged(int)),this,SLOT(displayTransformationType(int)));

    vbox2->addWidget(viewType3D);
    vbox2->addWidget(transformationType);

    manip3D->setLayout(vbox2);

    //On ajoute les onglets au QTabWidget passé en paramètre
    widget->addTab(manip2D, QWidget::tr("2D Manipulations"));
    widget->addTab(manip3D, QWidget::tr("3D Manipulations"));
}

