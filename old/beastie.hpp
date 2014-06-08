#ifndef __BEASTIE_HPP__
#define __BEASTIE_HPP__

#include "defines.hpp"
#include "entity.hpp"

class Beastie : public Entity
{
public:
    Beastie(float x, float y);

    std::string toString();
};

#endif
