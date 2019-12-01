#include <iostream>

#include "Game.h"
#include "Constants.h"
#include "../lib/glm/glm.hpp"

Game::Game()
{
    m_isRunning = false;
}

Game::~Game()
{
}

bool Game::isRunning() const
{
    return m_isRunning;
}

glm::vec2 projectilePos = glm::vec2(0.0f, 0.0f);
glm::vec2 projectileVel = glm::vec2(20.0f, 20.0f);

void Game::initialize(unsigned int width, unsigned int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "SDL_init error." << std::endl;
        return;
    }

    window = SDL_CreateWindow(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        std::cerr << "SDL_CreateWindow error." << std::endl;
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer)
    {
        std::cerr << "SDL_CreateRenderer error." << std::endl;
        return;
    }

    m_isRunning = true;
    return;
}

void Game::processInput()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        m_isRunning = false;
        break;
    case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_ESCAPE)
        {
            m_isRunning = false;
        }
        break;

    default:
        break;
    }
}

void Game::update()
{

    while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksLastFrame + FRAME_TARGET_TIME))
        ;

    float deltaTime = (SDL_GetTicks() - ticksLastFrame) / 1000.0f;

    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;

    ticksLastFrame = SDL_GetTicks();

    projectilePos = glm::vec2(
        projectilePos.x + projectileVel.x * deltaTime,
        projectilePos.y + projectileVel.y * deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    SDL_Rect projectile{
        (int)projectilePos.x,
        (int)projectilePos.y,
        10,
        10};

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderFillRect(renderer, &projectile);

    SDL_RenderPresent(renderer);
}

void Game::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}