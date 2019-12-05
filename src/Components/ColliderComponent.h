#ifndef _Collider_Component_h_
#define _Collider_Component_h_

#include <iostream>
#include <string>
#include "../Game.h"
#include "../Component.h"
#include "../Constants.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class ColliderComponent : public Component
{
public:
    std::string colliderTag;
    SDL_Rect collider;
    SDL_Rect srcRect;
    SDL_Rect destRect;
    TransformComponent *transform;

    ColliderComponent(std::string colliderTag, int x, int y, int width, int height)
    {
        this->colliderTag = colliderTag;
        collider = {x, y, width, height};
    }

    void initialize() override
    {
        if (owner->hasComponent<TransformComponent>())
        {
            transform = owner->getComponent<TransformComponent>();
            srcRect = {0, 0, transform->width, transform->height};
            destRect = {collider.x, collider.y, collider.w, collider.h};
            if (SHOW_HITBOX)
            {
                this->owner->addComponent<SpriteComponent>("hitbox-image");
            }
        }
        else
        {
            std::cout << "No transformComp found in collider!" << std::endl;
        }
    }

    void update(float deltaTime) override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = static_cast<int>(transform->width * transform->scale);
        collider.h = static_cast<int>(transform->height * transform->scale);
        destRect.x = collider.x - Game::camera.x;
        destRect.y = collider.y - Game::camera.y;
    }

    void print() override
    {
        std::cout << "\tComponent<ColliderComponent>" << std::endl;
    }
};

#endif
