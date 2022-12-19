
#include "../includes/object_manager.hpp"

void ObjectManager::update()
{
    for( Object *c : _gameObjects )
    {   
        c->update();
    }

    for ( auto const& connection : _connections )
    {
        connection.first->setValue( connection.second->getValue() );
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

    // Render all connections between objects.
    for ( auto const& connection : _connections )
    {
        renderWindow->draw( createLine( connection.first->getPosition(), connection.second->getPosition() ) );
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

void ObjectManager::createConnection( Connector *connector )
{
    Connector *selectedConnector = static_cast<Connector*>( _selectedObject );
    if( selectedConnector->getType() == ConnectorType::INPUT )
    {
        if( _connections.find(selectedConnector) != _connections.end() )
            return;
        
        _connections[selectedConnector] = connector;
    }
    else if ( connector->getType() == ConnectorType::INPUT )
    {
        if( _connections.find(connector) != _connections.end() )
            return;
        
        _connections[connector] = selectedConnector;
    }

    std::cout << "Created a new connection. New size is: " << _connections.size() << std::endl;
}

void ObjectManager::deleteConnection( Connector *connector )
{
    Connector *selectedConnector = static_cast<Connector*>( _selectedObject );
    if( selectedConnector->getType() == ConnectorType::INPUT )
    {
        _connections.erase( selectedConnector );
    }
    else if ( connector->getType() == ConnectorType::INPUT )
    {
        _connections.erase( connector );
    }

    selectedConnector->setValue( false );
    connector->setValue( false );
    
    std::cout << "Deleted a connection. New size is: " << _connections.size() << std::endl;
}

bool ObjectManager::isConnected( Connector *connector )
{
    // No limit on number of connections
    if( connector->getType() == ConnectorType::OUTPUT )
        return false;

    if( _connections.find( connector ) == _connections.end() )
        return false;

    return true;
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

sf::RectangleShape ObjectManager::createLine( sf::Vector2f const& position1, sf::Vector2f const& position2 )
{
    float lineLength = sqrt( pow( ( position1.x - position2.x ), 2 ) + pow( ( position1.y - position2.y ), 2 ) );

    sf::RectangleShape line{ sf::Vector2f{ lineLength, 5 } };

    float angle = 180 + atan2( position1.y  - position2.y, position1.x - position2.x ) * 180 / M_PI ;

    line.rotate( angle );
    line.setPosition( position1 );
    line.setFillColor( sf::Color( 0x737373FF ) );
    
    return line;
}

