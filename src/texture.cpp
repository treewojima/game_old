#include "texture.hpp"

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "defines.hpp"
#include "exception.hpp"
#include "graphics.hpp"
#include "logger.hpp"
#include "util.hpp"

using namespace std;

Texture::Texture(const string &name,
                 const string &filename) :
    _name(name),
    _width(0),
    _height(0),
    _texture(0)
{
    SDL_Surface *surface = IMG_Load(filename.c_str());
    if (!surface)
        throw SDLException();

    int width, height;
    _texture = copySurfaceToGL(surface, true, &width, &height);
    _width = p2m(width);
    _height = p2m(height);
    //cout << width << ", " << height << endl;
    //cout << _width << ", " << _height << endl;
    SDL_FreeSurface(surface);
}

Texture::Texture(const string &name,
                 SDL_Surface *surface,
                 bool optimize,
                 bool freeSurface) :
    _name(name),
    _width(0),
    _height(0),
    _texture(0)
{
    if (!surface)
        throw SDLException("NULL surface passed to Texture constructor");

    int width, height;
    _texture = copySurfaceToGL(surface, optimize, &width, &height);
    _width = p2m(width);
    _height = p2m(height);

    if (freeSurface) SDL_FreeSurface(surface);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_texture);
}

std::string Texture::toString() const
{
    ostringstream ss;
    ss << "Texture<ID = " << _texture << ">";
    return ss.str();
}
