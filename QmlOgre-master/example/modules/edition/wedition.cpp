#include "wedition.hpp"


#include <QHBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QTreeView>
#include <QSpinBox>
#include <QSpacerItem>
#include <QStandardItemModel>
#include <QMessageBox>


#include "treemodel.hpp"
#include "toolsButtonGroup.hpp"


WEdition::WEdition(QWidget* widget) : QWidget(widget), select(ActiveSelection::getInstance())
{

    QHBoxLayout * mainLayout = new QHBoxLayout();
    QVBoxLayout * leftLayout = new QVBoxLayout(); //treeWidget + 3 buttons
    QVBoxLayout * rightLayout = new QVBoxLayout(); //tools (pen , eraser, bucket, ..., spacer)

    //QStandardItemModel * treeModel = new QStandardItemModel();
    treeModel = new TreeModel();

    QTreeView * treeView = new QTreeView(this);
    treeView->setModel(treeModel);
    controller = new Controller(treeView,treeModel);


    QHBoxLayout * buttons = new QHBoxLayout(); // 3 buttons
    addGroupe = new QPushButton("Add Group",this);
    addMaskBt = new QPushButton("Add Mask",this);
    fusion = new QPushButton("Merge",this);

    buttons->addWidget(addGroupe);
    buttons->addWidget(addMaskBt);
    buttons->addWidget(fusion);

    leftLayout->addWidget(treeView);
    leftLayout->addLayout(buttons);


    nothingButton = new QPushButton("",this);
    penButton = new QPushButton("",this);
    penButton->setIcon(QIcon(":/resources/images/pen.png"));
    eraserButton = new QPushButton("",this);
    eraserButton->setIcon(QIcon(":/resources/images/eraser.png"));
    bucketButton = new QPushButton("",this);
    bucketButton->setIcon(QIcon(":/resources/images/bucket.png"));
    bevelButton = new QPushButton("",this);
    bevelButton->setIcon(QIcon(":/resources/images/pen.png")); //TODO found GPL bevel icon

    rightLayout->addWidget(nothingButton);
    rightLayout->addWidget(penButton);
    rightLayout->addWidget(eraserButton);
    rightLayout->addWidget(bucketButton);
    rightLayout->addWidget(bevelButton);
    rightLayout->addWidget(new QSpinBox());
    rightLayout->addItem(new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding));


    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    widget->setLayout(mainLayout);


    ToolsButtonGroup * toolsButtons = new ToolsButtonGroup();
    toolsButtons->addButton(nothingButton);
    toolsButtons->addButton(penButton);
    toolsButtons->addButton(eraserButton);
    toolsButtons->addButton(bucketButton);
    toolsButtons->addButton(bevelButton);

    nothingButton->setCheckable(true);
    penButton->setCheckable(true);
    eraserButton->setCheckable(true);
    bucketButton->setCheckable(true);
    bevelButton->setCheckable(true);


    nothingButton->setAutoExclusive(true);
    penButton->setAutoExclusive(true);
    eraserButton->setAutoExclusive(true);
    bucketButton->setAutoExclusive(true);
    bevelButton->setAutoExclusive(true);

    connect(nothingButton, SIGNAL(toggled(bool)),toolsButtons, SLOT(nothingAction()));
    connect(penButton, SIGNAL(toggled(bool)),toolsButtons, SLOT(penAction()));
    connect(eraserButton, SIGNAL(toggled(bool)),toolsButtons, SLOT(eraserAction()));
    connect(bucketButton, SIGNAL(toggled(bool)),toolsButtons, SLOT(bucketAction()));
    connect(bevelButton, SIGNAL(toggled(bool)),toolsButtons, SLOT(bevelAction()));
    connect(addGroupe,SIGNAL(clicked()),treeModel,SLOT(addGroupe()));
    connect(addMaskBt,SIGNAL(clicked()),controller,SLOT(addMask()));

}
void WEdition::retranslateUi(const QString &lang)
{
    if (lang == "fr"){
        addGroupe->setText(tr("Ajouter Groupe"));
        addMaskBt->setText(tr("Ajouter Masque"));
        fusion->setText(tr("Fusion"));
    }
    else if (lang == "es"){
        addGroupe->setText(trUtf8("Añadir grupo"));
        addMaskBt->setText(trUtf8("Añadir máscara"));
        fusion->setText(trUtf8("Fusión"));
    }

   else{ // English
        addGroupe->setText(tr("Add Group"));
        addMaskBt->setText(tr("Add Mask"));
        fusion->setText(tr("Merge"));
    }

    treeModel->retranslateUi(lang);
}
