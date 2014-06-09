#include "game.hpp"

#include <cassert>
#include <functional>
#include <GL/glew.h>
#include <iostream>
#include <string>
#include <SDL2/SDL.h>
#include <sstream>
#include <tclap/CmdLine.h>
#include <vector>

#include "exception.hpp"
#include "defines.hpp"
#include "graphics.hpp"
#include "logger.hpp"
#include "renderer.hpp"
#include "renderers/openglrenderer.hpp"
#include "renderers/sdlrenderer.hpp"
#include "resourcemanager.hpp"
#include "sprite.hpp"
#include "texture.hpp"
#include "util.hpp"

using std::cout;
using std::endl;

static const GameSettings DEFAULTS = { 800, 600, false };

static Game *globalGame;

GameState::GameState()
{
    // Initialize default values
    _settings = DEFAULTS;
    _renderer = NULL;
    _running = false;
    //_player = NULL;
    _trackMouse = false;
    _showFrameRate = false;
    _texMgr = NULL;
    //_vao = -vbo = 0;
}

GameState::~GameState()
{
    delete _texMgr;
    _texMgr = NULL;

    delete _renderer;
    _renderer = NULL;
}

Game::Game(int argc, char *argv[])
{
    // First, set up our game state and prepare our command line parser
    _currentState = new GameState();
    TCLAP::CmdLine cmdLine("teh game");
    auto argOpenGL = new TCLAP::SwitchArg("", "opengl",
                                          "render using OpenGL");
    cmdLine.add(argOpenGL);
    cmdLine.parse(argc, argv);

    // Parse any arguments and update settings appropriately
    parseArgs(cmdLine);
}

Game::~Game()
{
    delete _currentState;
    _currentState = NULL;
}

void Game::run()
{
    const int screenWidth = getCurrentState().getSettings().windowWidth;
    const int screenHeight = getCurrentState().getSettings().windowHeight;

    // Create either an OpenGL or standard SDL renderer
    if (getCurrentState().getSettings().useOpenGL)
    {
        _currentState->_renderer =
                new OpenGLRenderer(screenWidth, screenHeight);
    }
    else
    {
        _currentState->_renderer =
                new SDLRenderer(screenWidth, screenHeight);
    }
    if (!getCurrentState()._renderer)
        throw Exception("what the fuck yo");

    // The main loop
    _currentState->_running = true;
    while (getCurrentState().isRunning())
    {
        Uint32 startTicks;
        if (getCurrentState()._showFrameRate)
            startTicks = SDL_GetTicks();

        // Watch out for any tricky stuff
        // TODO: try to guard against these in other places once this system is
        //       more developed
        //assert(player);

        // Dispatch main window and game events
        handleEvents();

        // Draw the scene
        getCurrentState().getRenderer().clear();
        getCurrentState().getRenderer().present();

        // Calculate FPS if required
        if (getCurrentState()._showFrameRate)
        {
            auto frameTicks = SDL_GetTicks() - startTicks;
            float fps = frameTicks > 0 ? 1000.f / frameTicks : 0;
            cout << "FPS: " << fps << endl;
        }
    }
}

void Game::parseArgs(TCLAP::CmdLine &cmdLine)
{
    auto args = cmdLine.getArgList();

    for (auto i = args.begin(); i != args.end(); i++)
    {
        if ((*i)->getName() == "opengl")
        {
            _currentState->_settings.useOpenGL = true;
        }
        else
        {
            _currentState->_settings.useOpenGL = false;
        }
    }
}

void Game::loadTextures()
{
    getCurrentState().getTexMgr().addResource(
            new Texture("Tux", "res/textures/tux.png"));
}

void Game::handleEvents()
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            LOG_INFO << "Received quit event" << endl;
            _currentState->_running = false;
        }
        else if (event.type == SDL_KEYDOWN)
        {
            switch (event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                LOG_INFO << "Received quit event (escape was pressed)" << endl;
                getCurrentState().setRunning(false);
                break;

            case SDLK_F1:
                getCurrentState()._showFrameRate = !getCurrentState()._showFrameRate;
                LOG_INFO << "FPS display "
                         << (getCurrentState()._showFrameRate ? "enabled" : "disabled")
                         << endl;
                break;

            case SDLK_F2:
                getCurrentState()._trackMouse = !getCurrentState()._trackMouse;
                LOG_INFO << "Mouse tracking "
                         << (getCurrentState()._trackMouse ? "enabled" : "disabled")
                         << endl;
                break;

            default: break;
            }
        }
        else if (event.type == SDL_MOUSEMOTION && getCurrentState()._trackMouse)
        {
            cout << "X = " << event.motion.x
                 << " , Y = " << event.motion.y
                 << " (Xmeters = " << p2m(event.motion.x)
                 << ", Ymeters = " << p2m(getCurrentState().getSettings().windowHeight - event.motion.y)
                 << ")" << endl;
        }
    }
}

Game &getGame()
{
    return *globalGame;
}

int main(int argc, char *argv[])
{
    try
    {
        Game game(argc, argv);
        globalGame = &game;
        game.run();
    }
    catch (SDLException &e)
    {
        LOG_ERROR << "caught SDL exception: " << e.getMsg() << endl;
    }
    catch (GLException &e)
    {
        LOG_ERROR << "caught OpenGL exception: " << e.getMsg() << endl;
    }
    catch (GLEWException &e)
    {
        LOG_ERROR << "caught GLEW exception: " << e.getMsg() << endl;
    }
    catch (Exception &e)
    {
        LOG_ERROR << "caught exception: " << e.getMsg() << endl;
    }
    catch (TCLAP::ArgException &e)
    {
        LOG_ERROR << "caught TCLAP exception: " << e.what() << endl;
    }
    catch (...)
    {
        LOG_ERROR << "unknown error" << endl;
    }

    return 0;
}
