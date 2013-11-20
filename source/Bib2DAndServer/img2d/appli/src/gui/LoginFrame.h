#ifndef LOGINFRAME_H
#define LOGINFRAME_H

#include <QWidget>
#include <Examen.h>
#include <ImageMask2d.h>


namespace Ui {
class LoginFrame;
}

class LoginFrame: public QWidget
{
    Q_OBJECT

public:
    explicit LoginFrame(QWidget *parent = 0);
    ~LoginFrame();

private:
    Ui::LoginFrame *ui;

public slots:
    void checkConnexion();
    void createAccount();
};

#endif // LOGINFRAME_H
