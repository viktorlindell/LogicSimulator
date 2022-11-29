#ifndef COMPONENT_H
#define COMPONENT_H

#include "../includes/connector.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class Component
{
public:
    Component( sf::Vector2i const& pos, sf::Color const& color = sf::Color( 180, 180, 180 ) );
    void render( sf::RenderWindow *renderWindow );

    // Inline functions
    inline void setColor( sf::Color color ) { _shape.setFillColor( color ); };
    inline sf::RectangleShape const& getShape() const { return _shape; };

private:
    sf::RectangleShape _shape;
    sf::Color _color;
    std::vector<Connector> _connectors{};

};

#endif