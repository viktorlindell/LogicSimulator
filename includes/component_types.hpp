#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include "../includes/component.hpp"
#include <vector>

class Light : public Component
{
public:
    Light( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x5DB53FFF )}
    {
        createConnector( sf::Vector2i{ 0, 25 }, ConnectorType::INPUT );

        _light.setOrigin( _light.getSize().x / 2, _light.getSize().y / 2 );
        _light.setPosition( ( sf::Vector2f )position );
        _light.setFillColor( sf::Color( 0xB5B5B5FF ) );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        _value = false;
        if( _inputConnectors.front()->getValue() )
            _value = true;

        // Should be done last
        Component::update( renderWindow );
    };

    void render( sf::RenderWindow *renderWindow ) override
    {
        Component::render( renderWindow );
        
        _light.setFillColor( sf::Color( 0xB5B5B5FF ) );
        if( _value )
            _light.setFillColor( sf::Color( 0xFFEC42FF ) );

        renderWindow->draw( _light );
    }

    void setPosition( sf::Vector2i const& newPos ) override
    {
        Component::setPosition( newPos );
        _light.setPosition( newPos.x, newPos.y );
    }

private:
    sf::RectangleShape _light{ sf::Vector2f( 60.f, 30.f ) };

};

class And : public Component
{
public:
    And( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x5DB53FFF )}
    {
        createConnector( sf::Vector2i{ -25 , 25 }, ConnectorType::INPUT);
        createConnector( sf::Vector2i{ 25 , 25 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ 0 , -25 }, ConnectorType::OUTPUT );

        setText( "AND" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        // Should be done last
        _value = true;

        for( Connector* inputConnector: _inputConnectors )
            if ( !inputConnector->getValue() )
                _value = false;
        
        Component::update( renderWindow );
    };

private:

};

class Or : public Component
{
public:
    Or( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x5DB53FFF )}
    {
        createConnector( sf::Vector2i{ -25 , 25 }, ConnectorType::INPUT);
        createConnector( sf::Vector2i{ 25 , 25 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ 0 , -25 }, ConnectorType::OUTPUT );

        setText( "OR" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        // Should be done last
        _value = false;

        for( Connector* inputConnector: _inputConnectors )
            if ( inputConnector->getValue() )
                _value = true;
        
        Component::update( renderWindow );
    };

private:

};

class Xor : public Component
{
public:
    Xor( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x5DB53FFF )}
    {
        createConnector( sf::Vector2i{ -25 , 25 }, ConnectorType::INPUT);
        createConnector( sf::Vector2i{ 25 , 25 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ 0 , -25 }, ConnectorType::OUTPUT );

        setText( "XOR" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        // Should be done last
        _value = false;
        if( _inputConnectors.front()->getValue() != _inputConnectors.back()->getValue() )
            _value = true;
        
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
        createConnector( sf::Vector2i{ -25 , -25 }, ConnectorType::OUTPUT, false );
        createConnector( sf::Vector2i{ 25 , -25 }, ConnectorType::OUTPUT, false );

        setText( "Ground" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        // Should be done last
        _value = false;

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
        createConnector( sf::Vector2i{ -25 , -25 }, ConnectorType::OUTPUT, true );
        createConnector( sf::Vector2i{ 25 , -25 }, ConnectorType::OUTPUT, true );   

        setText( "5 V" );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {
        _value = true;

        // Should be done last
        Component::update( renderWindow );
    };

private:

};

#endif
