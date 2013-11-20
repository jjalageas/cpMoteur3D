#ifndef NEWACCOUNT_H
#define NEWACCOUNT_H

#include <QWidget>

namespace Ui {
class NewAccount;
}

class NewAccount: public QWidget
{
    Q_OBJECT

public:
    explicit NewAccount(QWidget *parent = 0);
    ~NewAccount();

private:
    Ui::NewAccount *ui;

public slots:
    void checkConnexion();

};



#endif // NEWACCOUNT_H
