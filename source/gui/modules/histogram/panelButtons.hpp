#ifndef PANELBUTTONS_H
#define PANELBUTTONS_H

/*
 * Dernière modification : 15/10/2013 - Refactorisation
 *
 * Panel contenant les boutons
 */

#include <QWidget>
#include <QCheckBox>
#include <QVBoxLayout>
#include <QPushButton>

#include "panelHisto.hpp"

class PanelButtons:public QWidget
{
    Q_OBJECT

    QCheckBox *qBoxRed, *qBoxBlue, *qBoxGreen, *qBoxNDG;
    QPushButton * qButtonStretch;
    QHBoxLayout *layout;

public:
    PanelButtons(QWidget *parent, PanelHisto * f);

public slots:
    void qBoxNDG_toggled(int state);
    void qBoxBlue_toggled(int state);
    void qBoxRed_toggled(int state);
    void qBoxGreen_toggled(int state);

protected:
    void paintEvent(QPaintEvent *);

private:
    PanelHisto * monPanelHisto;
};

#endif // PANELBUTTONS_H
