#include "../includes/connector.hpp"
#include "../includes/collision_control.hpp"

#include "cmath"

Connector::Connector(sf::Vector2i const& pos, sf::Vector2i const& parentPos, Object *parent, ConnectorType type, sf::Color const& color )
    : Object{ sf::Vector2f{ 20.f, 20.f }, color }, _offset{ pos }, _parent{ parent }, _type{ type }
{
    _shape.setOrigin( sf::Vector2f{ _shape.getSize().x / 2, _shape.getSize().y / 2 } );
    _shape.setPosition( _offset.x + parentPos.x,
                        _offset.y + parentPos.y );
    _shape.setFillColor( _color );
}

void Connector::update( )
{
    // Only update your own value if you are of type OUTPUT.
    if( _type == INPUT )
        return;

    _value = _parent->getValue();
}

void Connector::render( sf::RenderWindow *renderWindow )
{
    renderWindow->draw( _shape );
    _shape.setFillColor( _color );
}