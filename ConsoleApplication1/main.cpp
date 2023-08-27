#include <iostream>
#include "Game.h"

using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(1277, 741), "Tags");

	Game game(82, 474, 206);
	game.start_game("./Tiles.png", "./Board.png", window);
	window.display();

	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == event.Closed) {
				window.close();
			}

			if (event.type == event.MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					Vector2i position = Mouse::getPosition(window);

					int mouse_x = (position.x - game.LEFT_INDENT) / game.BLOCK_WIDTH;
					int mouse_y = (position.y - game.TOP_INDENT) / game.BLOCK_WIDTH;

					bool is_again = game.logic(mouse_x, mouse_y, window);
					if (!is_again) {
						break;
					}

					game.draw_field(window);
					window.display();
				}
			}
		}
	}
	return 0;
}