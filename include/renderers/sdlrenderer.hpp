#ifndef __SDLRENDERER_HPP__
#define __SDLRENDERER_HPP__

#include <SDL2/SDL.h>
#include "renderer.hpp"

class SDLRenderer : public Renderer
{
public:
    SDLRenderer(int windowWidth, int windowHeight);
    //virtual ~SDLRenderer();

    virtual void blitTexture(Texture *texture, float x, float y) const;
    virtual void clear() const;
    virtual void present() const;

private:
    SDL_Surface *_screen;
};

#endif
