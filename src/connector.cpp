#include "../includes/connector.hpp"
#include "../includes/collision_control.hpp"

#include "cmath"

Connector::Connector(sf::Vector2i const& pos, sf::Vector2i const& parentPos, Object *parent, ConnectorType type, sf::Color const& color )
    : Object{ sf::Vector2f{ 30.f, 20.f }, color }, _offset{ pos }, _parent{ parent }, _type{ type }
{
    _shape.setOrigin( sf::Vector2f{ _shape.getSize().x / 2, _shape.getSize().y / 2 } );
    _shape.setPosition( _offset.x + parentPos.x,
                        _offset.y + parentPos.y );
    _shape.setFillColor( _color );
}

void Connector::update( sf::RenderWindow *renderWindow )
{
    // Only update your own value if you are of type OUTPUT.
    if( _type == INPUT )
        return;

    _value = _parent->getValue();

    // Update the value of your connection.
    if( _connection )
        _connection->setValue( _value );
}

void Connector::render( sf::RenderWindow *renderWindow )
{
    if( _connection )
        renderWindow->draw( createLine() );

    renderWindow->draw( _shape );
    _shape.setFillColor( _color );
}

// TODO: Currently both sides of the connection draws a line, fix so it only draws one line.

// Helper fundtion that creates a Rectangle representing a line.
sf::RectangleShape Connector::createLine()
{
    sf::Vector2f connectorPosition = _shape.getPosition();
    sf::Vector2f connectionPosition = _connection->getPosition();

    float lineLength = sqrt( pow( ( connectorPosition.x - connectionPosition.x ), 2 ) + pow( ( connectorPosition.y - connectionPosition.y ), 2 ) );

    sf::RectangleShape line{ sf::Vector2f{ lineLength, 5 } };

    float angle = 180 + atan2( connectorPosition.y  - connectionPosition.y, connectorPosition.x - connectionPosition.x ) * 180 / M_PI ;

    line.rotate( angle );
    line.setPosition( connectorPosition );
    
    return line;
}