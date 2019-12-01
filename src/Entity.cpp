#include "Entity.h"

Entity::Entity(EntityManager &manager) : manager(manager)
{
    m_isActive = true;
}

Entity::Entity(EntityManager &manager, std::string name) : manager(manager), name(name)
{
    m_isActive = true;
}

void Entity::update(float deltaTime)
{
    for (auto &component : components)
    {
        component->update(deltaTime);
    }
}

void Entity::render()
{
    for (auto &component : components)
    {
        component->render();
    }
}

void Entity::destroy()
{
    m_isActive = false;
}

bool Entity::isActive() const
{
    return m_isActive;
}

void Entity::printComponents()
{
    for (auto &component : components)
    {
        component->print();
    }
}