#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

#include <SFML/Graphics.hpp>

#include "collision_control.hpp"
#include "object.hpp"
#include "component.hpp"
#include "component_types.hpp"
#include "connector.hpp"
#include "map"

#include <cmath>

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

    void createConnection( Connector *connector );
    void deleteConnection( Connector *connector );

    bool isConnected( Connector *connector );

    inline std::vector<Component*> const& getGameObjects() const { return _gameObjects; };

    inline Object* const& getSelectedGameObject() const { return _selectedObject; };
    inline void setSelectedGameObject( Object *object ) { _selectedObject = object; };

private:
    sf::RectangleShape createLine( sf::Vector2i const& position );
    sf::RectangleShape createLine( sf::Vector2f const& position1, sf::Vector2f const& position2 );

private:
    std::vector<Component*> _gameObjects{};
    Object* _selectedObject{ nullptr };

    // Map the input connector to its connected output connector;
    std::map<Connector*, Connector*> _connections{};
};

#endif