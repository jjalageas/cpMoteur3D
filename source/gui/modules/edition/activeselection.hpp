#ifndef ACTIVESELECTION_H
#define ACTIVESELECTION_H
#include "enumselection.hpp"
#include "zone.hpp"

class ActiveSelection
{
public:
    static ActiveSelection* getInstance();
    EnumSelection getTool();
    void setTool(EnumSelection tool);
    Zone* getZone();
    void setZone(Zone* z);

private:
    ActiveSelection();
    ~ActiveSelection();
    static ActiveSelection* Instance;
    EnumSelection activeTool;
    Zone* activeZone;
};

#endif // ACTIVESELECTION_H
