#ifndef FILTERWINDOW_H
#define FILTERWINDOW_H

#include "Filterv2.h"
#include <QPushButton>
#include <QLayout>
#include <vector>
#include <QDoubleSpinBox>

class FilterWindow : public QWidget
{
    Q_OBJECT

public:
    enum BUTTONS_MODE {
        APPLY,
        OK_CANCEL,
        NONE
    };

    FilterWindow(FilterV2 &filter, BUTTONS_MODE buttons_mode, QWidget *parent = 0);
    FilterV2& getFilter();

    FilterV2 &_filter;
    //BUTTONS_MODE _buttons_mode;
    QPushButton* _accept_button;
    QPushButton* _cancel_button;

protected:
    void addArgument(const FilterArgument&, QLayout* layout);
    void addBaseArgument(QVariant variant, std::string name, QGridLayout* layout, int row);

    std::vector< QPair<std::string, QDoubleSpinBox*> > _doubleSpinBoxs;

signals:
    void accept();
    void cancel();

private slots:
    void updateFilterArgumentValue();
};

#endif // FILTERWINDOW_H
