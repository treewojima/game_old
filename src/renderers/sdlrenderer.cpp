#include "renderers/sdlrenderer.hpp"

#include <SDL2/SDL.h>
#include "game.hpp"
#include "logger.hpp"

SDLRenderer::SDLRenderer(int windowWidth, int windowHeight)
{
    SDL_Window *window = SDL_CreateWindow("game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          windowWidth,
                                          windowHeight,
                                          SDL_WINDOW_SHOWN);
    if (!window)
        throw SDLException();
    setWindow(window);

    _screen = SDL_GetWindowSurface(window);

    LOG_INFO << "Using SDL for rendering" << endl;

    SDL_FillRect(_screen, NULL, SDL_MapRGB(_screen->format, 0xFF, 0xFF, 0xFF));
    SDL_UpdateWindowSurface(window);
}

void SDLRenderer::blitTexture(Texture *texture, float x, float y) const
{
}

void SDLRenderer::clear() const
{
}

void SDLRenderer::present() const
{
}
