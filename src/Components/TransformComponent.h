#ifndef _Transform_Component_h_
#define _Transform_Component_h_

#include <SDL2/SDL.h>
#include "../Game.h"
#include "../EntityManager.h"
#include "../../lib/glm/glm.hpp"

class TransformComponent : public Component
{
public:
    glm::vec2 position;
    glm::vec2 velocity;
    int width;
    int height;
    int scale;

    TransformComponent(int posX, int posY, int velX, int velY, int w, int h, int s)
    {
        position = glm::vec2(posX, posY);
        velocity = glm::vec2(velX, velY);
        width = w;
        height = h;
        scale = s;
    }

    void initialize() override {}

    void update(float deltaTime) override
    {
        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
    }

    void render() override
    {
    }

    void print() override
    {
        std::cout << "\tComponent<TransformComponent>" << std::endl;
    }
};

#endif