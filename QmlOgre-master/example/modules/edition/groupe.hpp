#ifndef GROUPE_H
#define GROUPE_H

#include <QStandardItem>
#include "zone.hpp"

class Groupe : public QStandardItem
{

public:
    Groupe(const QString & label);

private:
    QString name;
    QList<Zone *> childs;

};

#endif // GROUPE_H
