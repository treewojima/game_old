#include "renderers/sdlrenderer.hpp"

#include <SDL2/SDL.h>
#include "game.hpp"
#include "logger.hpp"

SDLRenderer::SDLRenderer()
{
    SDL_Window *window = SDL_CreateWindow("game",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH_PIXELS,
                                          SCREEN_HEIGHT_PIXELS,
                                          SDL_WINDOW_SHOWN);
    if (!window)
        throw SDLException();
    setWindow(window);

    _screen = SDL_GetWindowSurface(window);
}
