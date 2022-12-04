
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
        else if ( !dynamic_cast<Connector*>( _selectedObject )->getConnection() )
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
                    Component *component = CollisionHandler::checkCollisionPoint( _components, sf::Mouse::getPosition( *_renderWindow ) );
                    if( !component && !_selectedObject )
                    {
                        Component *newComponent{ new Component{ sf::Mouse::getPosition( *_renderWindow ) } };
                        if( !CollisionHandler::checkCollisionRectangle( _components, newComponent ) )
                            _components.push_back( newComponent );
                        else
                            delete newComponent;
                    }
                    else if ( component )
                    {
                        //Connector *connector = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );
                        if( _selectedObject /*&& (_selectedObject == dynamic_cast<Component*>( mouseCollision ) || _selectedObject == dynamic_cast<Connector*>( connector ) )*/ )
                        {
                            if( dynamic_cast<Component*>( _selectedObject ) )
                            {
                                if( component == static_cast<Component*>( _selectedObject ) )
                                    _selectedObject = nullptr;
                            }
                            else if ( dynamic_cast<Connector*>( _selectedObject ) )
                            {
                                //std::cout << c << " : " << static_cast<Connector*>( _selectedObject ) << std::endl;
                                Connector *connector = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );
                                if( connector == static_cast<Connector*>( _selectedObject ) )
                                    _selectedObject = nullptr;
                                else if( connector )
                                {
                                    for( Component *c : _components)
                                    {
                                        if( c != dynamic_cast<Component*>( dynamic_cast<Connector*>( _selectedObject )->getParent() ) )
                                        {
                                            Connector *other_connector = CollisionHandler::checkCollisionPoint( c->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );
                                            
                                            if( !static_cast<Connector*>( _selectedObject )->getConnection() )
                                            {
                                                if( other_connector )
                                                {
                                                    static_cast<Connector*>( _selectedObject )->setConnection( other_connector );
                                                    other_connector->setConnection( static_cast<Connector*>( _selectedObject ) );
                                                    _selectedObject = nullptr;
                                                    break;
                                                }
                                            }
                                            else
                                            {
                                                if( other_connector == static_cast<Connector*>( _selectedObject )->getConnection() )
                                                {
                                                    static_cast<Connector*>( _selectedObject )->setConnection( nullptr );
                                                    other_connector->setConnection( nullptr );
                                                    _selectedObject = nullptr;
                                                    break;
                                                }
                                            }

                                        }
                                    }
                                }
                            }
                        }
                        // Select a object.
                        else if ( !_selectedObject )
                        {
                            _selectedObject = component;
                            if( CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) ) )
                            {
                                _selectedObject = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );
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