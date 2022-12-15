#ifndef CONNECTOR_H
#define CONNECTOR_H

#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <vector>

// Forward declarations:
class Component;

enum ConnectorType
{
    INPUT,
    OUTPUT
};

class Connector : public Object
{
public:
    Connector(  sf::Vector2i const& pos, sf::Vector2i const& parentPos, Object *parent, ConnectorType type, 
                sf::Color const& color = sf::Color( 0x3B3B3BFF ) );

    Connector(const Connector&) = delete;
    Connector* operator=(const Connector&) = delete;

    void update( sf::RenderWindow *renderWindow ) override;
    void render( sf::RenderWindow *renderWindow ) override;

    inline void setPosition ( sf::Vector2i const& newPos ) { _shape.setPosition( _offset.x + newPos.x,
                                                                                _offset.y + newPos.y ); };
    inline void setConnection (Connector *c ) { _connection = c; };
    inline void setValue ( bool value ) { _value = value; };

    inline Connector* const& getConnection () const { return _connection; }; 
    inline sf::Vector2f const& getPosition () const { return _shape.getPosition(); };
    inline Object* const& getParent () const { return _parent; };

private:
    sf::RectangleShape createLine();

private:
    sf::Vector2i _offset;
    Object *_parent;
    Connector *_connection{ nullptr };
    ConnectorType _type;
};

#endif