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
    SEVEN_SEGMENT,
    GROUND,
    POSITIVE,
    MAX_COMPONENTS
};

class Component : public Object
{
public:
    Component( sf::Vector2i const& pos, sf::Vector2f const& size = sf::Vector2f{ 120.f, 70.f } );

    virtual void update() override;
    virtual void render( sf::RenderWindow *renderWindow ) override;
    virtual void setPosition( sf::Vector2i const& newPos ) override;

    inline std::vector<Connector*> const& getIConnectors() { return _iConnectors; };
    inline std::vector<Connector*> const& getOConnectors() { return _oConnectors; };
    inline std::vector<Connector*> const& getConnectors() { return _connectors; };

protected:
    void createConnector( sf::Vector2i const& position, ConnectorType type, bool initValue = false );
    void setText( std::string const& text );

private:
    sf::Font _font{};
    sf::Text _text{};

    std::vector<Connector*> _connectors{};
    std::vector<Connector*> _iConnectors{};
    std::vector<Connector*> _oConnectors{};
};

#endif