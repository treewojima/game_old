#ifndef __SDLRENDERER_HPP__
#define __SDLRENDERER_HPP__

#include <SDL2/SDL.h>
#include "renderer.hpp"

class SDLRenderer : public Renderer
{
public:
    SDLRenderer();
    //virtual ~SDLRenderer();

    void blitTexture(Texture *texture, float x, float y);

private:
    SDL_Surface *_screen;
};

#endif
