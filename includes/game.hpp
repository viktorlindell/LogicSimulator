#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>

#include <vector>

#include "object_manager.hpp"
#include "event_manager.hpp"

/* namespace COLORS
{
    uint32_t _grey = 0x404040FF;
    uint32_t _green = 0x5DB53FFF;
    uint32_t _red = 0xBD2121FF;
}; */

class Game
{
public:
    Game(sf::RenderWindow *window);
    Game(const Game&) = delete;
    Game* operator=(const Game&) = delete;
    void run();

private:

public:


private:
    sf::RenderWindow *_renderWindow;

    EventManager _eventManager;
    ObjectManager _objectManager;

/*     sf::Text _text{};
    sf::Font _font{};

    sf::RectangleShape _textBox{ }; */
};

#endif
