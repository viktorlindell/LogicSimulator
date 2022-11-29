
#include "../includes/game.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>

Game::Game(sf::RenderWindow *window)
    : _renderWindow{window}, _components{}
{
    _components.push_back( Component{ sf::Vector2i{ 200, 100 } } );
}

void Game::run()
{
    sf::Event event;
    while( _renderWindow->pollEvent( event ) )
    {
        switch ( event.type )
        {
        case sf::Event::Closed:
            _renderWindow->close();
            break;

        case sf::Event::MouseButtonPressed:
            if( event.mouseButton.button == sf::Mouse::Left )
            {
                Component newComp{ sf::Vector2i( event.mouseButton.x, event.mouseButton.y ) };
                if( !checkCollision( newComp.getShape() ) )
                    _components.push_back( newComp );
            }
            break;
        
        default:
            break;
        }
    }

    for( Component & c : _components )
    {   
        if( checkCollisionPoint( c.getShape(), sf::Mouse::getPosition( *_renderWindow ) ) )
            c.setColor( sf::Color( 180, 0, 0 ) );

        c.render( _renderWindow );
    }
}

bool Game::checkCollision(sf::RectangleShape const& shape)
{
    for( Component const& c : _components )
        if( checkCollisionRectangle( shape, c.getShape() ) )
            return true;
 
    return false;
}