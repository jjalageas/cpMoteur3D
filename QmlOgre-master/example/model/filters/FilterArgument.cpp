#include "FilterArgument.h"
#include "debug.h"

using namespace std;

//static FilterArgument* unMarshall(std::string marshalledFileArgument); // returns 0 if malformed string.

FilterArgument::FilterArgument(std::string name,
               QVariant::Type type,
               QVariant minValue,
               QVariant maxValue,
               QVariant defaultValue,
               vector<QVariant> domainDefinition) :
    _name(name),
    _type(type),
    _minValue(minValue),
    _maxValue(maxValue),
    _defaultValue(defaultValue),
    _currentValue(defaultValue),
    _domainDefinition(domainDefinition)
{
    eassert(_type != QVariant::Invalid);
    eassert(_minValue.isValid() == false || _minValue.type() == _type);
    eassert(_maxValue.isValid() == false || _maxValue.type() == _type);
    eassert(_defaultValue.isValid() == false || _defaultValue.type() == _type);
    eassert(_currentValue.isValid() == false || _currentValue.type() == _type);
}

const string& FilterArgument::getName() const
{
    return _name;
}

bool FilterArgument::isSet() const
{
    return _currentValue.isValid();
}

void FilterArgument::setValue(QVariant v)
{
    _currentValue = v; // note : v can be invalid <=> isSet now equals false
}

const string FilterArgument::getType() const {
    const char* name = QVariant::typeToName(_type); // not a malloc ? crashes at delete
    string stringname(name);
    return stringname;
}


const QVariant& FilterArgument::getValue() const
{
    return _currentValue;
}

const QVariant& FilterArgument::getMin() const
{
    return _minValue;
}

const QVariant& FilterArgument::getMax() const
{
    return _maxValue;
}

const QVariant& FilterArgument::getDefault() const
{
    return _defaultValue;
}

const std::vector<QVariant>& FilterArgument::getDomainDefinition() const
{
    return _domainDefinition;
}
