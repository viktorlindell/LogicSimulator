
#include "../includes/game.hpp"
#include "../includes/collision_control.hpp"
#include "../includes/event_handler.hpp"

#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow *window)
    : _renderWindow{window}, _components{}
{
}

void Game::run()
{
    eventHandler();

    if( _selectedObject )
    {
        _selectedObject->setColor( sf::Color( 0xFF0000FF ) );
        if( dynamic_cast<Component*>( _selectedObject ) )
            dynamic_cast<Component*>( _selectedObject )->setPosition( sf::Mouse::getPosition( *_renderWindow ) );

        else if ( !dynamic_cast<Connector*>( _selectedObject )->getConnection() )
            _renderWindow->draw( createLine() );
    }

    for( Object *c : _components )
    {   
        c->update( _renderWindow );
        c->render( _renderWindow );
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
                    EventHandler::mouseEvent();
                break;
        
            default:
                break;
        }
    }
}

sf::RectangleShape Game::createLine()
{
    sf::Vector2f connectorPosition = dynamic_cast<Connector*>( _selectedObject )->getPosition();
    sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition( *_renderWindow );

    float lineLength = sqrt( pow( ( connectorPosition.x - mousePosition.x ), 2 ) + pow( ( connectorPosition.y - mousePosition.y ), 2 ) );

    sf::RectangleShape line{ sf::Vector2f{ lineLength, 5 } };

    float angle = 180 + atan2( connectorPosition.y  - mousePosition.y, connectorPosition.x - mousePosition.x ) * 180 / M_PI ;

    line.rotate( angle );
    line.setPosition( connectorPosition );
    
    return line;
}