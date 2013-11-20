#include <QtGui>
#include <QtGui>
#include "NewAccount.h"
#include "ui_NewAccount.h"
//#include "sliceViewer.h"
//#include "ui_sliceViewer.h"

NewAccount::NewAccount(QWidget *parent):
    QWidget(parent),
    ui(new Ui::NewAccount)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(checkConnexion()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(close()));
    this->setFixedHeight(this->sizeHint().height());
}

NewAccount::~NewAccount()
{
    delete ui;
}

void NewAccount::checkConnexion()
{
    if (ui->lineEdit->text()   != 0 &&
        ui->lineEdit_2->text() != 0 &&
        ui->lineEdit_3->text() != 0 &&
        ui->lineEdit_4->text() != 0) {

        QMessageBox msgBox;
        msgBox.setText("For now, you must restart the application");
        msgBox.exec();
        this->hide();
    } else {
        QMessageBox msgBox;
        msgBox.setText("You must complete all information");
        msgBox.exec();
    }
}

