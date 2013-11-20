#include "controller.hpp"

Controller::Controller(QTreeView *treeView, TreeModel *treeModel) : treeModel(treeModel) , treeView(treeView)
{

}


void Controller::addMask()
 {
     QModelIndex groupeIndex = treeView->selectionModel()->currentIndex();
     treeModel->addMask(groupeIndex);
 }
