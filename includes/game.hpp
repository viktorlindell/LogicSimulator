#ifndef GAME_H
#define GAME_H

#include "../includes/component_types.hpp"
#include "../includes/component.hpp"
#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

// Enum that specifies what mode the user currently resides in.
enum InteractionMode
{
    MOVE,
    CREATE,
    MAX_MODES
};

// Enum that specifies what component the user will place.
enum ComponentType
{
    LIGHT, 
    AND,
    OR,
    GROUND,
    POSITIVE,
    MAX_COMPONENTS
};

class Game
{
public:
    Game(sf::RenderWindow *window);
    Game(const Game&) = delete;
    Game* operator=(const Game&) = delete;
    void run();

private:
    // Event handling
    void processEvents();
    void keyboardEvent( sf::Event const& event );
    void leftMouseEvent();

    // Helper functions
    void modifyConnection( Component *component );
    bool createComponent( );
    sf::RectangleShape createLine();
    void setText();

public:


private:
    sf::RenderWindow *_renderWindow;
    std::vector<Component*> _components;
    Object* _selectedObject { nullptr };

    int _componentType{ 0 };

    sf::Text _text{};
    sf::Font _font{};

    sf::RectangleShape _textBox{ };
};

#endif
