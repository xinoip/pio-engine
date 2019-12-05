#include "EntityManager.h"

#include <iostream>

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
    for (int layerNumber = 0; layerNumber < NUM_LAYERS; layerNumber++)
    {
        for (auto &entity : getEntitiesByLayer(static_cast<LayerType>(layerNumber)))
        {
            entity->render();
        }
    }
}

void EntityManager::destroy()
{
}

Entity &EntityManager::addEntity(std::string entityName, LayerType layer)
{
    Entity *entity = new Entity(*this, entityName, layer);
    entities.emplace_back(entity);
    return *entity;
}

std::vector<Entity *> EntityManager::getEntities() const
{
    return entities;
}

std::vector<Entity *> EntityManager::getEntitiesByLayer(LayerType layer) const
{
    std::vector<Entity *> rtr;
    for (auto &entity : entities)
    {
        if (entity->layer == layer)
        {
            rtr.emplace_back(entity);
        }
    }
    
    return rtr;
}

unsigned int EntityManager::getEntityCount()
{
    return entities.size();
}

void EntityManager::printEntities()
{
    for (auto &entity : entities)
    {
        std::cout << "Entity name: ";
        std::cout << entity->name << std::endl;
        entity->printComponents();
        std::cout << std::endl;
    }
}