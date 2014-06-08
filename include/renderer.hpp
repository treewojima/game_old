#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <SDL2/SDL.h>
#include "exception.hpp"
#include "texture.hpp"

class Renderer
{
public:
    virtual ~Renderer();

    virtual void blitTexture(Texture *texture, float x, float y) = 0;

    SDL_Window *getWindow() const;

protected:
    void setWindow(SDL_Window *window);

private:
    SDL_Window *_window;
};

#endif
