
#include "../includes/object_manager.hpp"

void ObjectManager::update()
{
    for( Object *c : _gameObjects )
    {   
        c->update();
    }
}

void ObjectManager::render( sf::RenderWindow *renderWindow )
{
    if( _selectedObject )
    {
        _selectedObject->setColor( sf::Color( 0xFF0000FF ) );
        if( dynamic_cast<Component*>( _selectedObject ) )
            dynamic_cast<Component*>( _selectedObject )->setPosition( sf::Mouse::getPosition( *renderWindow ) );

        if( dynamic_cast<Connector*>( _selectedObject ) )
            renderWindow->draw( createLine( sf::Mouse::getPosition( *renderWindow ) ) );
    }

    // Render all game objects.
    for( Object *c : _gameObjects )
        c->render( renderWindow );
}

bool ObjectManager::createGameObject( sf::Vector2i position, uint32_t type )
{
    Component *newComponent;
    if ( type == ComponentType::LIGHT )
        newComponent = new Light{ position };
    else if( type == ComponentType::AND )
        newComponent = new And{ position };
    else if( type == ComponentType::OR )
        newComponent = new Or{ position };
    else if( type == ComponentType::XOR )
        newComponent = new Xor{ position };
    else if( type == ComponentType::GROUND )
        newComponent = new Ground{ position };
    else if( type == ComponentType::POSITIVE )
        newComponent = new Positive{ position };
    else
        return false;

    if( !CollisionHandler::checkCollisionRectangle( _gameObjects, static_cast<Component*>( newComponent ) ) )
    {
        _gameObjects.push_back( newComponent );
        return true;
    }

    delete newComponent;
    return false;
}

void ObjectManager::deleteGameObject()
{
    
}

sf::RectangleShape ObjectManager::createLine( sf::Vector2i const& position )
{
    sf::Vector2f connectorPosition = dynamic_cast<Connector*>( _selectedObject )->getPosition();
    sf::Vector2f mousePosition = (sf::Vector2f)position;

    float lineLength = sqrt( pow( ( connectorPosition.x - mousePosition.x ), 2 ) + pow( ( connectorPosition.y - mousePosition.y ), 2 ) );

    sf::RectangleShape line{ sf::Vector2f{ lineLength, 5 } };

    float angle = 180 + atan2( connectorPosition.y  - mousePosition.y, connectorPosition.x - mousePosition.x ) * 180 / M_PI ;

    line.rotate( angle );
    line.setPosition( connectorPosition );
    line.setFillColor( sf::Color( 0x737373FF ) );
    
    return line;
}