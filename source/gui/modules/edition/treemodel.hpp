#ifndef TREEMODEL_H
#define TREEMODEL_H

#include <QStandardItemModel>
#include <QModelIndex>
#include "groupe.hpp"
#include "mask.hpp"

class TreeModel : public QStandardItemModel
{
    Q_OBJECT

public:
    explicit TreeModel(QObject *parent = 0);
    ~TreeModel();
    void retranslateUi(const QString& lang);

private:
     QStandardItem * racine;
     QStandardItem * racineView; //not the same than racine : this is weird
     QStandardItem * getItem(const QModelIndex & index);
     QStandardItem * getGroupeItem(const QModelIndex & index);

private slots :
     void addGroupe();

public slots :
     void addMask(const QModelIndex & groupeIndex);

};

#endif // TREEMODEL_H
