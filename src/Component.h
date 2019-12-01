#ifndef _Component_h_
#define _Component_h_

#include "Entity.h"

class Entity;

class Component
{
public:
    Entity *owner;
    virtual ~Component() {}
    virtual void initialize() {}
    virtual void update(float deltaTime) {}
    virtual void render() {}
};

#endif