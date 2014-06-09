#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

#include "defines.hpp"
#include "texture.hpp"
#include "util.hpp"
#include "vector.hpp"

// Create a blank surface, initialized to an RGBA color
SDL_Surface *createBlankSurface(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// Copy an SDL surface into OpenGL texture memory
GLuint copySurfaceToGL(SDL_Surface *surface, bool optimize,
    int *outWidth = NULL, int *outHeight = NULL);

// Initialize and destroy OpenGL shader
void initShaders();
void destroyShaders();

// Blitting functions
void blitTexture(Texture *texture, float x, float y);
void blitTexture(Texture *texture, const Vector2f &pos);
void blitTexture(Texture *texture, const Vector2i &pos);

// Platform-dependent colormasks
namespace ColorMasks
{
    extern const Uint32 RMASK;
    extern const Uint32 GMASK;
    extern const Uint32 BMASK;
    extern const Uint32 AMASK;
}

#endif
