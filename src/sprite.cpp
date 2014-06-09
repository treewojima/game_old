#include "sprite.hpp"

#include <iostream>
#include <sstream>

#include "defines.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "graphics.hpp"
#include "util.hpp"

using namespace std;

Sprite::Sprite(const string &name, Texture *texture) :
    Entity(name),
    _texture(texture)
    //_body(NULL)
{
    if (!texture)
    {
        ostringstream ss;
        ss << "NULL texture passed to sprite " << toString();
        throw Exception(ss.str());
    }
}

Sprite::Sprite(const string &name) :
    Entity(name),
    _texture(NULL)
    //_body(NULL)
{
}

void Sprite::update()
{
    //if (_body)
    //    position.set(_body->GetPosition());
}

void Sprite::draw()
{
    blitTexture(_texture, position);
}

void Sprite::kill()
{
    assert(isAlive());

    _texture->drop();

    //if (_body)
    //    getWorld()->DestroyBody(_body);

    //setAlive(false);
    Entity::kill();
}

float Sprite::getWidth() const
{
    return _texture->getWidth();
}

float Sprite::getHeight() const
{
    return _texture->getHeight();
}

string Sprite::toString() const
{
    ostringstream ss;
    ss << "Sprite<Name: '" << getName() << "', Position: "
       << position.toString() << ">";
    return ss.str();
}
