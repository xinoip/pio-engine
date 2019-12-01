#ifndef _Keyboard_Control_Component_h_
#define _Keyboard_Control_Component_h_

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"

class KeyboardControlComponent : public Component
{
public:
    std::string upKey;
    std::string downKey;
    std::string rightKey;
    std::string leftKey;
    std::string shootKey;
    TransformComponent *transform;
    SpriteComponent *sprite;

    KeyboardControlComponent() {}

    KeyboardControlComponent(std::string upKey, std::string rightKey, std::string downKey, std::string leftKey)
    {
        this->upKey = getSDLKeyStringCode(upKey);
        this->rightKey = getSDLKeyStringCode(rightKey);
        this->downKey = getSDLKeyStringCode(downKey);
        this->leftKey = getSDLKeyStringCode(leftKey);
        this->shootKey = getSDLKeyStringCode(shootKey);
    }

    std::string getSDLKeyStringCode(std::string key)
    {
        if (key.compare("up") == 0)
            return "1073741906";
        if (key.compare("down") == 0)
            return "1073741905";
        if (key.compare("left") == 0)
            return "1073741904";
        if (key.compare("right") == 0)
            return "1073741903";
        if (key.compare("space") == 0)
            return "32";
        return std::to_string(static_cast<int>(key[0]));
    }

    void initialize() override
    {
        transform = owner->getComponent<TransformComponent>();
        sprite = owner->getComponent<SpriteComponent>();
    }

    void update(float deltaTime) override
    {
        if (Game::event.type == SDL_KEYDOWN)
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);

            if (keyCode.compare(upKey) == 0)
            {
                transform->velocity.x = 0;
                transform->velocity.y = -10;
                sprite->play("UpAnimation");
            }
            if (keyCode.compare(rightKey) == 0)
            {
                transform->velocity.x = 10;
                transform->velocity.y = 0;
                sprite->play("RightAnimation");
            }
            if (keyCode.compare(downKey) == 0)
            {
                transform->velocity.x = 0;
                transform->velocity.y = 10;
                sprite->play("DownAnimation");
            }
            if (keyCode.compare(leftKey) == 0)
            {
                transform->velocity.x = -10;
                transform->velocity.y = 0;
                sprite->play("LeftAnimation");
            }
            if (keyCode.compare(shootKey) == 0)
            {
                
            }
        }

        if (Game::event.type == SDL_KEYUP)
        {
            std::string keyCode = std::to_string(Game::event.key.keysym.sym);

            if (keyCode.compare(upKey) == 0)
            {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(rightKey) == 0)
            {
                transform->velocity.x = 0;
            }
            if (keyCode.compare(downKey) == 0)
            {
                transform->velocity.y = 0;
            }
            if (keyCode.compare(leftKey) == 0)
            {
                transform->velocity.x = 0;
            }
            if (keyCode.compare(shootKey) == 0)
            {
            }
        }
    }
};

#endif
