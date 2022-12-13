#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include "../includes/component.hpp"

class Light : public Component
{
public:
    Light( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x89A18AFF )}
    {
        createConnector( sf::Vector2i{ 0, 25 } );
        _light.setOrigin( _light.getRadius(), _light.getRadius() );
        _light.setFillColor( sf::Color( 0xFFEC42FF ) );
        _light.setPosition( ( sf::Vector2f )position );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        Component::update( renderWindow );
    };

    void render( sf::RenderWindow *renderWindow ) override
    {
        Component::render( renderWindow );
        renderWindow->draw( _light );
    }

    void setPosition( sf::Vector2i const& newPos ) override
    {
        Component::setPosition( newPos );
        _light.setPosition( newPos.x, newPos.y );
    }

private:
    sf::CircleShape _light{ 20.f };

};

class And : public Component
{
public:
    And( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x38E043FF )}
    {
        createConnector( sf::Vector2i{ -25 , 25 } );
        createConnector( sf::Vector2i{ 25 , 25 } );
        createConnector( sf::Vector2i{ 0 , -25 } );

        setText( "AND" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        Component::update( renderWindow );
    };

private:

};

class Ground : public Component
{
public:
    Ground( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x0F0F0FFF )}
    {
        createConnector( sf::Vector2i{ -25 , 25 } );
        createConnector( sf::Vector2i{ 25 , 25 } );

        setText( "Ground" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        Component::update( renderWindow );
    };

private:

};

class Positive : public Component
{
public:
    Positive( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0xF00000FF )}
    {
        createConnector( sf::Vector2i{ -25 , 25 }, true );
        createConnector( sf::Vector2i{ 25 , 25 }, true );

        setText( "5 V" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        Component::update( renderWindow );
    };

private:

};

#endif
