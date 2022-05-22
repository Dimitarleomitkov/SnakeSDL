#include "Map.h"
#include "TextureManager.h"

Map::Map()
{
	ground = TextureManager::LoadTexture("resources/black.png");

	LoadMap();

	source.h = 20;
	source.w = 20;
	source.x = 0;
	source.y = 0;

	destination.h = 20;
	destination.w = 20;
	destination.x = 0;
	destination.y = 0;
}

void Map::LoadMap()
{
	for (int row = 0; row < 30; row++)
	{
		for (int col = 0; col < 40; col++)
		{
			map[row][col] = 0;
		}
	}
}

void Map::DrawMap()
{
	for (int row = 0; row < 30; row++) {
		for (int col = 0; col < 40; col++) {
			destination.x = col * 20;
			destination.y = row * 20;

			TextureManager::Draw(ground, source, destination);
		}
	}
}

vector<int> Map::ReturnAvailableSpace(Snake* the_snake, GameObject* the_apple)
{
	// Create the 2D array and populate it with 1D coords
	vector<int> availableSpace;

	for (int row = 0; row < 30; row++) {
		for (int col = 0; col < 40; col++) {
			availableSpace.push_back(col + row * 40);
		}
	}

	// Delete the elements that have objects on them
	vector<int>::iterator iter = availableSpace.begin() + (the_snake->GetSnakeHead()->GetX() / 20) + ((the_snake->GetSnakeHead()->GetY() / 20) * 40);
	availableSpace.erase(iter);

	int snakeL = the_snake->GetSnakeBody().size();
	if (snakeL > 0) {
		for (int i = 0; i < snakeL; i++)
		{
			iter = availableSpace.begin() + (the_snake->GetSnakeBody()[i]->GetX() / 20) + ((the_snake->GetSnakeBody()[i]->GetY() / 20) * 40);
			availableSpace.erase(iter);
		}
	}

	return availableSpace;
}