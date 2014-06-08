#ifndef __REFCOUNTED_HPP__
#define __REFCOUNTED_HPP__

#include <string>

class RefCounted
{
public:
    RefCounted();
    virtual ~RefCounted();

    int grab() { return ++_refCount; }
    int drop();
    int getRefCount() { return _refCount; }

    virtual std::string toString() const;

private:
    int _refCount;
    bool _resourcesReleased;
};

#endif
