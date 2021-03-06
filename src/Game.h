#ifndef _Game_h_
#define _Game_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "../lib/lua/sol.hpp"
#include "EntityManager.h"
#include "AssetManager.h"

class AssetManager;

class Game
{
private:
    bool m_isRunning;
    SDL_Window *window;
    int ticksLastFrame;
public:
    static SDL_Renderer *renderer;
    static AssetManager *assetManager;
    static SDL_Event event;
    static SDL_Rect camera;
    Game();
    ~Game();
    bool isRunning() const;
    void initialize(unsigned int width, unsigned int height);
    void processInput();
    void update();
    void render();
    void destroy();
    void loadLevel(int levelNumber);
    void handleCameraMovement();
    void checkCollisions();
    void processGameOver();
    void processNextLevel();
};

#endif