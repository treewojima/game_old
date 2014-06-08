#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <Box2D/Box2D.h>
#include <string>

#include "defines.hpp"
#include "texture.hpp"
#include "vector.hpp"

class Entity
{
public:
    Entity(const std::string &name);
    Entity(const std::string &name, Texture *texture);
    //Entity(const std::string &name, SDL_Surface *surface, bool optimize,
    //       bool freeSurface);
    virtual ~Entity();

    virtual void update(float dt);
    virtual void draw();
    virtual void kill();

    std::string getName() { return _name; }
    bool isAlive() { return _alive; }
    bool isVisible() { return _visible; }
    void setVisible(bool visible) { _visible = visible; }
    float getWidth();
    float getHeight();

    virtual SDL_Rect getBoundingBox();
    virtual std::string toString();

    Vector2f position;
    Vector2f velocity;

protected:
    void setAlive(bool alive) { _alive = alive; }

    void startContact() { _contacting = true; }
    void endContact() { _contacting = false; }

    Texture *_texture;
    b2Body *_body;
    //bool _obeysPhysics;

private:
    std::string _name;
    bool _alive;
    bool _visible;
    bool _contacting;
};

#endif
