#ifndef FILTER_HPP
#define FILTER_HPP

#include <QVBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QFont>
#include <QLabel>
#include <QDoubleSpinBox>
#include <QComboBox>

class Filter : public QVBoxLayout
{
public:
    Filter(QWidget *parent);
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

#endif // FILTER_HPP
