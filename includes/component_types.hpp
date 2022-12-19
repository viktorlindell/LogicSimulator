#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include "../includes/component.hpp"
#include <vector>

class Seven_Segment : public Component
{
public:
    Seven_Segment( sf::Vector2i const& position ) 
        : Component{ position, sf::Vector2f{ 140.f, 250.f } }
    {
        createConnector( sf::Vector2i{ -60, -90 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, -65 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, -40 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, -15 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, 15 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, 40 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, 65 }, ConnectorType::INPUT );
        createConnector( sf::Vector2i{ -60, 90 }, ConnectorType::INPUT );

        _ledA.setOrigin( _ledA.getSize().x / 2, _ledA.getSize().y / 2 );
        _ledB.setOrigin( _ledB.getSize().x / 2, _ledB.getSize().y / 2 );
        _ledC.setOrigin( _ledC.getSize().x / 2, _ledC.getSize().y / 2 );
        _ledD.setOrigin( _ledD.getSize().x / 2, _ledD.getSize().y / 2 );
        _ledE.setOrigin( _ledE.getSize().x / 2, _ledE.getSize().y / 2 );
        _ledF.setOrigin( _ledF.getSize().x / 2, _ledF.getSize().y / 2 );
        _ledG.setOrigin( _ledG.getSize().x / 2, _ledG.getSize().y / 2 );
        
        sf::Vector2f pos = ( sf::Vector2f )position;
        _ledA.setPosition( pos.x + 15.f, pos.y - 115.5f );
        _ledB.setPosition( pos.x + 60.f, pos.y - 57.5f );
        _ledC.setPosition( pos.x + 60.f, pos.y + 57.5f );
        _ledD.setPosition( pos.x + 15.f, pos.y + 115.5f );
        _ledE.setPosition( pos.x - 30.f, pos.y + 57.5f );
        _ledF.setPosition( pos.x - 30.f, pos.y - 57.5f );
        _ledG.setPosition( pos.x + 15.f, pos.y );

        _ledA.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledB.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledC.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledD.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledE.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledF.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledG.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
    };

    void update( ) override
    {
        _ledA.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledB.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledC.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledD.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledE.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledF.setFillColor( sf::Color( 0xB5B5B5FF ) ); 
        _ledG.setFillColor( sf::Color( 0xB5B5B5FF ) ); 

        std::vector<Connector*> connectors = getIConnectors();

        if( connectors.at( 0 )->getValue() )
            _ledA.setFillColor( sf::Color( 0xED0E0EFF ) ); 
        if( connectors.at( 1 )->getValue() )
            _ledB.setFillColor( sf::Color( 0xED0E0EFF ) ); 
        if( connectors.at( 2 )->getValue() )
            _ledC.setFillColor( sf::Color( 0xED0E0EFF ) ); 
        if( connectors.at( 3 )->getValue() )
            _ledD.setFillColor( sf::Color( 0xED0E0EFF ) ); 
        if( connectors.at( 4 )->getValue() )
            _ledE.setFillColor( sf::Color( 0xED0E0EFF ) ); 
        if( connectors.at( 5 )->getValue() )
            _ledF.setFillColor( sf::Color( 0xED0E0EFF ) ); 
        if( connectors.at( 6 )->getValue() )
            _ledG.setFillColor( sf::Color( 0xED0E0EFF ) );

        // Should be done last
        Component::update( );
    };

    void render( sf::RenderWindow *renderWindow ) override
    {
        Component::render( renderWindow );

        renderWindow->draw( _ledA );
        renderWindow->draw( _ledB );
        renderWindow->draw( _ledC );
        renderWindow->draw( _ledD );
        renderWindow->draw( _ledE );
        renderWindow->draw( _ledF );
        renderWindow->draw( _ledG );
    }

    void setPosition( sf::Vector2i const& pos ) override
    {
        Component::setPosition( pos );

        _ledA.setPosition( pos.x + 15.f, pos.y - 115.5f );
        _ledB.setPosition( pos.x + 60.f, pos.y - 57.5f );
        _ledC.setPosition( pos.x + 60.f, pos.y + 57.5f );
        _ledD.setPosition( pos.x + 15.f, pos.y + 115.5f );
        _ledE.setPosition( pos.x - 30.f, pos.y + 57.5f );
        _ledF.setPosition( pos.x - 30.f, pos.y - 57.5f );
        _ledG.setPosition( pos.x + 15.f, pos.y );
    }

private:
    sf::RectangleShape _ledA{ sf::Vector2f( 90.f, 15.f ) };
    sf::RectangleShape _ledB{ sf::Vector2f( 15.f, 90.f ) };
    sf::RectangleShape _ledC{ sf::Vector2f( 15.f, 90.f ) };
    sf::RectangleShape _ledD{ sf::Vector2f( 90.f, 15.f ) };
    sf::RectangleShape _ledE{ sf::Vector2f( 15.f, 90.f ) };
    sf::RectangleShape _ledF{ sf::Vector2f( 15.f, 90.f ) };
    sf::RectangleShape _ledG{ sf::Vector2f( 90.f, 15.f ) };
};

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
