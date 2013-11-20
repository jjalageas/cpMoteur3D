#ifndef MORPHOLOGY_HPP
#define MORPHOLOGY_HPP

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>

class Morphology : public QVBoxLayout
{
public:
    Morphology(QWidget *parent);
    void retranslateUi(const QString& lang);

private:
    QFont font;
    QPushButton *button;
    QLabel *connexity;
    QLabel *type;
    QLabel *size;
    QLabel *iteration;
    QLabel *morphology;
    QComboBox *comboBox;
    QDoubleSpinBox *spinBox1;
    QDoubleSpinBox *spinBox2;
    QComboBox *comboBox1;
    QComboBox *comboBox2;
    QHBoxLayout *hbox1;
    QHBoxLayout *hbox2;
};

#endif // MORPHOLOGY_HPP
