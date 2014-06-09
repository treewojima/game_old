#include "renderer.hpp"

#include "logger.hpp"

using namespace std;

Renderer::Renderer()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        throw SDLException();

    SDL_version ver;
    SDL_GetVersion(&ver);

    LOG_INFO << "SDL " << ver.major <<
                "." << ver.minor <<
                "." << ver.patch <<
                " initialized" << endl;
}

Renderer::~Renderer()
{
    if (!_window)
    {
        LOG_ERROR << "SDL window reference is NULL in ~Renderer" << endl;
        throw SDLException();
    }

    SDL_DestroyWindow(_window);
    SDL_Quit();
}

void Renderer::setWindow(SDL_Window *window)
{
    if (!window)
        throw Exception("NULL window passed to Renderer::setWindow()");

    _window = window;
}
