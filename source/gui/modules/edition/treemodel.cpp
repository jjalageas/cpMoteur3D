#include "treemodel.hpp"


TreeModel::TreeModel(QObject *parent) : QStandardItemModel(parent),racine(this->invisibleRootItem())
{
    racineView = this->itemFromIndex(this->indexFromItem(racine)); //this is not the same QStandartItem than racine!
    QStringList headerLabels(QString(tr("Group")));
    headerLabels += QString(tr("Color"));
    headerLabels += QString(tr("Region Name"));
    this->setHorizontalHeaderLabels(headerLabels);

}

TreeModel::~TreeModel()
{

}

void TreeModel::addGroupe(){
    Groupe * newGroupe = new Groupe(QString(tr("new Group")));
    this->racine->appendRow(newGroupe);
}

void TreeModel::addMask(const QModelIndex & groupeIndex)
{
    QStandardItem * groupe = getGroupeItem(groupeIndex);
    if (groupe == racineView) return;
    Mask * newMask = new Mask(QString(tr("new Mask")));
    groupe->appendRow(newMask);
}

QStandardItem * TreeModel::getGroupeItem(const QModelIndex & groupeIndex){
    QStandardItem * groupe = this->itemFromIndex(groupeIndex);
    if (groupe == racineView) return racineView;
    while(groupe->parent() != racineView){
        groupe = groupe->parent();
    }
    return groupe;
}


void TreeModel::retranslateUi(const QString &lang)
{
    if (lang == "fr") {
        this->horizontalHeaderItem(0)->setText("Groupe");
        this->horizontalHeaderItem(1)->setText("Couleur");
        this->horizontalHeaderItem(2)->setText("Nom Région");
    }
    else if (lang == "es") {
        this->horizontalHeaderItem(0)->setText("Groupo");
        this->horizontalHeaderItem(1)->setText("Color");
        this->horizontalHeaderItem(2)->setText("Nombre Región");
    }

   else{ // English
        this->horizontalHeaderItem(0)->setText("Group");
        this->horizontalHeaderItem(1)->setText("Color");
        this->horizontalHeaderItem(2)->setText("Region Name");
    }
}