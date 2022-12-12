#ifndef COMPONENT_TYPES_H
#define COMPONENT_TYPES_H

#include "../includes/component.hpp"

class Light : public Component
{
public:
    Light( sf::Vector2i const& position ) 
        : Component{ position, sf::Color( 0x89A18AFF )}
    {
        createConnector( sf::Vector2i{ -25, +25 } );
        createConnector( sf::Vector2i{ +25, +25 } );
    };

    void update( sf::RenderWindow *renderWindow ) override
    {

    };

private:


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

    };

private:

};

#endif
