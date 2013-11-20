#ifndef INFORMATION_VIEWER_H
#define INFORMATION_VIEWER_H

#include <QtGui>

#include <Information.h>
//#include <RessourceManager.h>


class InformationViewer: public QDockWidget
{
public:

       InformationViewer(QWidget *parent = 0);
       ~InformationViewer();

       void setGeneralInformation(Information *information);
       void setSliceInformation(Information *information);
       void clear();

private:

       void setupInterface();
       void clearGeneralInformation();
       void clearSliceInformation();

       QWidget  *_mainWidget;
       QStandardItemModel *_generalInformation;
       QStandardItemModel *_sliceInformation;
};

#endif
