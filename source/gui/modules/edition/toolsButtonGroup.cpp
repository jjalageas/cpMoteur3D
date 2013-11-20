#include "toolsButtonGroup.hpp"
#include <QMessageBox>


ToolsButtonGroup::ToolsButtonGroup(): QButtonGroup(), select(ActiveSelection::getInstance())
{

}

void ToolsButtonGroup::penAction(){
    select->setTool(pen);
}

void ToolsButtonGroup::eraserAction(){
    select->setTool(eraser);
}

void ToolsButtonGroup::bucketAction(){
    select->setTool(bucket);
}

void ToolsButtonGroup::bevelAction(){
    select->setTool(bevel);
}

void ToolsButtonGroup::nothingAction(){
    select->setTool(nothing);
}
