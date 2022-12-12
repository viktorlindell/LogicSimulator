#ifndef GAME_H
#define GAME_H

#include "../includes/component.hpp"
#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class Game
{
public:
    Game(sf::RenderWindow *window);
    void run();

private:
    void eventHandler();
    sf::RectangleShape createLine();

public:


private:
    sf::RenderWindow *_renderWindow;
    std::vector<Component*> _components;
    Object* _selectedObject { nullptr };
};

#endif
