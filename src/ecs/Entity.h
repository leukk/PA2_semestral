#pragma once
#include "cstdlib"
#include "EntityManager.h"

/**
 *  Entity "reference" class
 *  Each entity holds an index representing itself & bitmask of active components
 */
class Entity{
public:
    Entity();
    virtual ~Entity();

    template<typename TComponent>
    TComponent& addComponent(TComponent tComponent);

    template<typename TComponent>
    TComponent& getComponent(TComponent tComponent);

    int64_t entityId;
    int64_t componentMask;
    static EntityManager* entityManager;
};