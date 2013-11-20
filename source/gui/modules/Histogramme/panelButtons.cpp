#include "panelButtons.h"
#include <iostream>

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Panel contenant les boutons
 */

using namespace std;

PanelButtons::PanelButtons(QWidget *parent, PanelHisto * panelHisto): QWidget(parent){

    qBoxRed = new QCheckBox("Rouge", this);
    qBoxBlue = new QCheckBox("Bleue", this);
    qBoxGreen = new QCheckBox("Vert", this);
    qBoxNDG= new QCheckBox("Niveaux de gris", this);

    qBoxRed->setCheckable(true);

    connect(qBoxRed, SIGNAL(stateChanged(int)), this, SLOT(qBoxRed_toggled(int)));
    connect(qBoxBlue,  SIGNAL(stateChanged(int)), this, SLOT(qBoxBlue_toggled(int)));
    connect(qBoxGreen,  SIGNAL(stateChanged(int)), this, SLOT(qBoxGreen_toggled(int)));
    connect(qBoxNDG,  SIGNAL(stateChanged(int)), this, SLOT(qBoxNDG_toggled(int)));

    monPanelHisto = panelHisto;

    layout = new QHBoxLayout;
}

void PanelButtons::paintEvent(QPaintEvent *){
    layout->addWidget(qBoxRed);
    layout->addWidget(qBoxGreen);
    layout->addWidget(qBoxBlue);
    layout->addWidget(qBoxNDG);

    setLayout(layout);
}

void PanelButtons::qBoxNDG_toggled(int state){
    if(state==Qt::Checked){
        qBoxRed->setChecked(false);
        qBoxGreen->setChecked(false);
        qBoxBlue->setChecked(false);
        qBoxNDG->setChecked(true);

        monPanelHisto->color.clear();
        monPanelHisto->color.push_back("NDG");
        monPanelHisto->repaint();
    }
    else{
        monPanelHisto->color.erase(std::find (monPanelHisto->color.begin(), monPanelHisto->color.end(), "NDG"));
        monPanelHisto->repaint();
        }
}

void PanelButtons::qBoxBlue_toggled(int state){
        qBoxNDG->setChecked(false);
        if(state==Qt::Checked){
            monPanelHisto->color.push_back("blue");
            monPanelHisto->repaint();
        }
        else{
            monPanelHisto->color.erase(std::find (monPanelHisto->color.begin(), monPanelHisto->color.end(), "blue"));
            monPanelHisto->repaint();
        }

}

void PanelButtons::qBoxRed_toggled(int state){
        qBoxNDG->setChecked(false);
        if(state==Qt::Checked){
            monPanelHisto->color.push_back("red");
            monPanelHisto->repaint();
        }
        else{
            monPanelHisto->color.erase(std::find (monPanelHisto->color.begin(), monPanelHisto->color.end(), "red"));
            monPanelHisto->repaint();
        }
}


void PanelButtons::qBoxGreen_toggled(int state){
        qBoxNDG->setChecked(false);
        if(state==Qt::Checked){
            monPanelHisto->color.push_back("green");
            monPanelHisto->repaint();
        }
        else{
            monPanelHisto->color.erase(std::find (monPanelHisto->color.begin(), monPanelHisto->color.end(), "green"));
            monPanelHisto->repaint();
        }

}
