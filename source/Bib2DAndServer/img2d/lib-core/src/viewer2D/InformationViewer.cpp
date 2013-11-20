#include"InformationViewer.h"

using namespace std;

/* -------------------------------------------------------------------------------------------------
     CONSTRUCT & DESTRUCT
   -------------------------------------------------------------------------------------------------*/

InformationViewer::InformationViewer(QWidget *parent) : QDockWidget(parent)
{
       //RessourceManager::GetInstance()->addRessource("InformationViewer");

       setAllowedAreas(Qt::LeftDockWidgetArea);
       setFeatures(QDockWidget::NoDockWidgetFeatures);
       setMinimumSize(400, 400);

       setupInterface();
}

InformationViewer::~InformationViewer()
{
       //RessourceManager::GetInstance()->deleteRessource("InformationViewer");

       _generalInformation->clear();
       _sliceInformation->clear();

       delete _mainWidget;
}

/* ----------------------------------------------------------------------------------------------------------------
      PRIVATE METHODS
  ----------------------------------------------------------------------------------------------------------------*/

void InformationViewer::setupInterface()
{
       /* MAIN LAYOUT */
       _mainWidget = new QWidget(this);
       setWidget(_mainWidget);
       QVBoxLayout *mainLayout = new QVBoxLayout(_mainWidget);
       _mainWidget->setLayout(mainLayout);

       /* GENERAL INFORMATION GROUP BOX */
       QGroupBox *generalBox = new QGroupBox(tr("Generals Informations"), _mainWidget);
       mainLayout->addWidget(generalBox);

       QTreeView *generalTreeView = new QTreeView(_mainWidget);
       generalTreeView->setRootIsDecorated(false);
       generalTreeView->setAlternatingRowColors(true);
       mainLayout->addWidget(generalTreeView);

       _generalInformation = new QStandardItemModel(0, 2, generalTreeView);
       _generalInformation->setHeaderData(0, Qt::Horizontal, QObject::tr("Title"));
       _generalInformation->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
       generalTreeView->setModel(_generalInformation);

       /* SLICE INFORMATION GROUP BOX */
       QGroupBox *sliceBox = new QGroupBox(tr("Slice Informations"), _mainWidget);
       mainLayout->addWidget(sliceBox);

       QTreeView *sliceTreeView = new QTreeView(_mainWidget);
       sliceTreeView->setRootIsDecorated(false);
       sliceTreeView->setAlternatingRowColors(true);
       mainLayout->addWidget(sliceTreeView);

       _sliceInformation = new QStandardItemModel(0, 2, sliceTreeView);
       _sliceInformation->setHeaderData(0, Qt::Horizontal, QObject::tr("Title"));
       _sliceInformation->setHeaderData(1, Qt::Horizontal, QObject::tr("Description"));
       sliceTreeView->setModel(_sliceInformation);
}

void InformationViewer::clear()
{
       clearGeneralInformation();
       clearSliceInformation();
}

/* ----------------------------------------------------------------------------------------------------------------
      PUBLIC METHODS
  ----------------------------------------------------------------------------------------------------------------*/

void InformationViewer::clearGeneralInformation()
{
       _generalInformation->removeRows(0, _generalInformation->rowCount());
}

void InformationViewer::setGeneralInformation(Information *information)
{
       clearGeneralInformation();

       int informationsSize = information->getSize();
       if (informationsSize == 0)
       {
              _generalInformation->insertRow(0);
              _generalInformation->setData(_generalInformation->index(0, 1), tr("No information"));
       }
       else
       {
              for (int i =0 ; i < informationsSize ; i++)
              {
                     string title = information->getTitle(i);
                     string description = information->getDescription(i);

                     _generalInformation->insertRow(i);
                     _generalInformation->setData(_generalInformation->index(i, 0), QString(title.c_str()));
                     _generalInformation->setData(_generalInformation->index(i, 1), QString(description.c_str()));
              }
       }
}

void InformationViewer::clearSliceInformation()
{
       _sliceInformation->removeRows(0, _sliceInformation->rowCount());
}

void InformationViewer::setSliceInformation(Information *information)
{
       clearSliceInformation();

       int informationsSize = information->getSize();
       if (informationsSize == 0)
       {
              _sliceInformation->insertRow(0);
              _sliceInformation->setData(_sliceInformation->index(0, 1), tr("No information"));
       }
       else
       {
              for (int i =0 ; i < informationsSize ; i++)
              {
                     string title = information->getTitle(i);
                     string description = information->getDescription(i);

                     _sliceInformation->insertRow(i);
                     _sliceInformation->setData(_sliceInformation->index(i, 0), QString(title.c_str()));
                     _sliceInformation->setData(_sliceInformation->index(i, 1), QString(description.c_str()));
              }
       }
}

