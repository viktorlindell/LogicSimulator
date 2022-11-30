
#include "../includes/game.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>

Game::Game(sf::RenderWindow *window)
    : _renderWindow{window}, _components{}
{
}

void Game::run()
{
    eventHandler();

    for( Component & c : _components )
    {   
        c.checkCollision( _renderWindow );
        c.update( _renderWindow );
        c.render( _renderWindow );
    }
}

void Game::eventHandler()
{
    sf::Event event;
    while( _renderWindow->pollEvent( event ) )
    {
        switch ( event.type )
        {
            // User pressed close button
            case sf::Event::Closed:
                _renderWindow->close();
                break;

            // User pressed the mouse
            case sf::Event::MouseButtonPressed:
                // Left mousebutton pressed
                if( event.mouseButton.button == sf::Mouse::Left )
                {
                    Component newComp{ sf::Vector2i( event.mouseButton.x, event.mouseButton.y ) };
                    if( !checkCollision( newComp.getShape() ) )
                        _components.push_back( newComp );
                    else
                    {
                        for( Component & c : _components )
                        {
                            if( CollisionHandler::checkCollisionPoint( c.getShape(), sf::Mouse::getPosition( *_renderWindow ) ) )
                            {
                                if( c.selected )
                                    c.selected = false;
                                else
                                    c.selected = true;
                            }
                        }
                    }
                }
                break;
        
            default:
                break;
        }
    }
}

bool Game::checkCollision(sf::RectangleShape const& shape)
{
    for( Component & c : _components )
        if( CollisionHandler::checkCollisionRectangle( shape, c.getShape() ) )
            if( c.checkCollision( _renderWindow ) )    
                return true;
 
    return false;
}