#ifndef __ENTITY_HPP__
#define __ENTITY_HPP__

#include <string>

#include "defines.hpp"

class Entity
{
public:
    Entity(const std::string &name);
    virtual ~Entity();

    virtual void update() = 0;
    virtual void draw();
    virtual void kill();

    std::string getName() const { return _name; }
    bool isAlive() const { return _alive; }
    bool isVisible() const { return _visible; }

    void setVisible(bool visible) { _visible = visible; }

    virtual std::string toString() const;

protected:
    //void setAlive(bool alive) { _alive = alive; }

private:
    std::string _name;
    bool _alive;
    bool _visible;
};

#endif
