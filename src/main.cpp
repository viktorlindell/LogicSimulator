#include "../includes/game.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow renderWindow(sf::VideoMode(2000, 1400), "Logic Simulator");

    Game game{&renderWindow};

    while (renderWindow.isOpen())
    {
        renderWindow.clear();
        game.run();
        renderWindow.display();
    }

    return 0;
}
