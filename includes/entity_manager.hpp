#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include <queue>
#include <cassert>
#include <array>

#include "types.hpp"

class EntityManager
{
public:
    EntityManager()
    {
        for( Entity entity = 0; entity < MAX_ENTITIES; ++entity)
            _availableEntities.push(entity);
    }

    Entity createEntity()
    {
        assert( _livingEntityCount < MAX_ENTITIES && "Too many entities in existence." );

        Entity id = _availableEntities.front();
        _availableEntities.pop();
        ++_livingEntityCount;

        return id;
    }

    void destroyEntity( Entity entity )
    {
        assert( entity < MAX_ENTITIES && "Invalid entity id." );

        _availableEntities.push( entity );
        --_livingEntityCount;
    }

    void setSignature( Entity entity, Signature signature )
    {
        assert( entity < MAX_ENTITIES && "Invalid entity id." );

        _signatures[entity] = signature;
    }

    Signature getSignature( Entity entity )
    {
        assert( entity < MAX_ENTITIES && "Invalid entity id." );

        return _signatures[entity];
    }

private:
    std::queue<Entity> _availableEntities{};
    std::array<Signature, MAX_ENTITIES> _signatures{};
    uint32_t _livingEntityCount{};
};

#endif