#ifndef _Entity_Manager_h_
#define _Entity_Manager_h_

#include <string>
#include <vector>
#include "Entity.h"
#include "Component.h"

class Entity;

class EntityManager
{
private:
    std::vector<Entity*> entities;
public:
    void update(float deltaTime);
    void render();
    void destroy();
    bool hasNoEntities() const;
    Entity& addEntity(std::string entityName, LayerType layer);
    std::vector<Entity*> getEntities() const;
    std::vector<Entity*> getEntitiesByLayer(LayerType layer) const;
    unsigned int getEntityCount();
    void clearData();

    void printEntities();
};

#endif