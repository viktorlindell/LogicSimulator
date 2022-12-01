#ifndef COMPONENT_H
#define COMPONENT_H

#include "../includes/connector.hpp"
#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

class Component : public Object
{
public:
    Component( sf::Vector2i const& pos, sf::Color const& color = sf::Color( 180, 180, 180 ) );

    void update( sf::RenderWindow *renderWindow );
    void render( sf::RenderWindow *renderWindow );
    void setPosition( sf::Vector2i const& newPos );

    // Inline functions
    inline std::vector<Connector*> const& getConnectors() const { return _connectors; };

public:

private:
    std::vector<Connector*> _connectors{};

};

#endif