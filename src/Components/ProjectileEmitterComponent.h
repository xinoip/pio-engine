#ifndef _Projectile_Emitter_Component_h_
#define _Projectile_Emitter_Component_h_

#include "../Component.h"
#include "../../lib/glm/glm.hpp"
#include "../EntityManager.h"
#include "../Components/TransformComponent.h"

class ProjectileEmitterComponent : public Component
{
private:
    TransformComponent *transform;
    glm::vec2 origin;
    int speed;
    int range;
    float angleRad;
    bool shouldLoop;

public:
    ProjectileEmitterComponent(int speed, int angleDeg, int range, bool shouldLoop)
    {
        this->speed = speed;
        this->range = range;
        this->shouldLoop = shouldLoop;
        this->angleRad = glm::radians(static_cast<float>(angleDeg));
    }

    void initialize() override
    {
        transform = owner->getComponent<TransformComponent>();
        origin = glm::vec2(transform->position.x, transform->position.y);
        // polar coordinate conversion
        transform->velocity = glm::vec2(glm::cos(angleRad) * speed, glm::sin(angleRad) * speed);
    }

    void update(float deltaTime) override
    {
        if (glm::distance(transform->position, origin) > range)
        {
            if (shouldLoop)
            {
                transform->position.x = origin.x;
                transform->position.y = origin.y;
            }
            else
            {
                owner->destroy();
            }
        }
    }
};

#endif