#include <QtGui>
#include "LoginFrame.h"
#include "ui_LoginFrame.h"
#include "SliceViewer.h"
#include "NewAccount.h"

LoginFrame::LoginFrame(QWidget *parent):
    QWidget(parent),
    ui(new Ui::LoginFrame)
{
    ui->setupUi(this);
    connect(ui->Valider, SIGNAL(clicked()), this, SLOT(checkConnexion()));
    connect(ui->CreerCompte, SIGNAL(clicked()), this, SLOT(createAccount()));
    connect(ui->Annuler, SIGNAL(clicked()), this, SLOT(close()));
    this->setFixedSize(this->sizeHint());
}

static SliceViewer* viewer = NULL;

LoginFrame::~LoginFrame()
{
    delete ui;
}

void
LoginFrame::checkConnexion()
{
    if(ui->lineEdit->text() != 0 && ui->lineEdit_2->text() == 0) {
        QMessageBox msgBox;
        msgBox.setText("You have to enter your password");
        msgBox.exec();
    }

    if (ui->lineEdit->text() != 0 && ui->lineEdit_2->text() != 0) {
        this->hide();
        viewer = new SliceViewer();
        viewer->show();
    }
}

void
LoginFrame::createAccount()
{
    NewAccount *account = new NewAccount();
    account->show();
    this->hide();
}


