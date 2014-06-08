#include "renderers/openglrenderer.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "game.hpp"
#include "logger.hpp"

OpenGLRenderer::OpenGLRenderer()
{
    /*
     * First, set up SDL for OpenGL rendering
     */

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window *window = SDL_CreateWindow("game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH_PIXELS,
                                          SCREEN_HEIGHT_PIXELS,
                                          SDL_WINDOW_OPENGL);
    if (!window)
        throw SDLException();
    setWindow(window);

    _glContext = SDL_GL_CreateContext(window);
    if (!_glContext)
        throw SDLException();

    /*
     * Now configure OpenGL directly
     */

    auto errorCode = glewInit();
    if (errorCode != GLEW_OK)
        throw GLEWException(errorCode);

    LOG_INFO << "GLEW "
             << reinterpret_cast<const char *>(glewGetString(GLEW_VERSION))
             << " initialized" << endl;

    if (!GLEW_ARB_vertex_shader)
        throw GLEWException("platform does not support vertex shaders");

    if (!GLEW_ARB_fragment_shader)
        throw GLEWException("platform does not support fragment shaders");

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, SCREEN_WIDTH_PIXELS, SCREEN_HEIGHT_PIXELS);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    errorCode = glGetError();
    if (errorCode != GL_NO_ERROR)
        throw GLException(errorCode);
}

OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(_glContext);
}


