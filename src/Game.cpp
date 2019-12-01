#include <iostream>

#include "Game.h"
#include "Constants.h"
#include "../lib/glm/glm.hpp"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"

EntityManager manager;
AssetManager *Game::assetManager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;

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

    loadLevel(0);

    m_isRunning = true;
    return;
}

void Game::loadLevel(int levelNumber)
{
    // load assetsmanager
    std::string textureFilePath = "./assets/images/tank-big-right.png";
    assetManager->addTexture("tank-image", textureFilePath.c_str());

    // add entities and components

    Entity &tankEntity(manager.addEntity("tank"));
    tankEntity.addComponent<TransformComponent>(350, 200, 10, 10, 32, 32, 1);
    tankEntity.addComponent<SpriteComponent>("tank-image");

    manager.printEntities();
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

    manager.update(deltaTime);
}

void Game::render()
{
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    if (manager.hasNoEntities())
    {
        return;
    }

    manager.render();

    SDL_RenderPresent(renderer);
}

void Game::destroy()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}