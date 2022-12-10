#ifndef COMPONENT_ARRAY_H
#define COMPONENT_ARRAY_H

#include <array>
#include <cassert>
#include <unordered_map>

#include "types.hpp"

class IComponetArray
{
public:
    virtual ~IComponetArray() = default;
    virtual void entityDestroyed( Entity entity ) = 0;
};

template <typename T>
class ComponentArray : public IComponetArray
{
public:
    void insertData( Entity entity, T component )
    {
        assert(mEntityToIndexMap.find(entity) == mEntityToIndexMap.end() 
                && "Can only add component to the same entity once");

        size_t newIndex = _size;
        _entityToIndexMap[entity] = newIndex;
        _indexToEntityMap[newIndex] = entity;
        _componentArray[newIndex] = component;
        _size++;
    }

    void removeData( Entity entity )
    {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() 
                && "Removing non-existent component.");

        size_t indexOfRemovedEntity = _entityToIndexMap[entity];
        size_t indexOfLastElement = _size - 1;
        _componentArray[indexOfRemovedEntity] = _componentArray[indexOfLastElement];

        Entity entityOfLastElement = _indexToEntityMap[indexOfLastElement];
        _entityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
        _indexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

        _entityToIndexMap.erase( entity );
        _indexToEntityMap.erase( indexOfLastElement );

        --_size;
    }

    T& getData( Entity entity )
    {
        assert(mEntityToIndexMap.find(entity) != mEntityToIndexMap.end() 
                && "Retrieving non-existent component.");

        return _componentArray[_entityToIndexMap[entity]];
    }

    void entityDestroyed( Entity entity ) override
	{
		if( mEntityToIndexMap.find( entity ) != mEntityToIndexMap.end() )
		{
			RemoveData( entity );
		}
	}

private:
    std::array<T, MAX_ENTITIES> _componentArray{};
    std::unordered_map<Entity, size_t> _entityToIndexMap{};
    std::unordered_map<size_t, Entity> _indexToEntityMap{};
    size_t _size{};
};

#endif