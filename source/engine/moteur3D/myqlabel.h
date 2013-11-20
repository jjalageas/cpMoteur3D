#ifndef MYQLABEL_H
#define MYQLABEL_H

#include <QLabel>
#include <QMouseEvent>
#include <iostream>

class MyQlabel : public QLabel
{
    Q_OBJECT

public:
    MyQlabel(QWidget *parent);
    MyQlabel(){}

public slots:
    void mousePressEvent(QMouseEvent *ev)
    {
        if(ev->button() == Qt::LeftButton)
        {
            emit click(ev->x() , ev->y());
        }
    }

signals:
    void click(int x, int y);
};

#endif // MYQLABEL_H
