#ifndef __GAME_HPP__
#define __GAME_HPP__

#include <cassert>
#include <tclap/Arg.h>
#include <tclap/CmdLine.h>
#include "defines.hpp"
#include "renderer.hpp"
#include "resourcemanager.hpp"

// Various configurable settings for the game, meant to be used as a by-value
// data structure
struct GameSettings
{
    int windowWidth;
    int windowHeight;
    bool useOpenGL;
};

// Class to hold various game state variables
// TODO: modify to safeguard against tomfoolery
class GameState
{
    friend class Game;

public:
    GameState();
    ~GameState();

    inline GameSettings getSettings() const { return _settings; }
    inline Renderer &getRenderer() const { return *_renderer; }
    inline TextureManager &getTexMgr() const { return *_texMgr; }

    inline bool isRunning() const { return _running; }

protected:
    inline void setRunning(bool b) { _running = b; }
    inline void setSettings(GameSettings s) { _settings = s; }
    inline void setRenderer(Renderer *r);

private:
    GameSettings _settings;
    Renderer *_renderer;
    bool _running = false;
    //Entity *_player = NULL;
    bool _trackMouse = false;
    bool _showFrameRate = false;
    TextureManager *_texMgr;
    //GLuint _vao, _vbo;
};

class Game
{
    friend int main(int, char*[]);

public:
    Game(int argc, char *argv[]);
    ~Game();

    inline GameState &getCurrentState() const { return *_currentState; }

private:
    void run();
    void parseArgs(TCLAP::CmdLine &cmdLine);
    void loadTextures();
    void handleEvents();

    GameState *_currentState;
};

Game &getGame();

void GameState::setRenderer(Renderer *r)
{
    assert(r);
    _renderer = r;
}

#endif
