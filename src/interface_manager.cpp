#include "../includes/interface_manager.hpp"

void InterfaceManager::Init( EventManager *eventManager )
{
    _eventManager = eventManager;

    if ( _font.loadFromFile( "Roboto-Bold.ttf" ) ) // Why cant I read fonts from "../resources/Roboto-Regular.ttf"
        _text.setFont( _font );

    _text.setString( "" );
    _text.setCharacterSize( 32 );
    _text.setFillColor( sf::Color( 0xFFFFFFFF ) );
    _text.setPosition( sf::Vector2f( 20.f, 20.f ) );
    _textBox.setFillColor( sf::Color( 0x00000044 ) );
    _textBox.setPosition( sf::Vector2f( 12.f, 20.f ) ); 
}

void InterfaceManager::update()
{
    switch ( _eventManager->getType() )
    {
    case LIGHT:
        _text.setString( "Current component: LIGHT" );
        break;
    case AND:
        _text.setString( "Current component: AND" );
        break;
    case OR:
        _text.setString( "Current component: OR" );
        break;
    case XOR:
        _text.setString( "Current component: XOR" );
        break;
    case SEVEN_SEGMENT:
        _text.setString( "Current component: 7-SEGMENT" );
        break;
    case GROUND:
        _text.setString( "Current component: GROUND" );
        break;
    case POSITIVE:
        _text.setString( "Current component: POSITIVE" );
        break;
    default:
        break;
    }

    _textBox.setSize( sf::Vector2f( _text.getGlobalBounds().width + 16.f, _text.getGlobalBounds().height + 12.f ) );
}

void InterfaceManager::render( sf::RenderWindow *renderWindow )
{
    renderWindow->draw( _textBox );
    renderWindow->draw( _text );
}