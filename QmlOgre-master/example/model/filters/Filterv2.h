#ifndef FILTERV2_H
#define FILTERV2_H

#include <map>
#include <FilterArgument.h>
#include <iostream>

typedef std::map<std::string, FilterArgument*>::iterator farg_iterator;
typedef std::map<std::string, FilterArgument*>::const_iterator farg_const_iterator;

class FilterV2
{
public:
    //FilterArgumentsIterator getArgumentsIterator();
    farg_iterator begin(); // it->second <=> FilterArgument*
    farg_iterator end();
    unsigned int getNbArguments() const;
    FilterArgument* getArgument(std::string name);
    //const FilterArgument& getArgument(unsigned int i) const;

    bool addArgument(FilterArgument*);
    const std::string& getName() const;
    virtual bool canApply() const;

protected:
    FilterV2(std::string name);
    virtual ~FilterV2();

    std::map<std::string, FilterArgument*> _arguments;
    std::string _name;
};



/*class FilterArgumentsIterator {
public:
    FilterArgumentsIterator() {

    }

    FilterArgumentsIterator operator++() const {

    }


}*/

#endif // FILTERV2_H
