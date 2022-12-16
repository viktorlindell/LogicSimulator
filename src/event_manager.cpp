#include "../includes/event_manager.hpp"

void EventManager::Init( sf::RenderWindow *renderWindow, ObjectManager *objectManager )
{
    _renderWindow = renderWindow;
    _objectManager = objectManager;
}

void EventManager::listen()
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
                if( event.mouseButton.button == sf::Mouse::Left ) 
                    leftMouseEvent();
                break;
        
            case sf::Event::KeyPressed:
                keyboardEvent( event );

            default:
                break;
        }
    }
}

void EventManager::keyboardEvent( sf::Event const& event )
{
    if( event.key.code == sf::Keyboard::M )
    {
        _type++;
        if( _type >= ComponentType::MAX_COMPONENTS )
            _type = 0;
    }
    else if( event.key.code == sf::Keyboard::N )
    {
        _type--;
        if( _type >= ComponentType::MAX_COMPONENTS )
            _type = ComponentType::MAX_COMPONENTS - 1;
    }
}

void EventManager::leftMouseEvent()
{
    // Check if user pressed on existing component
    Component *component = CollisionHandler::checkCollisionPoint( _objectManager->getGameObjects(), sf::Mouse::getPosition( *_renderWindow ) );
    
    // Create new component 
    if( !_objectManager->getSelectedGameObject() && !component )
    {
        if( _objectManager->createGameObject( sf::Mouse::getPosition( *_renderWindow ), _type ) ) 
            return;
    }

    // Clicked on nothing but has something selected, do nothing!
    if ( !component ) return;

    // Select component
    if ( !_objectManager->getSelectedGameObject() ) 
    {
        _objectManager->setSelectedGameObject( component );

        // Check if user clicked on connector of said Component.
        Connector *connector = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );
        if( connector )
            _objectManager->setSelectedGameObject( connector );
        return;
    }

    // Deselected component
    if( dynamic_cast<Component*>( _objectManager->getSelectedGameObject() ) == component )
    {
        _objectManager->setSelectedGameObject( nullptr );
        return;
    }

    // Something weird happend
    if ( !dynamic_cast<Connector*>( _objectManager->getSelectedGameObject() ) ) return;

    // Only possibility left is that the user clicked on a connector! 
    modifyConnection( component );
}

void EventManager::modifyConnection( Component *component )
{
    Connector *connector = CollisionHandler::checkCollisionPoint( component->getConnectors(), sf::Mouse::getPosition( *_renderWindow ) );   
    if( !connector ) return;

    if( connector == static_cast<Connector*>( _objectManager->getSelectedGameObject() ) )
    {
        _objectManager->setSelectedGameObject( nullptr );
        return;
    }
    
    for( Component *c : _objectManager->getGameObjects() )
    {
        if( c == dynamic_cast<Component*>( dynamic_cast<Connector*>( _objectManager->getSelectedGameObject() )->getParent() ) ) continue;

        // Create connection between components.
        if( !static_cast<Connector*>( _objectManager->getSelectedGameObject() )->getConnection() )
        {
            static_cast<Connector*>( _objectManager->getSelectedGameObject() )->setConnection( connector );
            connector->setConnection( static_cast<Connector*>( _objectManager->getSelectedGameObject() ) );
            _objectManager->setSelectedGameObject( nullptr );
            break;
        }

        // Remove connection between components.
        else
        {
            static_cast<Connector*>( _objectManager->getSelectedGameObject() )->setValue( false );
            static_cast<Connector*>( _objectManager->getSelectedGameObject() )->setConnection( nullptr );
            connector->setValue( false );
            connector->setConnection( nullptr );
            _objectManager->setSelectedGameObject( nullptr );
            break;
        }
    }
}