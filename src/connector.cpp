#include "../includes/connector.hpp"
#include "../includes/collision_control.hpp"

#include "cmath"

Connector::Connector(sf::Vector2i const& pos, sf::Vector2i const& parentPos, Component *parent, sf::Color const& color )
    : Object{ sf::Vector2f{ 30.f, 20.f }, color }, _offset{ pos }, _parent{ parent }
{
    _shape.setOrigin( sf::Vector2f{ _shape.getSize().x / 2, _shape.getSize().y / 2 } );
    _shape.setPosition( _offset.x + parentPos.x,
                        _offset.y + parentPos.y );
    _shape.setFillColor( _color );
}

void Connector::render( sf::RenderWindow *renderWindow )
{
    if( _connection )
    {
        sf::Vector2f connectorPosition = _shape.getPosition();
        sf::Vector2f connectionPosition = _connection->getPosition();

        float lineLength = sqrt( pow( ( connectorPosition.x - connectionPosition.x ), 2 ) + pow( ( connectorPosition.y - connectionPosition.y ), 2 ) );

        sf::RectangleShape line{ sf::Vector2f{ lineLength, 5 } };

        float angle = 180 + atan2( connectorPosition.y  - connectionPosition.y, connectorPosition.x - connectionPosition.x ) * 180 / M_PI ;

        line.rotate( angle );
        line.setPosition( connectorPosition );

        renderWindow->draw( line );
    }

    renderWindow->draw( _shape );
    _shape.setFillColor( _color );
}