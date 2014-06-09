#ifndef __OPENGLRENDERER_HPP__
#define __OPENGLRENDERER_HPP__

#include <SDL2/SDL.h>
#include "renderer.hpp"

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer(int windowWidth, int windowHeight);
    virtual ~OpenGLRenderer();

    virtual void blitTexture(Texture *texture, float x, float y) const;
    virtual void clear() const;
    virtual void present() const;

private:
    SDL_GLContext _glContext;
};

#endif
