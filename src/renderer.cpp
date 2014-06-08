#include "renderer.hpp"

Renderer::~Renderer()
{
    SDL_DestroyWindow(_window);
}

inline SDL_Window *Renderer::getWindow() const
{
    return _window;
}

void Renderer::setwindow(SDL_Window *window)
{
    if (!window)
        throw Exception("NULL window passed to Renderer::setWindow()");

    _window = window;
}
