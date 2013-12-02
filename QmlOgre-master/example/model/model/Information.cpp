#include <Information.h>


Information::~Information() { _informations.empty(); }

void
Information::addInformation(std::string title, std::string description)
{
    std::pair<std::string, std::string> info(title, description);
    _informations.insert(info);
}

std::string
Information::getTitle(int n)
{
    std::map<std::string, std::string>::iterator it;
    int i = 0;

    for (it = _informations.begin(); it != _informations.end() && i < n ; ++it, ++i);

    return it->first;
}

std::string
Information::getDescription(int n)
{
    std::map<std::string, std::string>::iterator it;
    int i = 0;

    for (it = _informations.begin(); it != _informations.end() && i < n ; ++it, ++i);

    return it->second;
}

int
Information::getSize()
{
    return _informations.size();
}

std::string
Information::get(std::string title)
{
    //if(_informations.find(title) != _informations.end())
        return _informations[title];
    //else
    //    return "Not foud";
}
