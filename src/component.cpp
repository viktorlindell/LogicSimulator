
#include "../includes/component.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>

Component::Component( sf::Vector2i const& pos, sf::Color const& color )
    : Object{ sf::Vector2f{ 120.f, 70.f }, color }
{
    _shape.setFillColor( _color );
    _shape.setPosition( pos.x, pos.y );
    _shape.setOrigin( _shape.getSize().x / 2, _shape.getSize().y / 2 );

    if ( font.loadFromFile( "Roboto-Regular.ttf" ) ) // Why cant I read fonts from "../resources/Roboto-Regular.ttf"
        _text.setFont( font );

    _text.setString( "" );
    _text.setCharacterSize( 24 );
    _text.setFillColor( sf::Color( 0xFFFFFFFF ) );
}

void Component::render( sf::RenderWindow  *renderWindow )
{
    renderWindow->draw( _shape );
    renderWindow->draw( _text );
    setColor( _color );

    for (Connector *c : _connectors )
    {
        c->render( renderWindow );
    }
}

void Component::update( sf::RenderWindow *renderWindow )
{
    for (Connector *c : _connectors )
    {
        c->update( renderWindow );
    }
}

void Component::createConnector( sf::Vector2i const& position, bool value )
{
    _connectors.push_back( new Connector{ position, (sf::Vector2i)_shape.getPosition(), this, value } );
}

void Component::setPosition( sf::Vector2i const& newPos )
{
    _shape.setPosition( newPos.x, newPos.y );
    for (Connector *c : _connectors )
    {
        c->setPosition( newPos );
    }

    // Update text position
    float width = _text.getLocalBounds().width;
    float height = _text.getLocalBounds().height;
    _text.setPosition( _shape.getPosition().x - width * .5f, _shape.getPosition().y - height );
}

void Component::setText( std::string const& text )
{
    _text.setString( text );
    float width = _text.getLocalBounds().width;
    float height = _text.getLocalBounds().height;
    _text.setPosition( _shape.getPosition().x - width * .5f, _shape.getPosition().y - height );
}