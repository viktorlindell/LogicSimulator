#ifndef COMPONENT_H
#define COMPONENT_H

#include "../includes/connector.hpp"
#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

// Enum that specifies what component the user will place.
enum ComponentType : uint32_t
{
    LIGHT, 
    AND,
    OR,
    XOR,
    GROUND,
    POSITIVE,
    MAX_COMPONENTS
};

/// @brief Generic component class, creates a sprite at the provided location.
class Component : public Object
{
public:
    Component( sf::Vector2i const& pos, sf::Color const& color = sf::Color( 180, 180, 180 ) );

    virtual void update( sf::RenderWindow *renderWindow = nullptr );
    virtual void render( sf::RenderWindow *renderWindow );
    virtual void setPosition( sf::Vector2i const& newPos );

    inline std::vector<Connector*> const& getConnectors() const { return _connectors; };

protected:
    void createConnector( sf::Vector2i const& position, ConnectorType type, bool value = false );
    void setText( std::string const& text ); 

public:

protected:
    std::vector<Connector*> _connectors{};
    std::vector<Connector*> _inputConnectors{};
    std::vector<Connector*> _outputConnectors{};
    
    sf::Font _font{};
    sf::Text _text{};
};

#endif