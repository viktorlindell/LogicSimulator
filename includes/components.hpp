#pragma once

#include <SFML/Graphics.hpp>

struct Renderable
{
    sf::RectangleShape _shape;
    sf::Color _color;
};

struct Transform
{
    sf::Vector2f _position;
    sf::Vector2f _scale;
    float _angle;
};
