#ifndef COLLISIONCONTROL
#define COLLISIONCONTROL

#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

namespace CollisionHandler
{
    static bool checkCollisionPoint( sf::RectangleShape const& rect1, sf::Vector2i const& objPos )
    {
        if( rect1.getPosition().x  - rect1.getSize().x / 2  < objPos.x &&
            rect1.getPosition().x  + rect1.getSize().x / 2  > objPos.x &&
            rect1.getPosition().y  - rect1.getSize().y / 2  < objPos.y &&
            rect1.getPosition().y  + rect1.getSize().y / 2  > objPos.y 
            )
            return true;

        return false;
    }

    template <typename T>
    static T* checkCollisionPoint( std::vector<T*> const& container, sf::Vector2i const& objPos )
    {
        for(T *obj : container)
        {
            sf::RectangleShape rect{ obj->getShape() };
            if( rect.getPosition().x  - rect.getSize().x / 2  < objPos.x &&
                rect.getPosition().x  + rect.getSize().x / 2  > objPos.x &&
                rect.getPosition().y  - rect.getSize().y / 2  < objPos.y &&
                rect.getPosition().y  + rect.getSize().y / 2  > objPos.y 
                )
                return obj;
        }

        return nullptr;
    }

    static bool checkCollisionRectangle( sf::RectangleShape const& rect1, sf::RectangleShape const& rect2 )
    {
        if( rect1.getPosition().x - rect1.getSize().x / 2 < rect2.getPosition().x - rect2.getSize().x / 2 + rect2.getSize().x &&
            rect1.getPosition().x - rect1.getSize().x / 2 + rect1.getSize().x > rect2.getPosition().x - rect2.getSize().x / 2 &&
            rect1.getPosition().y - rect1.getSize().x / 2 < rect2.getPosition().y - rect2.getSize().x / 2 + rect2.getSize().y &&
            rect1.getSize().y + rect1.getPosition().y - rect1.getSize().x / 2 > rect2.getPosition().y - rect2.getSize().x / 2
            )
            return true;

        return false;
    }

    template <typename T>
    static T* checkCollisionRectangle( std::vector<T*> const& container, T *obj2 )
    {
        sf::RectangleShape rect2{ obj2->getShape() };
        for(T *obj1 : container)
        {
            sf::RectangleShape rect1{ obj1->getShape() };
            if( obj1 != obj2 )
                if( rect1.getPosition().x - rect1.getSize().x / 2 < rect2.getPosition().x - rect2.getSize().x / 2 + rect2.getSize().x &&
                    rect1.getPosition().x - rect1.getSize().x / 2 + rect1.getSize().x > rect2.getPosition().x - rect2.getSize().x / 2 &&
                    rect1.getPosition().y - rect1.getSize().x / 2 < rect2.getPosition().y - rect2.getSize().x / 2 + rect2.getSize().y &&
                    rect1.getSize().y + rect1.getPosition().y - rect1.getSize().x / 2 > rect2.getPosition().y - rect2.getSize().x / 2
                    )
                    return obj1;
        }

        return nullptr;
    }
}

#endif