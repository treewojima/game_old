#ifndef __RENDERER_HPP__
#define __RENDERER_HPP__

#include <SDL2/SDL.h>
#include "exception.hpp"
#include "texture.hpp"

class Renderer
{
public:
    Renderer();
    virtual ~Renderer();

    // These are basic graphics functions that every renderer must support
    virtual void blitTexture(Texture *texture, float x, float y) const = 0;
    virtual void clear() const = 0;
    virtual void present() const = 0;

    inline SDL_Window *getWindow() const { return _window; }

protected:
    void setWindow(SDL_Window *window);

private:
    SDL_Window *_window;
};

#endif
