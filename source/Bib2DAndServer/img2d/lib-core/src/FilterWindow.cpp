#include "FilterWindow.h"
#include <QtGui>
#include "debug.h"

using namespace std;

FilterWindow::FilterWindow(FilterV2 &filter, BUTTONS_MODE buttons_mode, QWidget *parent) :
    QWidget(parent),
    _filter(filter),
    //_buttons_mode(buttons_mode),
    _accept_button(NULL),
    _cancel_button(NULL),
    _doubleSpinBoxs(vector< QPair<std::string, QDoubleSpinBox*> >())
{

    QLayout *mainLayout = new QVBoxLayout(this);
    this->setLayout(mainLayout);

    QLabel *name = new QLabel(QString::fromStdString(filter.getName()), this);
    mainLayout->addWidget(name);
    for(farg_iterator it = _filter.begin(); it != _filter.end(); ++it) {
        addArgument(* it->second, mainLayout);
    }

    QBoxLayout *layoutButtons = new QHBoxLayout(this);
    layoutButtons->addStretch();

    switch(buttons_mode) {
    case OK_CANCEL:
        _accept_button = new QPushButton("Ok", this);
        layoutButtons->addWidget(_accept_button);
        _cancel_button = new QPushButton("Cancel", this);
        layoutButtons->addWidget(_cancel_button);
    break;
    case APPLY:
        _accept_button = new QPushButton("Apply", this);
        layoutButtons->addWidget(_accept_button);

    case NONE:
        ;
    }
    connect(_accept_button, SIGNAL(clicked()), this, SIGNAL(accept()));
    connect(_cancel_button, SIGNAL(clicked()), this, SIGNAL(cancel()));
    connect(_cancel_button, SIGNAL(clicked()), this, SLOT(close()));

    mainLayout->addItem(layoutButtons);
}

FilterV2& FilterWindow::getFilter()
{
    return _filter;
}


void
FilterWindow::addArgument(const FilterArgument& arg, QLayout* layout)
{
    QGridLayout *gLayout = new QGridLayout(this);
    layout->addItem(gLayout);

    QLabel *name = new QLabel(QString::fromStdString(arg.getName()), this);
    gLayout->addWidget(name, 0, 0);

    if (arg.getDomainDefinition().size() != 0) {
        // do what is needed (display a list of values)
        return;
    }

    //QLayout *vLayout = new QVBoxLayout(this);
    //hLayout->addItem(vLayout);

    if (arg.getType() == "double") {
        QDoubleSpinBox* valUserInput = new QDoubleSpinBox(this);
        connect(valUserInput, SIGNAL(valueChanged(double)), this, SLOT(updateFilterArgumentValue()));
        _doubleSpinBoxs.push_back(qMakePair(string(arg.getName()), valUserInput));
        if (arg.getDefault().isValid() == true)
            valUserInput->setValue(arg.getDefault().toDouble());
        else
            valUserInput->cleanText();

        if (arg.getMin().isValid() == true)
            valUserInput->setMinimum(arg.getMin().toDouble());
        if (arg.getMax().isValid() == true)
            valUserInput->setMaximum(arg.getMax().toDouble());

        int row = 0;
        gLayout->addWidget(valUserInput, row++, 1);

        addBaseArgument(arg.getMin(), "min", gLayout, row++);
        addBaseArgument(arg.getMax(), "max", gLayout, row++);
    }
    else {
        eassert(false); // need an exception here.
    }
}


void
FilterWindow::addBaseArgument(QVariant variant, std::string name,
                              QGridLayout* gLayout, int row)
{
    if (variant.isValid() == false)
        return;
    //QLayout *hLayout = new QHBoxLayout(this);
    //layout->addItem(hLayout);
    QLabel *nameAndValLabel = new QLabel(QString::fromStdString(name) + " : " +
                                         variant.toString(), this);
    gLayout->addWidget(nameAndValLabel, row, 1);
}

void FilterWindow::updateFilterArgumentValue() {
    for(vector< QPair<std::string, QDoubleSpinBox*> >::iterator it = _doubleSpinBoxs.begin();
        it != _doubleSpinBoxs.end(); ++it) {
        eassert(_filter.getArgument(it->first) != NULL);
        eassert(_filter.getArgument(it->first)->getType() == "double");
        FilterArgument* arg = _filter.getArgument(it->first);
        QVariant val = QVariant((double)it->second->value());
        arg->setValue(val);
    }

    //cout << "updated argument value" << endl;
}


/*void
FilterWindow::doubleArgumentModif(double value)
{


}*/
