#if 0

#include "tile.hpp"

#include <SDL2/SDL.h>

const int TILE_WIDTH = 80;
const int TILE_HEIGHT = 80;
const int LEVEL_WIDTH_PIXELS = 1280;
const int LEVEL_HEIGHT_PIXELS = 960;

Tile::Tile(const std::string &name, Vector2f pos, int type) :
    Entity(name),
    position(pos),
    type(type)
{
    _box.x = pos.x;
    _box.y = pos.y;
    _box.w = TILE_WIDTH;
    _box.h = TILE_HEIGHT;
}

void Tile::update()
{

}

void Tile::draw()
{

}

void Tile::kill()
{

}

#endif
