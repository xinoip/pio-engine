#ifndef _Entity_h_
#define _Entity_h_

#include <vector>
#include <string>
#include "EntityManager.h"
#include "Component.h"

class Component;
class EntityManager;

class Entity
{
private:
    EntityManager &manager;
    bool m_isActive;
    std::vector<Component *> components;

public:
    std::string name;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name);
    void update(float deltaTime);
    void render();
    void destroy();
    bool isActive() const;

    template <typename T, typename... TArgs>
    T &addComponent(TArgs &&... args)
    {
        T *newComponent(new T(std::forward<TArgs>(args)...));
        newComponent->owner = this;
        components.emplace_back(newComponent);
        newComponent->initialize();
        return *newComponent;
    }

    void printComponents();
};

#endif