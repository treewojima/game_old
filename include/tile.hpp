#if 0

#ifndef __TILE_HPP__
#define __TILE_HPP__

#include "entity.hpp"
#include "vector.hpp"

#include <string>

extern const int TILE_WIDTH, TILE_HEIGHT;
extern const int LEVEL_WIDTH_PIXELS, LEVEL_HEIGHT_PIXELS;

enum
{
    TILE_RED = 0,
    TILE_GREEN,
    TILE_BLUE,
    TILE_CENTER,
    TILE_TOP,
    TILE_TOPRIGHT,
    TILE_RIGHT,
    TILE_BOTTOMRIGHT,
    TILE_BOTTOM,
    TILE_BOTTOMLEFT,
    TILE_LEFT,
    TILE_TOPLEFT,

    NUM_TILES
};

class Tile : public Entity
{
public:
    Tile(const std::string &name, Vector2f pos, int type);

    virtual void update();
    virtual void draw();
    virtual void kill();

    int getType() const { return _type; }

    SDL_Rect getBoundingBox() const;
    std::string toString() const;

    Vector2f position;

private:
    int _type;
    SDL_Rect _box;
};

#endif

#endif
