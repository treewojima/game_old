#include "entity.hpp"

#include <cassert>
#include <iostream>
#include <sstream>

using namespace std;

Entity::Entity(const string &name) :
    _name(name),
    _alive(true),
    _visible(true)
{
}

Entity::~Entity()
{
    // I forgot why this is commented out
    //if (_alive)
    //    kill();
}

void Entity::draw()
{
    // Default implementation is to do nothing
}

void Entity::kill()
{
    assert(_alive);

    _alive = false;
}

string Entity::toString() const
{
    ostringstream ss;
    //ss << "Entity<Name: '" << getName() << "', Position: "
    //   << position.toString() << ">";
    ss << "Entity<Name: '" << getName() << "'>";
    return ss.str();
}
