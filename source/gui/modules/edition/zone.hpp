#ifndef ZONE_HPP
#define ZONE_HPP

#include <QColor>

class Zone
{


public:
    explicit Zone();
    void setName(std::string &name);
    std::string getName();
    int getId();
    void setColor(QColor &color);
    QColor getColor();

private:
    std::string name;
    int id;
    QColor color;
    static int compteur;

};

#endif // ZONE_HPP
