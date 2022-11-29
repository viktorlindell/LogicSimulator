#ifndef COLLISIONCONTROL
#define COLLISIONCONTROL

#include <SFML/Graphics.hpp>

static bool checkCollisionPoint( sf::RectangleShape const& rect1, sf::Vector2i const& objPos )
{
    if (    rect1.getPosition().x  - rect1.getSize().x / 2  < objPos.x &&
            rect1.getPosition().x  + rect1.getSize().x / 2  > objPos.x &&
            rect1.getPosition().y  - rect1.getSize().y / 2  < objPos.y &&
            rect1.getPosition().y  + rect1.getSize().y / 2  > objPos.y )
        return true;

    return false;
}

static bool checkCollisionRectangle( sf::RectangleShape const& rect1, sf::RectangleShape const& rect2 )
{
    if (    rect1.getPosition().x - rect1.getSize().x / 2 <
                rect2.getPosition().x - rect2.getSize().x / 2 + rect2.getSize().x &&

            rect1.getPosition().x - rect1.getSize().x / 2 + rect1.getSize().x > 
                rect2.getPosition().x - rect2.getSize().x / 2 &&

            rect1.getPosition().y - rect1.getSize().x / 2 < 
                rect2.getPosition().y - rect2.getSize().x / 2 + rect2.getSize().y &&

            rect1.getSize().y + rect1.getPosition().y - rect1.getSize().x / 2 >
                rect2.getPosition().y - rect2.getSize().x / 2
            )
        return true;

    return false;
}

#endif