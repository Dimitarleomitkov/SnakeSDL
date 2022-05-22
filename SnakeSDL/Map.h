#pragma once
#include "Game.h"
#include "Snake.h"
#include "Apple.h"

class Map
{
public:
	Map();
	~Map();

	void LoadMap();
	void DrawMap();

	vector<int> ReturnAvailableSpace(Snake* the_snake, GameObject* the_apple);

private:
	SDL_Rect source, destination;
	SDL_Texture* ground;

	int map[30][40];

};

