#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

class Connector : public Object
{
public:
    Connector(  sf::Vector2i const& pos, sf::Vector2i const& parentPos, 
                sf::Color const& color = sf::Color(   10, 180, 10   ) );

    void update( sf::RenderWindow *renderWindow ) override {};
    void render( sf::RenderWindow *renderWindow ) override;

    inline void setPosition ( sf::Vector2i const& newPos ) { _shape.setPosition( _offset.x + newPos.x,
                                                                                _offset.y + newPos.y ); };
    inline sf::Vector2f const& getPosition () const { return _shape.getPosition(); };

private:
    sf::Vector2i _offset;
};

#endif