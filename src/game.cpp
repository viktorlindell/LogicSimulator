
#include "../includes/game.hpp"

#include <iostream>

Game::Game(sf::RenderWindow *window)
    : _renderWindow{ window }
{
    _eventManager.Init( _renderWindow, &_objectManager );
    _interfaceManager.Init( &_eventManager );
}

void Game::run()
{
    // Process events
    _eventManager.listen();

    // Update everything
    _objectManager.update();
    _interfaceManager.update();

    // Render everything
    _objectManager.render( _renderWindow );
    _interfaceManager.render( _renderWindow );
}

/* // Creates a line object between the currently selected component and the mouse!
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
 */
