#include "../includes/connector.hpp"

Connector::Connector(sf::Vector2i const& pos, sf::Vector2i const& parentPos, sf::Color const& color )
    : _shape{ sf::Vector2f{ 30.f, 30.f } }, _offset{ pos }, _color{ color }
{
    _shape.setOrigin( sf::Vector2f{ _shape.getSize().x / 2, _shape.getSize().y / 2 } );
    _shape.setPosition( _offset.x + parentPos.x,
                        _offset.y + parentPos.y );
    _shape.setFillColor( _color );
}

void Connector::render(sf::RenderWindow *renderWindow)
{
    renderWindow->draw( _shape );
    _shape.setFillColor( _color );
}