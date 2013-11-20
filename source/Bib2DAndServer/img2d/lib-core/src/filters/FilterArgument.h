#ifndef FILTERARGUMENT_H
#define FILTERARGUMENT_H

#include <string>
#include <vector>
#include <QVariant>

class FilterArgument
{
public:
    // ideal : => no recompilation of both client and server
    //static FilterArgument* unMarshall(std::string marshalledFileArgument); // returns 0 if malformed string.

    FilterArgument(std::string name,
                   QVariant::Type type,
                   QVariant minValue = QVariant(),
                   QVariant maxValue = QVariant(),
                   QVariant defaultValue = QVariant(),
                   std::vector<QVariant> domainDefinition = std::vector<QVariant>());
    const std::string& getName() const;

    bool isSet() const;
    void setValue(QVariant v); // the user must check the conditions himself.
    const std::string getType() const;
    const QVariant& getValue() const;

    const QVariant& getMin() const; // if no value : QVariant.isValid() == false
    const QVariant& getMax() const;
    const QVariant& getDefault() const;
    const std::vector<QVariant>& getDomainDefinition() const; // enumeration or list of numbers for example

private:
    std::string _name;
    QVariant::Type _type;
    QVariant _minValue;
    QVariant _maxValue;
    QVariant _defaultValue;
    QVariant _currentValue;
    std::vector<QVariant> _domainDefinition;
};

#endif // FILTERARGUMENT_H
