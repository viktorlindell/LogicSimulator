
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