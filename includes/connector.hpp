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
    Connector(  sf::Vector2i const& pos, sf::Vector2i const& parentPos, Object *parent, 
                ConnectorType type, sf::Color const& color = sf::Color( 0x3B3B3BFF ) );

    Connector(const Connector&) = delete;
    Connector* operator=(const Connector&) = delete;

    void update( ) override;
    void render( sf::RenderWindow *renderWindow ) override;

    inline void setPosition ( sf::Vector2i const& newPos ) override { _shape.setPosition(   _offset.x + newPos.x,
                                                                                            _offset.y + newPos.y ); };
    
    inline void setValue ( bool value ) { _value = value; };
    inline sf::Vector2f const& getPosition () const { return _shape.getPosition(); };
    inline Object* const& getParent () const { return _parent; };
    inline ConnectorType const& getType() const { return _type; };

private:
    sf::Vector2i _offset;
    Object *_parent;
    ConnectorType _type;
};

#endif