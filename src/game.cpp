
#include "../includes/game.hpp"
#include "../includes/collision_control.hpp"

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
        _selectedObject->setColor( sf::Color( 180, 0, 0 ) );
        if( dynamic_cast<Component*>( _selectedObject ) )
            dynamic_cast<Component*>( _selectedObject )->setPosition( sf::Mouse::getPosition( *_renderWindow ) );
        else 
        {
            sf::Vector2f connectorPosition = dynamic_cast<Connector*>( _selectedObject )->getPosition();
            sf::Vector2f mousePosition = (sf::Vector2f) sf::Mouse::getPosition( *_renderWindow );

            float lineLength = sqrt( pow( ( connectorPosition.x - mousePosition.x ), 2 ) + pow( ( connectorPosition.y - mousePosition.y ), 2 ) );

            sf::RectangleShape line{ sf::Vector2f{ lineLength, 5 } };

            float angle = 180 + atan2( connectorPosition.y  - mousePosition.y, connectorPosition.x - mousePosition.x ) * 180 / M_PI ;

            line.rotate( angle );
            line.setPosition( connectorPosition );

            _renderWindow->draw( line );
        }
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
                {
                    if( !CollisionHandler::checkCollisionPoint( _components, sf::Mouse::getPosition( *_renderWindow ) ) )
                    {
                        Component *newComponent{ new Component{ sf::Mouse::getPosition( *_renderWindow ) } };
                        if( !CollisionHandler::checkCollisionRectangle( _components, newComponent ) )
                            _components.push_back( newComponent );
                        else
                            delete newComponent;
                    }
                    else
                    {
                        Component *component = CollisionHandler::checkCollisionPoint( _components, sf::Mouse::getPosition( *_renderWindow ) );
                        Connector *connector = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );
                        if( _selectedObject && (_selectedObject == static_cast<Component*>( component ) || _selectedObject == static_cast<Connector*>( connector ) ) )
                        {
                            if( dynamic_cast<Component*>( _selectedObject ) )
                            {
                                if( !CollisionHandler::checkCollisionRectangle( _components, static_cast<Component*>( _selectedObject ) ) )
                                    _selectedObject = nullptr;
                            }
                            else
                                _selectedObject = nullptr;
                        }
                        else if ( !_selectedObject )
                        {
                            _selectedObject = component;
                            if( connector )
                                _selectedObject = connector;
                        }
                    }
                }
                break;
        
            default:
                break;
        }
    }
}