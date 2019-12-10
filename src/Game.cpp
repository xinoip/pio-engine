#include <iostream>

#include "Game.h"
#include "Constants.h"
#include "../lib/glm/glm.hpp"
#include "Components/TransformComponent.h"
#include "Components/SpriteComponent.h"
#include "Components/KeyboardControlComponent.h"
#include "Components/ColliderComponent.h"
#include "Components/TextLabelComponent.h"
#include "Components/ProjectileEmitterComponent.h"
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

    if (TTF_Init() != 0)
    {
        std::cerr << "TTF_init error." << std::endl;
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

    loadLevel(1);

    m_isRunning = true;
    return;
}

Entity &chopperEntity(manager.addEntity("chopper", PLAYER_LAYER));

void Game::loadLevel(int levelNumber)
{
    //**********//
    // Init Lua //
    //**********//
    sol::state lua;
    lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);

    //*****************//
    // Lua level names //
    //*****************//
    std::string levelName = "Level" + std::to_string(levelNumber);
    std::cout << "Loading level from: " << levelName << std::endl;
    lua.script_file("./assets/scripts/" + levelName + ".lua");

    //*****************//
    // Lua table names //
    //*****************//
    sol::table levelData = lua[levelName];
    sol::table levelAssets = levelData["assets"];
    sol::table levelMap = levelData["map"];

    //**********************//
    // Load Assets from lua //
    //**********************//
    unsigned int assetIndex = 0;
    while (true)
    {
        sol::optional<sol::table> existsAssetIndexMode = levelAssets[assetIndex];
        if (existsAssetIndexMode == sol::nullopt)
        {
            break;
        }
        else
        {
            sol::table asset = levelAssets[assetIndex];
            std::string assetType = asset["type"];
            if (assetType == "texture")
            {
                std::string assetId = asset["id"];
                std::string assetFile = asset["file"];
                assetManager->addTexture(assetId, assetFile.c_str());
            }
        }
        assetIndex++;
    }

    //********************//
    // Load Maps from lua //
    //********************//
    std::string mapTextureId = levelMap["textureAssetId"];
    std::string mapFile = levelMap["file"];
    int mapScale = static_cast<int>(levelMap["scale"]);
    int mapTileSize = static_cast<int>(levelMap["tileSize"]);
    int mapSizeX = static_cast<int>(levelMap["mapSizeX"]);
    int mapSizeY = static_cast<int>(levelMap["mapSizeY"]);

    map = new Map(mapTextureId, mapScale, mapTileSize);
    map->LoadMap(mapFile, mapSizeX, mapSizeY);

    // // load assetsmanager
    // std::string imageFilePath = "./assets/images/";
    // std::string tileFilePath = "./assets/tilemaps/";
    // std::string fontFilePath = "./assets/fonts/";
    // assetManager->addTexture("tank-image", (imageFilePath + "tank-big-right.png").c_str());
    // assetManager->addTexture("chopper-image", (imageFilePath + "chopper-spritesheet.png").c_str());
    // assetManager->addTexture("radar-image", (imageFilePath + "radar.png").c_str());
    // assetManager->addTexture("hitbox-image", (imageFilePath + "collision-texture.png").c_str());
    // assetManager->addTexture("heliport-image", (imageFilePath + "heliport.png").c_str());
    // assetManager->addTexture("army-image", (imageFilePath + "army-group-1.png").c_str());
    // assetManager->addTexture("projectile-image", (imageFilePath + "bullet-enemy.png").c_str());
    // assetManager->addTexture("jungle-map", (tileFilePath + "jungle.png").c_str());
    // assetManager->addFont("charriot-font", (fontFilePath + "charriot.ttf").c_str(), 14);

    // map = new Map("jungle-map", 2, 32);
    // map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

    // // add entities and components
    chopperEntity.addComponent<TransformComponent>(400, 300, 0, -10, 32, 32, 1);
    chopperEntity.addComponent<SpriteComponent>("chopper-texture", 2, 90, true, false);
    chopperEntity.addComponent<KeyboardControlComponent>("up", "right", "down", "left");
    chopperEntity.addComponent<ColliderComponent>("PLAYER", 400, 300, 32, 32);

    // Entity &projectile(manager.addEntity("projectile", PROJECTILE_LAYER));
    // projectile.addComponent<TransformComponent>(350 + 16, 200 + 16, 0, 0, 4, 4, 1);
    // projectile.addComponent<SpriteComponent>("projectile-image");
    // projectile.addComponent<ColliderComponent>("PROJECTILE", 350 + 16, 200 + 16, 4, 4);
    // projectile.addComponent<ProjectileEmitterComponent>(50, 270, 200, true);

    // Entity &tankEntity(manager.addEntity("tank", ENEMY_LAYER));
    // tankEntity.addComponent<TransformComponent>(350, 200, 10, 10, 32, 32, 1);
    // tankEntity.addComponent<SpriteComponent>("tank-image");
    // tankEntity.addComponent<ColliderComponent>("ENEMY", 350, 200, 32, 32);

    // Entity &heliportEntity(manager.addEntity("heliport", ENEMY_LAYER));
    // heliportEntity.addComponent<TransformComponent>(470, 420, 0, 0, 32, 32, 1);
    // heliportEntity.addComponent<SpriteComponent>("heliport-image");
    // heliportEntity.addComponent<ColliderComponent>("LEVEL_COMPLETE", 470, 420, 32, 32);

    // Entity &radarEntity(manager.addEntity("radar", UI_LAYER));
    // radarEntity.addComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
    // radarEntity.addComponent<SpriteComponent>("radar-image", 8, 160, false, true);

    // Entity &armyEntity(manager.addEntity("army", ENEMY_LAYER));
    // armyEntity.addComponent<TransformComponent>(300, 200, 10, 10, 32, 32, 1);
    // armyEntity.addComponent<SpriteComponent>("army-image");
    // armyEntity.addComponent<ColliderComponent>("ENEMY", 300, 200, 32, 32);

    // Entity &labelLevelName(manager.addEntity("LabelLevelName", UI_LAYER));
    // labelLevelName.addComponent<TextLabelComponent>(10, 10, "First level...", "charriot-font", WHITE_COLOR);

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

    checkCollisions();
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
    TransformComponent *playerTransform = chopperEntity.getComponent<TransformComponent>();
    camera.x = playerTransform->position.x - (WINDOW_WIDTH / 2);
    camera.y = playerTransform->position.y - (WINDOW_HEIGHT / 2);

    // clamp
    if (camera.x < 0)
        camera.x = 0;
    if (camera.y < 0)
        camera.y = 0;
    if (camera.x > camera.w)
        camera.x = camera.w;
    if (camera.y > camera.h)
        camera.y = camera.h;
}

void Game::processGameOver()
{
    m_isRunning = false;
}

void Game::processNextLevel()
{
    std::cout << "next level!" << std::endl;
    m_isRunning = false;
}

void Game::checkCollisions()
{
    CollisionType collisionTagType = manager.checkCollisions();
    switch (collisionTagType)
    {
    case PLAYER_ENEMY_COLLISION:
        processGameOver();
        break;
    case PLAYER_LEVEL_COMPLETE_COLLISION:
        processNextLevel();
        break;
    case PLAYER_PROJECTILE_COLLISION:
        processGameOver();
        break;

    default:
        break;
    }
}