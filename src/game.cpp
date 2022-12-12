
#include "../includes/game.hpp"
#include "../includes/collision_control.hpp"

#include <iostream>
#include <cmath>

Game::Game(sf::RenderWindow *window)
    : _renderWindow{ window }, _components{}
{
}

void Game::run()
{
    processEvents();

    if( _selectedObject )
    {
        _selectedObject->setColor( sf::Color( 0xFF0000FF ) );
        if( dynamic_cast<Component*>( _selectedObject ) )
            dynamic_cast<Component*>( _selectedObject )->setPosition( sf::Mouse::getPosition( *_renderWindow ) );

        else if ( dynamic_cast<Connector*>( _selectedObject ) )
            _renderWindow->draw( createLine() );
    }

    for( Object *c : _components )
    {   
        c->update( _renderWindow );
        c->render( _renderWindow );
    }
}

void Game::processEvents()
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

            // User pressed mouse button
            case sf::Event::MouseButtonPressed:
                if( event.mouseButton.button == sf::Mouse::Left ) leftMouseEvent();
                break;
        
            default:
                break;
        }
    }
}

// Processes a left mouse button event
void Game::leftMouseEvent()
{
    // Check if user pressed on existing component
    Component *component = CollisionHandler::checkCollisionPoint( _components, sf::Mouse::getPosition( *_renderWindow ) );
    
    // Create new component 
    if( !_selectedObject && !component )
    {
        if( createComponent() ) return;
    }

    // Clicked on nothing but has something selected, do nothing!
    if ( !component ) return;

    // Clicked on component & has nothing selected.
    if ( !_selectedObject ) 
    {
        _selectedObject = component;
        // Check if user clicked on connector of said Component.
        if( CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) ) )
            _selectedObject = CollisionHandler::checkCollisionPoint(    component->getConnectors(), 
                                                                        sf::Mouse::getPosition( *_renderWindow ) );
        return;
    }

    // Deselected component
    if( dynamic_cast<Component*>( _selectedObject ) == component )
    {
        _selectedObject = nullptr;
        return;
    }

    // Something weird happend
    if ( !dynamic_cast<Connector*>( _selectedObject ) ) return;

    // Only possibility left is that the user clicked on a connector! 
    modifyConnection( component );
}

// Check how to handle to connector: create/destroy connection to another connector or select/deselect a connector
void Game::modifyConnection( Component *component )
{
    Connector *connector = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );   
    if( !connector ) return;
    if( connector == static_cast<Connector*>( _selectedObject ) )
    {
        _selectedObject = nullptr;
        return;
    }
    
    for( Component *c : _components)
    {
        if( c == dynamic_cast<Component*>( dynamic_cast<Connector*>( _selectedObject )->getParent() ) ) continue;

        if( !static_cast<Connector*>( _selectedObject )->getConnection() )
        {
            static_cast<Connector*>( _selectedObject )->setConnection( connector );
            connector->setConnection( static_cast<Connector*>( _selectedObject ) );
            _selectedObject = nullptr;
            break;
        }
        else
        {
            static_cast<Connector*>( _selectedObject )->setConnection( nullptr );
            connector->setConnection( nullptr );
            _selectedObject = nullptr;
            break;
        }
    }
}

// Creates a new component and returns true if succesful
bool Game::createComponent()
{
    Component *newComponent{ new Component{ sf::Mouse::getPosition( *_renderWindow ) } };
    if( !CollisionHandler::checkCollisionRectangle( _components, newComponent ) )
    {
        _components.push_back( newComponent );
        return true;
    }

    delete newComponent;
    return false;
}

// Creates a line object between the currently selected component and the mouse!
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