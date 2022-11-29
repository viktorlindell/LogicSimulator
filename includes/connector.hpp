#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <SFML/Graphics.hpp>

class Connector
{
public:
    Connector(  sf::Vector2i const& pos, sf::Vector2i const& parentPos, 
                sf::Color const& color = sf::Color(  0, 180, 0  ) );

    void render(sf::RenderWindow *renderWindow);

    inline void setColor( sf::Color color ) { _shape.setFillColor( color ); };
    inline sf::RectangleShape const& getShape() const { return _shape; };

private:
    sf::RectangleShape _shape;
    sf::Vector2i _parentPosition;
    sf::Color _color;
};

#endif