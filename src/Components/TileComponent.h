#ifndef _Tile_Component_h_
#define _Tile_Component_h_

#include <SDL2/SDL.h>
#include <iostream>
#include "../../lib/glm/glm.hpp"
#include "../TextureManager.h"
#include "../EntityManager.h"
#include "../Component.h"

class TileComponent : public Component
{
public:
    SDL_Texture *texture;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    glm::vec2 position;

    TileComponent(int srcRectX, int srcRectY, int x, int y, int tileSize, int tileScale, std::string textureId)
    {
        texture = Game::assetManager->getTexture(textureId);

        srcRect.x = srcRectX;
        srcRect.y = srcRectY;
        srcRect.w = tileSize;
        srcRect.h = tileSize;

        destRect.x = x;
        destRect.y = y;
        destRect.w = tileSize * tileScale;
        destRect.h = tileSize * tileScale;

        position.x = x;
        position.y = y;
    }

    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }

    void update(float deltaTime) override
    {
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
    }

    void render() override
    {
        TextureManager::draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }

    void print() override
    {
        // std::cout << "\tComponent<TileComponent>" << std::endl;
    }
};

#endif