#ifndef __EXCEPTION_HPP__
#define __EXCEPTION_HPP__

#include <GL/glew.h>
//#include <GL/glu.h>
#include <SDL2/SDL.h>
//#include <SDL2/SDL_opengl.h>
#include <sstream>
#include <string>

#include "defines.hpp"

class Exception
{
public:
    Exception() {}
    Exception(const std::string &msg) : _msg(msg) {}

    const std::string &getMsg() { return _msg; }

protected:
    std::string _msg;
};

class SDLException : public Exception
{
public:
    SDLException(const std::string &msg) : Exception(msg) {}
    
    SDLException() : Exception(SDL_GetError()) {}
};

class GLException : public Exception
{
public:
    GLException(const std::string &msg) : Exception(msg) {}

    GLException(GLenum error)
    {
        std::ostringstream ss;
        ss << getErrorString(error);
        _msg = ss.str();
    }

protected:
    virtual const GLubyte *getErrorString(GLenum error)
    {
        return gluErrorString(error);
    }
};

class GLEWException : public GLException
{
public:
    GLEWException(const std::string &msg) : GLException(msg) {}
    GLEWException(GLenum error) : GLException(error) {}

protected:
    const GLubyte *getErrorString(GLenum error)
    {
        return glewGetErrorString(error);
    }
};

class RefCountException : public Exception
{
public:
    RefCountException(const std::string &msg) : Exception(msg) {}
};

#endif
