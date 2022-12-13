#ifndef COMPONENT_H
#define COMPONENT_H

#include "../includes/connector.hpp"
#include "../includes/object.hpp"

#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

/// @brief Generic component class, creates a sprite at the provided location.
class Component : public Object
{
public:
    Component( sf::Vector2i const& pos, sf::Color const& color = sf::Color( 180, 180, 180 ) );

    virtual void update( sf::RenderWindow *renderWindow );
    virtual void render( sf::RenderWindow *renderWindow );
    virtual void setPosition( sf::Vector2i const& newPos );
    // Inline functions
    inline std::vector<Connector*> const& getConnectors() const { return _connectors; };

protected:
    void createConnector( sf::Vector2i const& position, bool value = false );
    void setText( std::string const& text ); 

public:

protected:
    std::vector<Connector*> _connectors{};
    sf::Font font{};
    sf::Text _text{}; 
    bool value{ false };

};

#endif