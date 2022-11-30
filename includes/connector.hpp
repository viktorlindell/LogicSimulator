#ifndef CONNECTOR_H
#define CONNECTOR_H

#include <SFML/Graphics.hpp>

class Connector
{
public:
    Connector(  sf::Vector2i const& pos, sf::Vector2i const& parentPos, 
                sf::Color const& color = sf::Color(  0, 180, 0  ) );

    bool checkCollision( sf::RenderWindow *renderWindow );
    void render( sf::RenderWindow *renderWindow );

    inline void setColor( sf::Color color ) { _shape.setFillColor( color ); };
    inline sf::RectangleShape const& getShape() const { return _shape; };
    inline void setPosition (sf::Vector2i const& newPos ) { _shape.setPosition( _offset.x + newPos.x,
                                                                                _offset.y + newPos.y ); };

private:
    sf::RectangleShape _shape;
    sf::Vector2i _offset;
    sf::Color _color;
};

#endif