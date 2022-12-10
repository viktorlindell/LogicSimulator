#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include <any>
#include <memory>
#include <unordered_map>

#include "component_array.hpp"
#include "types.hpp"

class ComponentManager
{
public:
    template <typename T>
    void registerComponent()
    {
        const char* typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) == mComponentTypes.end() 
                && "Registering component type more than once.");

        _componentTypes.insert( { typeName, _nextComponentType } );
        _componentArrays.insert( { typeName, std::make_shared<ComponentArray<T>>() } );

        ++_nextComponentType;
    }
    
    template<typename T>
	ComponentType getComponentType()
	{
		const char* typeName = typeid(T).name();

		assert(_componentTypes.find(typeName) != _componentTypes.end() 
                && "Component not registered before use.");

		return _componentTypes[typeName];
	}

	template<typename T>
	void addComponent(Entity entity, T component)
	{
		getComponentArray<T>()->insertData(entity, component);
	}

	template<typename T>
	void RemoveComponent(Entity entity)
	{
		getComponentArray<T>()->RemoveData(entity);
	}

	template<typename T>
	T& getComponent(Entity entity)
	{
		return getComponentArray<T>()->GetData(entity);
	}

	void entityDestroyed(Entity entity)
	{
		for (auto const& pair : _componentArrays)
		{
			auto const& component = pair.second;

			component->entityDestroyed(entity);
		}
	}

private:
    std::unordered_map<const char*, ComponentType> _componentTypes{};
    std::unordered_map<const char*, std::shared_ptr<IComponetArray>> _componentArrays{};
    ComponentType _nextComponentType{};

    template <typename T>
    std::shared_ptr<ComponentArray<T>> getComponentArray()
    {
        const char* typeName = typeid(T).name();

        assert(mComponentTypes.find(typeName) != mComponentTypes.end() 
                && "Component not registered before use.");

        return std::static_pointer_cast<ComponentArray<T>>( _componentArrays[typeName] );
    }
};

#endif