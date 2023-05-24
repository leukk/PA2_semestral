#pragma once
#include "Entity.h"

/**
 * Entity management base class
 */
class EntityManager{
public:
    EntityManager();
    virtual ~EntityManager();

    Entity newEntity();

    bool destroyEntity(Entity& entity);

    Entity getEntity(int64_t entityId);

    void updateEntity(double delta);
};
