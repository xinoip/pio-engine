#include "EntityManager.h"

void EntityManager::clearData()
{
    for (auto &entity : entities)
    {
        entity->destroy();
    }
}

bool EntityManager::hasNoEntities() const
{
    return entities.size() == 0;
}

void EntityManager::update(float deltaTime)
{
    for (auto &entity : entities)
    {
        entity->update(deltaTime);
    }
}

void EntityManager::render()
{
    for (auto &entity : entities)
    {
        entity->render();
    }
}

void EntityManager::destroy()
{
}

Entity &EntityManager::addEntity(std::string entityName)
{
    Entity *entity = new Entity(*this, entityName);
    // entities.push_back(entity);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity *> EntityManager::getEntities() const
{
    return entities;
}

unsigned int EntityManager::getEntityCount()
{
    return entities.size();
}