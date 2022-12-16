
#include "../includes/game.hpp"

#include <iostream>

Game::Game(sf::RenderWindow *window)
    : _renderWindow{ window }, _eventManager{}, _objectManager{}
{
/*     if ( _font.loadFromFile( "Roboto-Bold.ttf" ) ) // Why cant I read fonts from "../resources/Roboto-Regular.ttf"
        _text.setFont( _font );

    _text.setString( "" );
    _text.setCharacterSize( 32 );
    _text.setFillColor( sf::Color( 0xFFFFFFFF ) );
    _text.setPosition( sf::Vector2f( 20.f, 20.f ) );
    _textBox.setFillColor( sf::Color( 0x00000044 ) );
    _textBox.setPosition( sf::Vector2f( 12.f, 20.f ) ); */
    //setText();

    _eventManager.Init( _renderWindow, &_objectManager );
}

void Game::run()
{
    // Process events
    _eventManager.listen();

    // Update everything
    _objectManager.update();

    // Render everything
    _objectManager.render( _renderWindow );
}

/* // Processes a left mouse button event
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

    // Select component
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
 */
/* // Check how to handle to connector: create/destroy connection to another connector or select/deselect a connector
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
        // Remove connection between components.
        else
        {
            static_cast<Connector*>( _selectedObject )->setValue( false );
            static_cast<Connector*>( _selectedObject )->setConnection( nullptr );
            connector->setValue( false );
            connector->setConnection( nullptr );
            _selectedObject = nullptr;
            break;
        }
    }
}
 */
/* // Creates a new component and returns true if succesful
bool Game::createComponent()
{
    Component *newComponent;
    sf::Vector2i position = sf::Mouse::getPosition( *_renderWindow );
    if ( _componentType == ComponentType::LIGHT )
        newComponent = new Light{ position };
    else if( _componentType == ComponentType::AND )
        newComponent = new And{ position };
    else if( _componentType == ComponentType::OR )
        newComponent = new Or{ position };
    else if( _componentType == ComponentType::XOR )
        newComponent = new Xor{ position };
    else if( _componentType == ComponentType::GROUND )
        newComponent = new Ground{ position };
    else if( _componentType == ComponentType::POSITIVE )
        newComponent = new Positive{ position };
    else
        return false;

    if( !CollisionHandler::checkCollisionRectangle( _components, static_cast<Component*>( newComponent ) ) )
    {
        _components.push_back( newComponent );
        return true;
    }

    delete newComponent;
    return false;
}
 */
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
/* 
void Game::setText()
{
    switch (_componentType)
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
} */