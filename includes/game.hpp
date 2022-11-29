#ifndef GAME_H
#define GAME_H

#include "../includes/component.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

class Game
{
public:
    Game(sf::RenderWindow *window);
    void run();

private:
    bool checkCollision(sf::RectangleShape const& shape);

public:


private:
    sf::RenderWindow *_renderWindow;
    std::vector<Component> _components;
};

#endif
