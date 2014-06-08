#ifndef __RESOURCEMANAGER_HPP__
#define __RESOURCEMANAGER_HPP__

#include <cassert>
#include <map>
#include <sstream>
#include <string>

#include "defines.hpp"
#include "exception.hpp"

template <class T>
class ResourceManager
{
public:
    ~ResourceManager();

    void addResource(T *r);
    void delResource(const std::string &name);
    T *getResource(const std::string &name);

private:
    std::map<std::string, T *> _resourceMap;
};

template <class T>
ResourceManager<T>::~ResourceManager()
{
    for (auto i = _resourceMap.begin(); i != _resourceMap.end(); i++)
        delete i->second;

    _resourceMap.clear();
}

template <class T>
void ResourceManager<T>::addResource(T *r)
{
    // TODO: add code to check for duplicate resources

    assert(r);
    _resourceMap[r->getName()] = r;
}

template <class T>
void ResourceManager<T>::delResource(const std::string &name)
{
    auto i = _resourceMap.find(name);
    if (i == _resourceMap.end())
    {
        std::ostringstream ss;
        ss << "Tried to remove nonexistent resource " << i->second->toString();
        throw Exception(ss.str());
    }
    delete i->second;
    _resourceMap.erase(i);
}

template <class T>
T *ResourceManager<T>::getResource(const std::string &name)
{
    auto *r = _resourceMap[name];
    r->grab();
    return r;
}

class Texture;
typedef ResourceManager<Texture> TextureManager;

#endif
