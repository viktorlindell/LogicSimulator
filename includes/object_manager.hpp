#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <SFML/Graphics.hpp>

#include "collision_control.hpp"
#include "object.hpp"
#include "component.hpp"
#include "component_types.hpp"
#include "connector.hpp"

class ObjectManager
{
public:
    ObjectManager() = default; 
    ObjectManager(const ObjectManager&) = delete;
    ObjectManager& operator=(const ObjectManager&) = delete;

    void update();
    void render( sf::RenderWindow *renderWindow );

    bool createGameObject( sf::Vector2i position, uint32_t type );
    void deleteGameObject();

    inline std::vector<Component*> const& getGameObjects() const { return _gameObjects; };

    inline Object* const& getSelectedGameObject() const { return _selectedObject; };
    inline void setSelectedGameObject( Object *object ) { _selectedObject = object; };

private:
    std::vector<Component*> _gameObjects{};
    Object* _selectedObject{ nullptr };

};

#endif