#ifndef __GRAPHICS_HPP__
#define __GRAPHICS_HPP__

#include "defines.hpp"
#include "texture.hpp"
#include "util.hpp"
#include "vector.hpp"

// Blit a texture to the screen
void blitTexture(Texture *texture, float x, float y);

// Create a blank surface, initialized to an RGBA color
SDL_Surface *createBlankSurface(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a);

// Copy an SDL surface into OpenGL texture memory
GLuint copySurfaceToGL(SDL_Surface *surface, bool optimize,
    int *outWidth = NULL, int *outHeight = NULL);

// Initialize and destroy OpenGL shader
void initShaders();
void destroyShaders();

// Overloaded blitting functions taking vectors instead of separate coordinates
inline void blitTexture(Texture *texture, const Vector2f &pos)
{
    blitTexture(texture, pos.x, pos.y);
}

inline void blitTexture(Texture *texture, const Vector2i &pos)
{
    blitTexture(texture, pos.x, pos.y);
}

// Platform-dependent colormasks
namespace ColorMasks
{
    extern const Uint32 RMASK;
    extern const Uint32 GMASK;
    extern const Uint32 BMASK;
    extern const Uint32 AMASK;
}

#endif
