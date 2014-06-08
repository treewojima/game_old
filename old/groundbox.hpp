#ifndef __GROUND_HPP__
#define __GROUND_HPP__

#include "defines.hpp"
#include "entity.hpp"

class GroundBox : public Entity
{
public:
    GroundBox();

    std::string toString();
};

#endif
