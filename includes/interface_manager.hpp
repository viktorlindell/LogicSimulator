#ifndef INTERFACE_H
#define INTERFACE_H

#include "SFML/Graphics.hpp"

#include "component.hpp"
#include "event_manager.hpp"

class InterfaceManager
{
public:
    void Init( EventManager *eventManager );
    
    void update();
    void render( sf::RenderWindow *renderWindow );

private:
    EventManager *_eventManager{ nullptr };

    sf::Text _text{};
    sf::Font _font{};
    sf::RectangleShape _textBox{ };
};

#endif