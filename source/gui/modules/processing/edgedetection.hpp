#ifndef EDGEDETECTION_H
#define EDGEDETECTION_H

#include <QVBoxLayout>
#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QPushButton>
#include <QComboBox>
#include <QLabel>
#include <QFont>

class EdgeDetection : public QVBoxLayout
{
public:
    EdgeDetection(QWidget *parent);
    void retranslateUi(const QString& lang);

private:
    QFont font;
    QLabel *iteration;
    QLabel *order;
    QLabel *label;
    QComboBox *comboBox;
    QSpinBox *spinBox1;
    QDoubleSpinBox *spinBox2;
    QHBoxLayout *hbox;
    QPushButton *button;
};

#endif // EDGEDETECTION_H
