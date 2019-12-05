#include <iostream>

#include "Game.h"
#include "Constants.h"
#include "../lib/glm/glm.hpp"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Map.h"

EntityManager manager;
AssetManager *Game::assetManager = new AssetManager(&manager);
SDL_Renderer *Game::renderer;
SDL_Event Game::event;
Map *map;
SDL_Rect Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

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

Entity &chopperEntity(manager.addEntity("chopper", PLAYER_LAYER));

void Game::loadLevel(int levelNumber)
{
    // load assetsmanager
    std::string imageFilePath = "./assets/images/";
    std::string tileFilePath = "./assets/tilemaps/";
    assetManager->addTexture("tank-image", (imageFilePath + "tank-big-right.png").c_str());
    assetManager->addTexture("chopper-image", (imageFilePath + "chopper-spritesheet.png").c_str());
    assetManager->addTexture("radar-image", (imageFilePath + "radar.png").c_str());
    assetManager->addTexture("jungle-map", (tileFilePath + "jungle.png").c_str());

    map = new Map("jungle-map", 2, 32);
    map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

    // add entities and components
    chopperEntity.addComponent<TransformComponent>(350, 200, 0, -10, 32, 32, 1);
    chopperEntity.addComponent<SpriteComponent>("chopper-image", 2, 90, true, false);
    chopperEntity.addComponent<KeyboardControlComponent>("up", "right", "down", "left");

    Entity &tankEntity(manager.addEntity("tank", ENEMY_LAYER));
    tankEntity.addComponent<TransformComponent>(350, 200, 10, 10, 32, 32, 1);
    tankEntity.addComponent<SpriteComponent>("tank-image");

    Entity &radarEntity(manager.addEntity("radar", UI_LAYER));
    radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    radarEntity.addComponent<SpriteComponent>("radar-image", 8, 160, false, true);

    manager.printEntities();
}

void Game::processInput()
{
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

    handleCameraMovement();
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

void Game::handleCameraMovement()
{
    TransformComponent* playerTransform = chopperEntity.getComponent<TransformComponent>();
    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

    // clamp
    if(camera.x < 0) camera.x = 0;
    if(camera.y < 0) camera.y = 0;
    if(camera.x > camera.w) camera.x = camera.w;
    if(camera.y > camera.h) camera.y = camera.h;

    std::cout << camera.x << " , " << camera.y << std::endl;
}