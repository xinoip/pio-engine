#ifndef _Sprite_Component_h_
#define _Sprite_Component_h_

#include <SDL2/SDL.h>
#include <string>
#include <map>
#include "../Animation.h"
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
    bool isAnimated;
    unsigned int numFrames;
    int animationSpeed;
    bool isFixed;
    std::map<std::string, Animation> animations;
    std::string currentAnimationName;
    unsigned int animationIndex = 0;

public:
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;

    SpriteComponent(const char *filePath, unsigned int numFrames, int animationSpeed, bool hasDirections, bool isFixed)
    {
        this->isAnimated = true;
        this->numFrames = numFrames;
        this->animationSpeed = animationSpeed;
        this->isFixed = isFixed;

        if (hasDirections)
        {
            Animation downAnimation = Animation(0, numFrames, animationSpeed);
            Animation rightAnimation = Animation(1, numFrames, animationSpeed);
            Animation leftAnimation = Animation(2, numFrames, animationSpeed);
            Animation upAnimation = Animation(3, numFrames, animationSpeed);
            animations.emplace("DownAnimation", downAnimation);
            animations.emplace("RightAnimation", rightAnimation);
            animations.emplace("LeftAnimation", leftAnimation);
            animations.emplace("UpAnimation", upAnimation);

            this->animationIndex = 0;
            this->currentAnimationName = "DownAnimation";
        }
        else
        {
            Animation singleAnimation = Animation(0, numFrames, animationSpeed);
            animations.emplace("SingleAnimation", singleAnimation);
            this->animationIndex = 0;
            this->currentAnimationName = "SingleAnimation";
        }

        play(this->currentAnimationName);
        setTexture(filePath);
    }

    void play(std::string animationName)
    {
        numFrames = animations[animationName].numFrames;
        animationIndex = animations[animationName].index;
        animationSpeed = animations[animationName].animationSpeed;
        currentAnimationName = animationName;
    }

    SpriteComponent(const char *filePath)
    {
        isAnimated = false;
        isFixed = false;
        setTexture(filePath);
    }

    void setTexture(std::string assetTextureId)
    {
        texture = Game::assetManager->getTexture(assetTextureId);
        if (texture == nullptr)
        {
            std::cout << "SpriteComponent does not have texture!\n";
        }
    }

    void initialize() override
    {
        transform = owner->getComponent<TransformComponent>();
        if (transform == nullptr)
        {
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
        if (isAnimated)
        {
            srcRectangle.x = srcRectangle.w * static_cast<int>((SDL_GetTicks() / animationSpeed) % numFrames);
        }
        srcRectangle.y = animationIndex * transform->height;

        if (isFixed)
        {
            destRectangle.x = static_cast<int>(transform->position.x);
            destRectangle.y = static_cast<int>(transform->position.y);
        }
        else
        {
            destRectangle.x = static_cast<int>(transform->position.x) - Game::camera.x;
            destRectangle.y = static_cast<int>(transform->position.y) - Game::camera.y;
        }
        destRectangle.w = transform->width * transform->scale;
        destRectangle.h = transform->height * transform->scale;
    }

    void render() override
    {
        TextureManager::draw(texture, srcRectangle, destRectangle, spriteFlip);
    }

    void print() override
    {
        std::cout << "\tComponent<SpriteComponent>" << std::endl;
    }
};

#endif