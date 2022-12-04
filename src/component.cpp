
#include "../includes/component.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>

Component::Component( sf::Vector2i const& pos, sf::Color const& color )
    : Object{ sf::Vector2f{ 120.f, 70.f }, color }
{
    _shape.setFillColor( _color );
    _shape.setPosition( pos.x, pos.y );
    _shape.setOrigin( _shape.getSize().x / 2, _shape.getSize().y / 2 );

    _connectors.push_back( new Connector{ sf::Vector2i{ -0, -25 }, (sf::Vector2i)_shape.getPosition(), this } );
    _connectors.push_back( new Connector{ sf::Vector2i{ -25, 25 }, (sf::Vector2i)_shape.getPosition(), this } );
    _connectors.push_back( new Connector{ sf::Vector2i{ +25, 25 }, (sf::Vector2i)_shape.getPosition(), this } );
}

void Component::update( sf::RenderWindow *renderWindow )
{

}

void Component::render( sf::RenderWindow  *renderWindow )
{
    renderWindow->draw( _shape );
    setColor( _color );

    for (Connector *c : _connectors )
    {
        c->render( renderWindow );
    }
}

void Component::setPosition( sf::Vector2i const& newPos )
{
    _shape.setPosition( newPos.x, newPos.y );
    for (Connector *c : _connectors )
    {
        c->setPosition( newPos );
    }
}