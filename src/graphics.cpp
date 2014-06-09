#include "graphics.hpp"

#include <fstream>
#include <GL/glew.h>
#include <iostream>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>
#include <string>

#include "defines.hpp"
#include "exception.hpp"
#include "game.hpp"
#include "logger.hpp"
#include "util.hpp"

using namespace std;

static GLuint vertexShader = 0, fragmentShader = 0, shaderProgram = 0;

namespace ColorMasks
{
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    const Uint32 RMASK = 0xff000000;
    const Uint32 GMASK = 0x00ff0000;
    const Uint32 BMASK = 0x0000ff00;
    const Uint32 AMASK = 0x000000ff;
#else
    const Uint32 RMASK = 0x000000ff;
    const Uint32 GMASK = 0x0000ff00;
    const Uint32 BMASK = 0x00ff0000;
    const Uint32 AMASK = 0xff000000;
#endif
}

void blitTexture(Texture *texture, float x, float y)
{
    getGame().getCurrentState().getRenderer().blitTexture(texture, x, y);
}

void blitTexture(Texture *texture, const Vector2f &pos)
{
    getGame().getCurrentState().getRenderer().blitTexture(texture, pos.x, pos.y);
}

void blitTexture(Texture *texture, const Vector2i &pos)
{
    getGame().getCurrentState().getRenderer().blitTexture(texture, pos.x, pos.y);
}

SDL_Surface *createBlankSurface(int width, int height, Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_Surface *surface = SDL_CreateRGBSurface(SDL_SWSURFACE, width,
        height, 32, ColorMasks::RMASK, ColorMasks::GMASK, ColorMasks::BMASK,
        ColorMasks::AMASK);
    if (!surface)
        throw SDLException();

    SDL_FillRect(surface, NULL, SDL_MapRGBA(surface->format, r, g, b, a));

    return surface;
}

GLuint copySurfaceToGL(SDL_Surface *surface,
                          bool optimize,
                          int *outWidth,
                          int *outHeight)
{
    GLuint retTexture;
    SDL_Surface *workingSurface = surface;

    //cout << "width = " << surface->w << ", height = " << surface->h << endl;

    if (optimize)
    {
        auto optimizedSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                     workingSurface->w,
                                                     workingSurface->h,
                                                     32,
                                                     ColorMasks::RMASK,
                                                     ColorMasks::GMASK,
                                                     ColorMasks::BMASK,
                                                     ColorMasks::AMASK);
        if (!optimizedSurface)
            throw SDLException();

        SDL_BlitSurface(workingSurface, NULL, optimizedSurface, NULL);
        workingSurface = optimizedSurface;
    }

    if (!isPowerOfTwo(workingSurface->w))
    {
        LOG_WARNING << "width of SDL_Surface (" << workingSurface->w
                    << ") is not a power of two" << endl;
    }
    if (!isPowerOfTwo(workingSurface->h))
    {
        LOG_WARNING << "height of SDL_Surface (" << workingSurface->h
                    << ") is not a power of two" << endl;
    }

    if (outWidth) *outWidth = workingSurface->w;
    if (outHeight) *outHeight = workingSurface->h;

    GLenum colorFormat;
    int numColors = workingSurface->format->BytesPerPixel;
    switch (numColors)
    {
    case 4:
        colorFormat = GL_RGBA;
        break;

    case 3:
        colorFormat = GL_RGB;
        break;

    default:
        throw SDLException("Surface is not truecolor");
    }

    glGenTextures(1, &retTexture);
    glBindTexture(GL_TEXTURE_2D, retTexture);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 numColors,
                 workingSurface->w,
                 workingSurface->h,
                 0,
                 colorFormat,
                 GL_UNSIGNED_BYTE,
                 workingSurface->pixels);
    if (optimize)
        SDL_FreeSurface(workingSurface);

    glGenerateMipmap(GL_TEXTURE_2D);

    return retTexture;
}

void initShaders()
{
    // TODO: make all this more... elegant

    // Load vertex shader source
    string contents = readFileContents("res/shaders/vert.glsl");
    const char *contentsPtr = contents.c_str();
    int contentsSize = contents.size();

    // Compile the shader
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, (const GLchar **)&contentsPtr, &contentsSize);
    glCompileShader(vertexShader);
    GLint status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        // Something went wrong during compilation
        char errorBuffer[512];
        glGetShaderInfoLog(vertexShader, 512, NULL, errorBuffer);
        std::ostringstream oss;
        oss << "error compiling vertex shader - dumping compilation log\n\n"
            << errorBuffer;
        throw GLException(oss.str());
    }

    // Now do the same for the fragment shader
    contents = readFileContents("res/shaders/frag.glsl");
    contentsPtr = contents.c_str();
    contentsSize = contents.size();

    // Compile the shader
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, (const GLchar **)&contentsPtr, &contentsSize);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status != GL_TRUE)
    {
        // Something went wrong during compilation
        char errorBuffer[512];
        glGetShaderInfoLog(fragmentShader, 512, NULL, errorBuffer);
        std::ostringstream oss;
        oss << "error compiling fragment shader - dumping compilation log\n\n"
            << errorBuffer;
        throw GLException(oss.str());
    }

    // Create the shader program
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram);
}

void destroyShaders()
{
    glDeleteProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}
