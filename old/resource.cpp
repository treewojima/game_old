#include "resource.hpp"

#include <sstream>

using namespace std;

Resource::Resource(const std::string &name, ResourceType type, bool delete_) :
    RefCounted(),
    _name(name),
    _type(type),
    _delete(delete_)
{
}

Resource::~Resource()
{
}

string Resource::toString()
{
    ostringstream ss;
    ss << "Resource<Name: " << _name << ", Type: " << _type << ">";
    return ss.str();
}
