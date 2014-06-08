#ifndef __RESOURCE_HPP__
#define __RESOURCE_HPP__

#include <string>

#include "defines.hpp"
#include "refcounted.hpp"

enum ResourceType
{
    RT_TEXTURE
};

class Resource : public RefCounted
{
    friend class ResourceManager;

public:
    Resource(const std::string &name, ResourceType type, bool delete_);
    virtual ~Resource();

    std::string getName() { return _name; }
    ResourceType getType() { return _type; }

    virtual std::string toString();

private:
    std::string _name;
    ResourceType _type;
    bool _delete;
};

#endif
