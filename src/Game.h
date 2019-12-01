#ifndef _Game_h_
#define _Game_h_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

class Game
{
private:
    bool m_isRunning;
    SDL_Window *window;
    SDL_Renderer *renderer;
public:
    Game();
    ~Game();
    bool isRunning() const;
    void initialize(unsigned int width, unsigned int height);
    void processInput();
    void update();
    void render();
    void destroy();
};

#endif