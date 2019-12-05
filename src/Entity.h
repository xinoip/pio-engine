#ifndef _Entity_h_
#define _Entity_h_

#include "Constants.h"
#include <vector>
#include <string>
#include <map>
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
    std::map<const std::type_info *, Component *> componentTypeMap;

public:
    std::string name;
    LayerType layer;
    Entity(EntityManager &manager);
    Entity(EntityManager &manager, std::string name, LayerType layer);
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
        componentTypeMap[&typeid(*newComponent)] = newComponent;
        newComponent->initialize();
        return *newComponent;
    }

    template <typename T>
    T *getComponent()
    {
        return static_cast<T *>(componentTypeMap[&typeid(T)]);
    }

    template <typename T>
    bool hasComponent()
    {
        if (componentTypeMap[&typeid(T)] != nullptr)
        {
            return true;
        }
        return false;
    }

    void printComponents();
};

#endif