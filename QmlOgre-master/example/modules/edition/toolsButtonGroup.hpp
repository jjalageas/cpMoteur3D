#ifndef TOOLSBUTTONGROUP_HPP
#define TOOLSBUTTONGROUP_HPP

#include <QButtonGroup>
#include "activeselection.hpp"

class ToolsButtonGroup : public QButtonGroup{

    Q_OBJECT

public:
    ToolsButtonGroup();
    ActiveSelection* select;

private slots:
    void penAction();
    void eraserAction();
    void bucketAction();
    void bevelAction();
    void nothingAction();

};


#endif // TOOLSBUTTONGROUP_HPP
