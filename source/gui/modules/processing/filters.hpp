#ifndef FILTERS_HPP
#define FILTERS_HPP

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>

class Filters : public QVBoxLayout
{
public:
    Filters(QWidget *parent);
    void retranslateUi(const QString& lang);

private:
    QFont font;
    QPushButton *button;
    QLabel *pitch;
    QLabel *order;
    QLabel *filtering;
    QComboBox *comboBox;
    QDoubleSpinBox *spinBox1;
    QDoubleSpinBox *spinBox2;
    QHBoxLayout *hbox;
};

#endif // FILTERS_HPP
