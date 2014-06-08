#include "entity.hpp"

#include <cassert>
#include <iostream>
//#include <SDL/SDL_opengl.h>

#include "defines.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "logger.hpp"
#include "util.hpp"

using namespace std;

Entity::Entity(const string &name) :
    _texture(NULL),
    _body(NULL),
    _name(name),
    _alive(true),
    _visible(true)
{
}

Entity::Entity(const string &name, Texture *texture) :
    _texture(texture),
    _body(NULL),
    _name(name),
    _alive(true),
    _visible(true)
{
    if (!texture)
        throw Exception(format("NULL texture passed to entity %s", toString().c_str()));
}

Entity::~Entity()
{
    if (_alive)
        kill();
}

void Entity::update(float dt)
{
    if (_body)
        position.set(_body->GetPosition());

    //if (_contacting)
    //    LOG_INFO << "Contacting!" << endl;
}

void Entity::draw()
{
    blitTexture(_texture, position.x, position.y);
}

void Entity::kill()
{
    assert(_alive);

    _texture->drop();

    if (_body)
        getWorld()->DestroyBody(_body);

    _alive = false;
}

float Entity::getWidth()
{
    if (_texture)
        return _texture->getWidth();

    return 0;
}

float Entity::getHeight()
{
    if (_texture)
        return _texture->getHeight();

    return 0;
}

SDL_Rect Entity::getBoundingBox()
{
    SDL_Rect r;
    r.x = position.x;
    r.y = position.y;
    r.w = _texture->getWidth();
    r.h = _texture->getHeight();

    return r;
}

string Entity::toString()
{
    ostringstream ss;
    ss << "Entity<Name: '" << getName() << "', Position: "
       << position.toString() << ">";
    return ss.str();
}
