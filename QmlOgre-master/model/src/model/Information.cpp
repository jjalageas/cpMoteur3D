#include <Information.h>


Information::~Information() { _informations.empty(); }

void
Information::addInformation(std::string title, std::string description)
{
    Pair_t<std::string, std::string> info(title, description);
    _informations.add(info);
}

std::string
Information::getTitle(int n)
{
    return _informations.get(n).first;
}

std::string
Information::getDescription(int n)
{
    return _informations.get(n).second;
}

int
Information::getSize()
{
    return _informations.size();
}
