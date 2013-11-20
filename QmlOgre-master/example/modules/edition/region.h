#ifndef REGION_H
#define REGION_H

#include <QObject>
#include <QColor>

class Region : public QObject
{

    Q_OBJECT
public:
    explicit Region(QObject *parent = 0);
    void setName(std::string &name);
    std::string getName();
    int getId();
    void setRegions(std::list<Region> regions);
    std::list<Region> getRegions();

signals:

public slots:

private:
    std::string name;
    int id;
    QColor color;

};

#endif // REGION_H
