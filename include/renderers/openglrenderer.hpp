#ifndef __OPENGLRENDERER_HPP__
#define __OPENGLRENDERER_HPP__

#include <SDL2/SDL.h>
#include "renderer.hpp"

class OpenGLRenderer : public Renderer
{
public:
    OpenGLRenderer();
    virtual ~OpenGLRenderer();

    void blitTexture(Texture *texture, float x, float y);

private:
    SDL_GLContext *_glContext;
};

#endif
