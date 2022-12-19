
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

    // Only update the logic every 10:th frame.
    if( updateCounter % 10 == 0 )
    {
        // Update everything
        _objectManager.update();
        _interfaceManager.update();
    }

    // Render everything
    _objectManager.render( _renderWindow );
    _interfaceManager.render( _renderWindow );

    updateCounter++;
    fps_limiter();
}

void Game::fps_limiter()
{
    sf::sleep( sf::milliseconds( 1000 / 60 ) - _clock.restart() );
}
