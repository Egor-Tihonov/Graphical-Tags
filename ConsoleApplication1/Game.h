#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;

class Game
{
private:
	static const int X = 4;
	static const int Y = 4;
	bool win;

	int correct_field[X][Y];
	int game_field[X][Y];

	std::vector<Texture> textures;
	Sprite sprite[17];

	bool check_for_repeate(int);
	bool find_elem(int, int&, int&);
	void generate_field();
	void set_texture(std::string);
	void fill_sprites();

public:
	static int BLOCK_WIDTH;
	static int LEFT_INDENT, TOP_INDENT;

	Game(int, int, int);

	bool logic(int, int, RenderWindow&);
	bool victory();

	void start_game(std::string, std::string, RenderWindow&);
	void draw_field(RenderWindow&);
	bool move_tile(int, int);
};

