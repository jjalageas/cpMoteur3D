#ifndef WEDITION_H
#define WEDITION_H
#include <QWidget>
#include <QObject>
#include <QTreeView>
#include <QPushButton>
#include "treemodel.hpp"
#include "activeselection.hpp"
#include "enumselection.hpp"
#include "controller.hpp"

class WEdition : public QWidget
{

public:
  WEdition(QWidget *widget);
  void retranslateUi(const QString& lang);

private:
  TreeModel * treeModel;
  QPushButton * penButton;
  QPushButton * eraserButton;
  QPushButton * bucketButton;
  QPushButton * bevelButton;
  QPushButton * nothingButton;
  Controller * controller;
  QPushButton * addGroupe;
  QPushButton * addMaskBt;
  QPushButton * fusion;

  ActiveSelection* select;

};

#endif // WEDITION_H
