#include <iostream>
#include "Game.h"

using namespace sf;

int main()
{
    RenderWindow window(sf::VideoMode(1277, 741), "Tags");

    Game game(82, 474, 206);
    game.start_game("./Tiles.png","./Board.png", window);
    return 0;
}