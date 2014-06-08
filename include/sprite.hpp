#ifndef __SPRITE_HPP__
#define __SPRITE_HPP__

//#include <Box2D/Box2D.h>
#include <string>

#include "defines.hpp"
#include "entity.hpp"
#include "texture.hpp"
#include "vector.hpp"

class Sprite : public Entity
{
public:
    Sprite(const std::string &name, Texture *texture);

protected:
    Sprite(const std::string &name);

public:
    void update();
    void draw();
    void kill();

    virtual float getWidth() const;
    virtual float getHeight() const;

    Vector2f position;
    Vector2f velocity;

    std::string toString() const;

protected:
    Texture *_texture;
    //b2Body *_body;
};

#endif
