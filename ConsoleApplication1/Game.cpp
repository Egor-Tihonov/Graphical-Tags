#include "Game.h"
#include <SFML/Graphics.hpp>
#include <numeric>
#include <time.h>
#include <Windows.h>



Game::Game(int size_of_tile, int left_indent, int top_indent)
{
	LEFT_INDENT = left_indent;
	TOP_INDENT = top_indent;
	game_field[X][Y] = { 0 };
	win = false;

	BLOCK_WIDTH = size_of_tile;

	for (int i = 0; i < X; i++) {
		for (int j = 0; j < Y; j++) {
			correct_field[i][j] = 1 + j + i * X;
		}
	}
}

void Game::start_game(std::string tiles, std::string background, RenderWindow& window)
{
	set_texture(background);
	set_texture(tiles);
	fill_sprites();
	generate_field();
	draw_field(window);
	logic(window);
}

void Game::draw_field(RenderWindow& window)
{
	int numb = 0;
	sprite[numb].setTexture(textures[numb]);
	window.draw(sprite[0]);
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
		{
			numb = game_field[i][j];
			sprite[numb].setPosition(j * BLOCK_WIDTH + LEFT_INDENT, i * BLOCK_WIDTH + TOP_INDENT);
			window.draw(sprite[numb]);
		}
	}
}

bool Game::check_for_repeate(int a)
{
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (game_field[i][j] == a && a == 0) // if a is 0 we allow to stay
			{
				return true;
			}
			else if (game_field[i][j] == a)
			{
				return false;
			}
		}
	}
	return true;
}

bool Game::find_elem(int a, int& xa, int& ya)
{

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < X; j++)
		{
			if (game_field[i][j] == a)
			{
				xa = i;
				ya = j;
				return 1;
			}
		}
	}

	return 0;
}

void Game::generate_field()
{
	int new_value = 0;
	bool a = false;

	srand(time(0));
	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			do
			{
				new_value = 1 + rand() % 16;
				a = check_for_repeate(new_value);
			} while (!a);

			game_field[i][j] = new_value;
		}
	}
}


bool Game::logic(int mouse_x, int mouse_y, RenderWindow& window)
{
	win = move_tile(mouse_x, mouse_y);
	if (win) {
		bool ok = victory();
		if (!ok) {
			return 1;
		}


		for (int i = 0; i < X; i++)
		{
			memset(game_field[i], 0, sizeof(int) * X);
		}

		generate_field();
	}

	return 1;
}

bool Game::victory()
{
	int ok = MessageBoxA(NULL, "Victory!\n Do you want try again?", "Game", MB_YESNO);
	if (ok == IDNO) {
		return 0;
	}
	else if (ok == IDYES) {
		return 1;
	}
	return 1;
}

void Game::set_texture(std::string path)
{
	Texture new_texture;
	new_texture.loadFromFile(path);
	textures.push_back(new_texture);
}

void Game::fill_sprites()
{
	for (int i = 0, n = 1; i < X; i++) {
		for (int j = 0; j < X; j++)
		{
			sprite[n].setTexture(textures[1]);
			sprite[n].setTextureRect(sf::IntRect(j * BLOCK_WIDTH, i * BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH));
			n++;
		}
	}
}

bool Game::move_tile(int mouse_x, int mouse_y) {
	int xa = 0, ya = 0;

	bool ok = find_elem(16, xa, ya);
	if (!ok) {
		return 0;
	}

	if ((game_field[mouse_y - 1][mouse_x] == 16 && mouse_y - 1 >= 0) || (game_field[mouse_y + 1][mouse_x] == 16 && mouse_y + 1 <= 3) || (game_field[mouse_y][mouse_x + 1] == 16 && mouse_x + 1 <= 3) || (game_field[mouse_y][mouse_x - 1] == 16 && mouse_x - 1 >= 0))
	{
		game_field[xa][ya] = game_field[mouse_y][mouse_x]; // move numbers
		game_field[mouse_y][mouse_x] = 16;

	}
	else
	{
		return 0;
	}

	for (int i = 0; i < X; i++)
	{
		for (int j = 0; j < Y; j++)
		{
			if (game_field[i][j] != correct_field[i][j])
			{
				return 0;
			}
		}
	}
	return 1;
}