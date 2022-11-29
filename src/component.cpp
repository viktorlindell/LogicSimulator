
#include "../includes/component.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>

Component::Component(sf::Vector2i const& pos, sf::Color const& color)
    : _shape{ sf::Vector2f{ 100.f, 50.f } }, _color{ color }
{
    _shape.setFillColor( _color );
    _shape.setPosition( pos.x, pos.y );
    _shape.setOrigin( _shape.getSize().x / 2, _shape.getSize().y / 2 );

    _connectors.push_back( Connector{ sf::Vector2i{ -0, -25 }, (sf::Vector2i)_shape.getPosition() } );
    _connectors.push_back( Connector{ sf::Vector2i{ -25, 25 }, (sf::Vector2i)_shape.getPosition() } );
    _connectors.push_back( Connector{ sf::Vector2i{ +25, 25 }, (sf::Vector2i)_shape.getPosition() } );
}

void Component::render(sf::RenderWindow  *renderWindow)
{
    renderWindow->draw( _shape );
    _shape.setFillColor( _color );

    for (Connector & c : _connectors )
    {
        if( CollisionController::checkCollisionPoint( c.getShape(), sf::Mouse::getPosition( *renderWindow ) ) )
            c.setColor( sf::Color( 180, 0, 0 ) );
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