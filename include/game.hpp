#ifndef __GAME_HPP__
#define __GAME_HPP__

//#include <Box2D/Box2D.h>

#include "defines.hpp"
#include "entity.hpp"
#include "resourcemanager.hpp"

extern const int SCREEN_WIDTH_PIXELS;
extern const int SCREEN_HEIGHT_PIXELS;
extern const float SCREEN_WIDTH;
extern const float SCREEN_HEIGHT;

bool isRunning();
void setRunning(bool b);
Entity *getPlayer();
void setPlayer(Entity *e);
//b2World *getWorld();
TextureManager *getTexMgr();

#endif
