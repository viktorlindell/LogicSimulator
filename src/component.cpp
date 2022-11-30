
#include "../includes/component.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>

Component::Component( sf::Vector2i const& pos, sf::Color const& color )
    : _shape{ sf::Vector2f{ 100.f, 50.f } }, _color{ color }
{
    _shape.setFillColor( _color );
    _shape.setPosition( pos.x, pos.y );
    _shape.setOrigin( _shape.getSize().x / 2, _shape.getSize().y / 2 );

    _connectors.push_back( Connector{ sf::Vector2i{ -0, -25 }, (sf::Vector2i)_shape.getPosition() } );
    _connectors.push_back( Connector{ sf::Vector2i{ -25, 25 }, (sf::Vector2i)_shape.getPosition() } );
    _connectors.push_back( Connector{ sf::Vector2i{ +25, 25 }, (sf::Vector2i)_shape.getPosition() } );
}

bool Component::checkCollision( sf::RenderWindow *renderWindow )
{
    bool connectorCollision{ false };
    for (Connector & c : _connectors )
    {
        connectorCollision = c.checkCollision( renderWindow );
        if( connectorCollision )
            break;
    }
    if( !connectorCollision )
        if( CollisionHandler::checkCollisionPoint( _shape, sf::Mouse::getPosition( *renderWindow ) ) )
        {
            setColor( sf::Color( 180, 0, 0 ) );
            return true;
        }

    return false;
}

void Component::update( sf::RenderWindow *renderWindow )
{
    if( selected )
        setPosition( sf::Mouse::getPosition( *renderWindow ) );
}

void Component::render( sf::RenderWindow  *renderWindow )
{
    renderWindow->draw( _shape );
    setColor( _color );

    for (Connector & c : _connectors )
    {
        c.render( renderWindow );
    }
}

void Component::setPosition( sf::Vector2i const& newPos )
{
    _shape.setPosition( newPos.x, newPos.y );
    for (Connector & c : _connectors )
    {
        c.setPosition( newPos );
    }
}