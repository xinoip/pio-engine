#ifndef _Game_h_
#define _Game_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "EntityManager.h"

class Game
{
private:
    bool m_isRunning;
    SDL_Window *window;
    int ticksLastFrame;
public:
    static SDL_Renderer *renderer;
    Game();
    ~Game();
    bool isRunning() const;
    void initialize(unsigned int width, unsigned int height);
    void processInput();
    void update();
    void render();
    void destroy();
    void loadLevel(int levelNumber);
};

#endif