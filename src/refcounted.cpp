#include "refcounted.hpp"

#include <sstream>

#include "exception.hpp"
#include "logger.hpp"

using namespace std;

RefCounted::RefCounted() : _refCount(0)
{
}

RefCounted::~RefCounted()
{
    ostringstream ss;

    if (_refCount > 0)
    {
        ss << "Deleted object " << toString() << " has " << getRefCount()
           << " active reference" << (_refCount > 1 ? "s" : "");

        // Throwing exceptions in any destructor in C++ causes an error
        //throw RefCountException(ss.str());

        LOG_ERROR << ss.str() << endl;

        /*if (!this->_forceReleaseFunc())
        {
            ss.str("");
            ss << "Forced release of resources for " << toString() << " failed";
            LOG_ERROR << ss.str() << endl;
        }*/
    }
    else if (_refCount < 0) // This should be caught in drop() before it ever
                            // gets here
    {
        ss << "Deleted object " << toString() << " has a negative reference "
           << "count (" << _refCount << "); why wasn't this caught earlier?";

        // See above
        //throw RefCountException(ss.str());

        LOG_ERROR << ss.str() << endl;

        /*if (!this->_forceReleaseFunc())
        {
            ss.str("");
            ss << "Forced release of resources for " << toString() << " failed";
            LOG_ERROR << ss.str() << endl;
        }*/
    }
}

int RefCounted::drop()
{
    _refCount--;
    if (_refCount < 0)
    {
        ostringstream ss;
        ss << "Deleted object " << toString() << " has a negative reference "
           << "count (" << _refCount << ")";
        throw RefCountException(ss.str());
    }
    return _refCount;
}

string RefCounted::toString() const
{
    ostringstream ss;
    ss << "RefCounted<RefCount: " << _refCount << ">";
    return ss.str();
}
