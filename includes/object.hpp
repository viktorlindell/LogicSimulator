#ifndef OBJECT_H
#define OBJECT_H

#include <SFML/Graphics.hpp>

#include <iostream>

class Object
{
protected:
    Object(sf::Vector2f const& size, sf::Color const& color) 
        : _shape{ sf::Vector2f{ size } }, _color{ color }
    {};

    virtual ~Object() {};

public:
    virtual void update( sf::RenderWindow *renderWindow = nullptr ) = 0;
    virtual void render( sf::RenderWindow *renderWindow ) = 0;

    inline void setColor( sf::Color color ) { _shape.setFillColor( color ); };
    inline sf::RectangleShape const& getShape() const { return _shape; };
    inline bool getValue() const { return _value; };
    
protected:
    sf::RectangleShape _shape;
    sf::Color _color;

    bool _value{ false };
};

#endif