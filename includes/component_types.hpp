#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include "../includes/component.hpp"
#include <vector>

class Light : public Component
{
public:
    Light( sf::Vector2i const& position ) 
        : Component{ position }
    {
        createConnector( sf::Vector2i{ 0, 25 }, ConnectorType::INPUT );

        _light.setOrigin( _light.getSize().x / 2, _light.getSize().y / 2 );
        _light.setPosition( ( sf::Vector2f )position );
        _light.setFillColor( sf::Color( 0xB5B5B5FF ) );
    };

    void update( ) override
    {
        _value = false;
        if( getIConnectors().front()->getValue() )
            _value = true;

        // Should be done last
        Component::update( );
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
        : Component{ position }
    {
        createConnector( sf::Vector2i{ -25 , 25 }, ConnectorType::INPUT);
        createConnector( sf::Vector2i{ 25 , 25 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ 0 , -25 }, ConnectorType::OUTPUT );

        setText( "AND" );
    };

    void update( ) override
    {
        // Should be done last
        _value = true;

        for( Connector* inputConnector: getIConnectors() )
            if ( !inputConnector->getValue() )
                _value = false;
        
        Component::update( );
    };

private:

};

class Or : public Component
{
public:
    Or( sf::Vector2i const& position ) 
        : Component{ position }
    {
        createConnector( sf::Vector2i{ -25 , 25 }, ConnectorType::INPUT);
        createConnector( sf::Vector2i{ 25 , 25 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ 0 , -25 }, ConnectorType::OUTPUT );

        setText( "OR" );
    };

    void update( ) override
    {
        // Should be done last
        _value = false;

        for( Connector* inputConnector: getIConnectors() )
            if ( inputConnector->getValue() )
                _value = true;
        
        Component::update( );
    };

private:

};

class Xor : public Component
{
public:
    Xor( sf::Vector2i const& position ) 
        : Component{ position }
    {
        createConnector( sf::Vector2i{ -25 , 25 }, ConnectorType::INPUT);
        createConnector( sf::Vector2i{ 25 , 25 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ 0 , -25 }, ConnectorType::OUTPUT );

        setText( "XOR" );
    };

    void update( ) override
    {
        // Should be done last
        _value = false;
        if( getIConnectors().front()->getValue() != getIConnectors().back()->getValue() )
            _value = true;
        
        Component::update( );
    };

private:

};

class Ground : public Component
{
public:
    Ground( sf::Vector2i const& position ) 
        : Component{ position }
    {
        createConnector( sf::Vector2i{ -25 , -25 }, ConnectorType::OUTPUT, false );
        createConnector( sf::Vector2i{ 25 , -25 }, ConnectorType::OUTPUT, false );

        setText( "Ground" );
    };

    void update( ) override
    {
        // Should be done last
        _value = false;

        Component::update( );
    };

private:

};

class Positive : public Component
{
public:
    Positive( sf::Vector2i const& position ) 
        : Component{ position }
    {
        createConnector( sf::Vector2i{ -25 , -25 }, ConnectorType::OUTPUT, true );
        createConnector( sf::Vector2i{ 25 , -25 }, ConnectorType::OUTPUT, true );   

        setText( "5 V" );
    };

    void update( ) override
    {
        _value = true;

        // Should be done last
        Component::update( );
    };

private:

};

#endif
