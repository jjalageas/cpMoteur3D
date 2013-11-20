#include "view4boxes.hpp"
#include "coral.hpp"
#include "imageviewer.hpp"

#include <QTextEdit>

View4Boxes::View4Boxes(QWidget *parent)
    : QWidget(parent)
{
    setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    setupInterface();
}

View4Boxes::View4Boxes(const View4Boxes &other, QWidget *parent)
    :QWidget(parent)
{
    int size = other._mainLayout->count();
    setupInterface();

    for (int i=0; i<size/2; i++)
    {
        _mainLayout->addWidget(new QWidget(other._mainLayout->itemAt(i)->widget()), 1, i);
        _mainLayout->itemAtPosition(1,i)->widget()->setObjectName(other._mainLayout->itemAt(i)->widget()->objectName());
        _mainLayout->addWidget(new QWidget(other._mainLayout->itemAt(size - i - 1)->widget()), 0, i);
        _mainLayout->itemAtPosition(0,i)->widget()->setObjectName(other._mainLayout->itemAt(size - i - 1)->widget()->objectName());
    }

    // ---- ------just for testing ----------------------------

    QGridLayout * l1 = new QGridLayout(_mainLayout->itemAtPosition(0,0)->widget());
    QGridLayout * l2 = new QGridLayout(_mainLayout->itemAtPosition(0,1)->widget());
    QGridLayout * l3 = new QGridLayout(_mainLayout->itemAtPosition(1,0)->widget());
    QGridLayout * l4 = new QGridLayout(_mainLayout->itemAtPosition(1,1)->widget());

    QTextEdit *t1 = new QTextEdit(_mainLayout->itemAtPosition(0,0)->widget());
    QTextEdit *t2 = new QTextEdit(_mainLayout->itemAtPosition(0,1)->widget());
    QTextEdit *t3 = new QTextEdit(_mainLayout->itemAtPosition(1,0)->widget());
    QTextEdit *t4 = new QTextEdit(_mainLayout->itemAtPosition(1,1)->widget());


    l1->addWidget(t1,0,0,1,1);
    l2->addWidget(t2,0,0,1,1);
    l3->addWidget(t3,0,0,1,1);
    l4->addWidget(t4,0,0,1,1);

    // ---------------------------------------------------------

    setLayout(_mainLayout);
}

View4Boxes &View4Boxes::operator =(const View4Boxes &other)
{
    if(this != &other)
    {
        int size = other._mainLayout->count();
        setupInterface();

        for (int i=0; i<size/2; i++)
        {
            _mainLayout->addWidget(new QWidget(other._mainLayout->itemAt(i)->widget()), 1, i);
            _mainLayout->itemAtPosition(1,i)->widget()->setObjectName(other._mainLayout->itemAt(i)->widget()->objectName());
            _mainLayout->addWidget(new QWidget(other._mainLayout->itemAt(size - i - 1)->widget()), 0, i);
            _mainLayout->itemAtPosition(0,i)->widget()->setObjectName(other._mainLayout->itemAt(size - i - 1)->widget()->objectName());
        }
        setLayout(_mainLayout);
    }
    return *this;
}

void View4Boxes::setupInterface()
{
    int WidthCells=this->width()/2;
    int HeightCells=this->height()/2;
    _mainLayout = new QGridLayout(this);
    _mainLayout->setColumnMinimumWidth(0,WidthCells);
    _mainLayout->setColumnMinimumWidth(1,WidthCells);
    _mainLayout->setRowMinimumHeight(0,HeightCells);
    _mainLayout->setRowMinimumHeight(1,HeightCells);
    setLayout(_mainLayout);
}

void View4Boxes::clearLayout()
{
    int cp=0;
    QLayoutItem* child = NULL;
    while((child = _mainLayout->takeAt(cp)) != NULL) {
        cp++;
        _mainLayout->removeItem(child);
    }
}

void View4Boxes::clearLayoutAtPosition(int index)
{
    QLayoutItem* child = NULL;
    if ((child = _mainLayout->takeAt(index)) != NULL)
        _mainLayout->removeItem(child);
}

QGridLayout *View4Boxes::getMainLayout()
{
    return _mainLayout;
}

void View4Boxes::setVues(QWidget *widget)
{
    _mainLayout->addWidget(widget,0,0,0,1,Qt::AlignLeft);
    widget->show();
}

void View4Boxes::setVues(QQueue<QWidget *> queuWidget)
{
    int nbElements = queuWidget.size();
    Q_ASSERT(nbElements == 4);
    clearLayout();

    _mainLayout->addWidget(queuWidget[0], 0, 0);
    _mainLayout->addWidget(queuWidget[1], 0, 1);
    _mainLayout->addWidget(queuWidget[2], 1, 0);
    _mainLayout->addWidget(queuWidget[3], 1, 1);
}

void View4Boxes::setup8Boxes()
{
    _wrdock = new QDockWidget(Coral::instance()->window());

    // Trick to hide dock title bar
    QWidget* wtitleWidget = new QWidget(this);
    _wrdock->setTitleBarWidget(wtitleWidget);
    _wrdock->setFeatures(QDockWidget::NoDockWidgetFeatures);

    QWidget *cwidget = new QWidget(_wrdock);
    QGridLayout * layout = new QGridLayout(cwidget);
    layout->addWidget(new QWidget(_mainLayout->itemAtPosition(0,0)->widget()), 0, 0);
    layout->addWidget(new QWidget(_mainLayout->itemAtPosition(0,1)->widget()), 0, 1);
    layout->addWidget(new QWidget(_mainLayout->itemAtPosition(1,0)->widget()), 1, 0);
    layout->addWidget(new QWidget(_mainLayout->itemAtPosition(1,1)->widget()), 1, 1);

    _wrdock->setWidget(cwidget);
    Coral::instance()->window()->addDockWidget(Qt::RightDockWidgetArea, _wrdock);

    // ---- ------maybe just for testing ----------------
    QGridLayout * l1 = new QGridLayout(layout->itemAtPosition(0,0)->widget());
    QGridLayout * l2 = new QGridLayout(layout->itemAtPosition(0,1)->widget());
    QGridLayout * l3 = new QGridLayout(layout->itemAtPosition(1,0)->widget());
    QGridLayout * l4 = new QGridLayout(layout->itemAtPosition(1,1)->widget());

    ImageViewer *t1 = new ImageViewer(layout->itemAtPosition(0,0)->widget());
    ImageViewer *t2 = new ImageViewer(layout->itemAtPosition(0,1)->widget());
    ImageViewer *t3 = new ImageViewer(layout->itemAtPosition(1,0)->widget());
    ImageViewer *t4 = new ImageViewer(layout->itemAtPosition(1,1)->widget());

    l1->addWidget(t1,0,0,1,1);
    l2->addWidget(t2,0,0,1,1);
    l3->addWidget(t3,0,0,1,1);
    l4->addWidget(t4,0,0,1,1);
    // ----------------------------------------------
}

void View4Boxes::remove8Boxes()
{
    Coral::instance()->window()->removeDockWidget(_wrdock);
    delete _wrdock;
}
