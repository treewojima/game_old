#ifndef __TUX_HPP__
#define __TUX_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Tux : public Entity
{
    friend class TuxContactListener;

public:
    Tux(float x, float y);

    void update(float dt);
    std::string toString();

private:
    bool _jumping;
};

#endif
