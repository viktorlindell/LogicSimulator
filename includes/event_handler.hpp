#include "../includes/object.hpp"
#include "../includes/collision_control.hpp"

class Component;
class Connector;

namespace EventHandler
{
    static void mouseEvent()
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
            if( _selectedObject )
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
};