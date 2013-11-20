#ifndef TREEOBJECT_HPP
#define TREEOBJECT_HPP
#include <QObject>
#include <QTreeView>
#include "treemodel.hpp"

class Controller : public QObject
{
    Q_OBJECT
public:
    Controller(QTreeView * treeView, TreeModel * treeModel);

private:
    TreeModel * treeModel;
    QTreeView * treeView;

private slots:
    void addMask();

};

#endif // TREEOBJECT_HPP
