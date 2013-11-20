#include "Filterv2.h"

using namespace std;

FilterV2::FilterV2(string name) :
    _name(name)
{}

FilterV2::~FilterV2()
{
    for (farg_iterator i = _arguments.begin(); i != _arguments.end(); ++i) {
        delete (*i).second;
    }
}

farg_iterator FilterV2::begin() {
    return _arguments.begin();
}

farg_iterator FilterV2::end() {
    return _arguments.end();
}

unsigned int FilterV2::getNbArguments() const {
    return _arguments.size();
}

FilterArgument* FilterV2::getArgument(string name) {
    farg_iterator it = _arguments.find(name);
    if (it != _arguments.end())
        return it->second;
    else
        return NULL;
}

/*const FilterArgument& FilterV2::getArgument(unsigned int i) const {
    return *(_arguments[i]);
}*/

bool FilterV2::addArgument(FilterArgument* arg) {
    if (_arguments.find(arg->getName()) == _arguments.end()) {
        _arguments[arg->getName()] = arg;
        return true;
    }
    return false;
}

bool FilterV2::canApply() const {
    for (farg_const_iterator i = _arguments.begin(); i != _arguments.end(); ++i) {
        if (i->second->isSet() == false)
            return false;
    }
    return true;
}

const std::string& FilterV2::getName() const {
    return _name;
}
