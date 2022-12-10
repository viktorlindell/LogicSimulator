#ifndef COORDINATOR_H
#define COORDINATOR_H

#include <memory>

#include "types.hpp"
#include "entity_manager.hpp"

class Coordinator
{
public:
    void init()
    {
        _entityManager = std::make_unique<EntityManager>();
    }

    Entity createEntity() { return _entityManager->createEntity(); }
    Entity destroyEntity( Entity entity ) { _entityManager->destroyEntity(entity); }

private:
    std::unique_ptr<EntityManager> _entityManager;

};

#endif