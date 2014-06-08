#ifndef __TEXTURE_HPP__
#define __TEXTURE_HPP__

#include <GL/glew.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>
#include <string>

#include "defines.hpp"
#include "refcounted.hpp"
#include "util.hpp"

class Texture : public RefCounted
{
public:
    Texture(const std::string &name, const std::string &filename);
    Texture(const std::string &name, SDL_Surface *surface,
            bool optimize, bool freeSurface);
    ~Texture();

    std::string getName() { return _name; }
    float getWidth() { return _width; }
    float getHeight() { return _height; }
    GLuint getTexture() { return _texture; }
    
    std::string toString() const;

private:
    std::string _name;
    float _width, _height;
    GLuint _texture;
};

#endif

