#ifndef _Sprite_Component_h_
#define _Sprite_Component_h_

#include <SDL2/SDL.h>
#include <string>
#include "../Component.h"
#include "../TextureManager.h"
#include "../AssetManager.h"

class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRectangle;
    SDL_Rect destRectangle;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    SpriteComponent(const char *filePath)
    {
        setTexture(filePath);
    }

    void setTexture(std::string assetTextureId)
    {
        texture = Game::assetManager->getTexture(assetTextureId);
        if(texture == nullptr) {
            std::cout << "SpriteComponent does not have texture!\n";
        }
    }

    void initialize() override
    {
        transform = owner->getComponent<TransformComponent>();
        if(transform == nullptr) {
            std::cout << "SpriteComponent does not have TranformComponent!\n";
            exit(EXIT_FAILURE);
        }
        srcRectangle.x = 0;
        srcRectangle.y = 0;
        srcRectangle.w = transform->width;
        srcRectangle.h = transform->height;
    }

    void update(float deltaTime) override
    {
        destRectangle.x = (int) transform->position.x;
        destRectangle.y = (int) transform->position.y;
        destRectangle.w = (int) transform->width * transform->scale;
        destRectangle.h = (int) transform->height * transform->scale;
    }

    void render() override
    {
        TextureManager::draw(texture, srcRectangle, destRectangle, spriteFlip);
    }
};

#endif