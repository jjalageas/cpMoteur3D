#include "activeselection.hpp"

ActiveSelection* ActiveSelection::Instance;

ActiveSelection::ActiveSelection(){
        activeTool = nothing;
    }

ActiveSelection* ActiveSelection::getInstance(){
    if (Instance == 0)
     Instance = new ActiveSelection();
    return Instance;
}

EnumSelection ActiveSelection::getTool(){
    return activeTool;
}

void ActiveSelection::setTool(EnumSelection tool){
    activeTool = tool;
}

Zone* ActiveSelection::getZone(){
    return activeZone;
}

void ActiveSelection::setZone(Zone* z){
    activeZone = z;
}
