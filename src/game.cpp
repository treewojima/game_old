#include "game.hpp"

#include <cassert>
#include <functional>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <sstream>
#include <vector>

#include "exception.hpp"
#include "defines.hpp"
#include "graphics.hpp"
#include "logger.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "util.hpp"

using std::cout;
using std::endl;

const int SCREEN_WIDTH_PIXELS = 800;
const int SCREEN_HEIGHT_PIXELS = 600;
const float SCREEN_WIDTH = SCREEN_WIDTH_PIXELS * PTM_RATIO;
const float SCREEN_HEIGHT = SCREEN_HEIGHT_PIXELS * PTM_RATIO;

static SDL_Window *window = NULL;
static SDL_GLContext glContext = NULL;
static bool running = false;
static Entity *player = NULL;
static bool trackMouse = false;
static bool showFrameRate = false;
static TextureManager *texMgr;
static GLuint vao, vbo;

static void runGame(int argc, char *argv[]);
static void initSDL();
static void initGL();
static void loadTextures();
static void handleEvents();
static void loadPolygons();
static void destroyPolygons();

int main(int argc, char *argv[])
{
    try
    {
        LOG_INFO << "Game started" << endl;
        runGame(argc, argv);
    }
    catch (SDLException e)
    {
        LOG_ERROR << "caught SDL exception: " << e.getMsg() << endl;
    }
    catch (GLException e)
    {
        LOG_ERROR << "caught OpenGL exception: " << e.getMsg() << endl;
    }
    catch (GLEWException e)
    {
        LOG_ERROR << "caught GLEW exception: " << e.getMsg() << endl;
    }
    catch (Exception e)
    {
        LOG_ERROR << "caught exception: " << e.getMsg() << endl;
    }
    catch (...)
    {
        LOG_ERROR << "unknown error" << endl;
    }
}

bool isRunning()
{
    return running;
}

void setRunning(bool b)
{
    running = b;
}

Entity *getPlayer()
{
    return player;
}

void setPlayer(Entity *e)
{
    if (!e) throw Exception("tried to set player entity to NULL");

    player = e;
}

TextureManager *getTexMgr()
{
    return texMgr;
}

void runGame(int argc, char *argv[])
{
    // Initialize SDL and OpenGL
    initSDL();
    initGL();
    //initShaders();

    // Load resources
    texMgr = new TextureManager();
    loadTextures();

    // Create entities
    Sprite tux("Tux", texMgr->getResource("Tux"));
    tux.position.set(p2m(400), p2m(300));

    // The main loop
    setRunning(true);
    while (isRunning())
    {
        Uint32 startTicks;
        if (showFrameRate)
            startTicks = SDL_GetTicks();

        // Watch out for any tricky stuff
        // TODO: try to guard against these in other places once this system is
        //       more developed
        //assert(player);

        // Dispatch main window and game events
        handleEvents();

        // Update entity positions and logic
        tux.update();

        // Draw the scene
        glClear(GL_COLOR_BUFFER_BIT);

        tux.draw();

        SDL_GL_SwapWindow(window);

        // Calculate FPS if required
        if (showFrameRate)
        {
            auto frameTicks = SDL_GetTicks() - startTicks;
            float fps = frameTicks > 0 ? 1000.f / frameTicks : 0;
            cout << "FPS: " << fps << endl;
        }
    }

    // Clean up
    tux.kill();
    //delete world;
    delete texMgr;
    //destroyPolygons();
    //destroyShaders();
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) == -1)
        throw SDLException();

    SDL_version ver;
    SDL_GetVersion(&ver);

    LOG_INFO << "SDL " << ver.major <<
                "." << ver.minor <<
                "." << ver.patch <<
                " initialized" << endl;

    /*
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    window = SDL_CreateWindow("game",
                              SDL_WINDOWPOS_UNDEFINED,
                              SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH_PIXELS,
                              SCREEN_HEIGHT_PIXELS,
                              SDL_WINDOW_OPENGL);
    if (!window)
        throw SDLException();

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
        throw SDLException();
        */
}

void initGL()
{
    auto errorCode = glewInit();
    if (errorCode != GLEW_OK)
        throw GLEWException(errorCode);

    LOG_INFO << "GLEW "
             << reinterpret_cast<const char *>(glewGetString(GLEW_VERSION))
             << " initialized" << endl;

    if (!GLEW_ARB_vertex_shader)
        throw GLEWException("platform does not support vertex shaders");

    if (!GLEW_ARB_fragment_shader)
        throw GLEWException("platform does not support fragment shaders");

    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);

    glClearColor(0, 0, 0, 0);
    glViewport(0, 0, SCREEN_WIDTH_PIXELS, SCREEN_HEIGHT_PIXELS);
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    errorCode = glGetError();
    if (errorCode != GL_NO_ERROR)
        throw GLException(errorCode);
}

void loadTextures()
{
    texMgr->addResource(new Texture("Tux", "res/textures/tux.png"));
}

void handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            LOG_INFO << "Received quit event" << endl;
            setRunning(false);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                LOG_INFO << "Received quit event (escape was pressed)" << endl;
                setRunning(false);
                break;

            case SDLK_F1:
                showFrameRate = !showFrameRate;
                LOG_INFO << "FPS display "
                         << (showFrameRate ? "enabled" : "disabled") << endl;
                break;

            case SDLK_F2:
                trackMouse = !trackMouse;
                LOG_INFO << "Mouse tracking "
                         << (trackMouse ? "enabled" : "disabled") << endl;
                break;

            default: break;
            }
        }
        else if (event.type == SDL_MOUSEMOTION && trackMouse)
        {
            cout << "X = " << event.motion.x
                 << " , Y = " << event.motion.y
                 << " (Xmeters = " << p2m(event.motion.x)
                 << ", Ymeters = " << p2m(SCREEN_HEIGHT_PIXELS - event.motion.y)
                 << ")" << endl;
        }
    }
}
