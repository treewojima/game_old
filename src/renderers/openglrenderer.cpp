#include "renderers/openglrenderer.hpp"

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include "game.hpp"
#include "logger.hpp"

OpenGLRenderer::OpenGLRenderer(int windowWidth, int windowHeight)
{
    /*
     * First, set up SDL for OpenGL rendering
     */

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    SDL_Window *window = SDL_CreateWindow("game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          windowWidth,
                                          windowHeight,
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
    glViewport(0, 0, windowWidth, windowHeight);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, windowWidth * PTM_RATIO, 0, windowHeight * PTM_RATIO);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    errorCode = glGetError();
    if (errorCode != GL_NO_ERROR)
        throw GLException(errorCode);

    LOG_INFO << "Using OpenGL for rendering" << endl;
}

OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(_glContext);
}

void OpenGLRenderer::blitTexture(Texture *texture, float x, float y) const
{
    const float width = texture->getWidth();
    const float height = texture->getHeight();
    const float centeredWidth = width / 2.f;
    const float centeredHeight = height / 2.f;

    glBindTexture(GL_TEXTURE_2D, texture->getTexture());
    //glTranslatef(x, y, 0);
    glTranslatef(x - centeredWidth, y - centeredHeight, 0);
    glBegin(GL_QUADS);
        glTexCoord2i(1, 1);
        //glVertex2f(centeredWidth, -centeredHeight);
        glVertex2f(width, 0);

        glTexCoord2i(0, 1);
        //glVertex2f(-centeredWidth, -centeredHeight);
        glVertex2f(0, 0);

        glTexCoord2i(0, 0);
        //glVertex2f(-centeredWidth, centeredHeight);
        glVertex2f(0, height);

        glTexCoord2i(1, 0);
        //glVertex2f(centeredWidth, centeredHeight);
        glVertex2f(width, height);
    glEnd();

    glLoadIdentity();
}

void OpenGLRenderer::clear() const
{
    glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::present() const
{
    SDL_GL_SwapWindow(getWindow());
}
