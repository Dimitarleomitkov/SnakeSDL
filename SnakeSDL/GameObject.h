#pragma once
#include "Game.h"

class GameObject
{
public:
	GameObject(const char* texturesheet, int x, int y);
	~GameObject();

	void MoveLeft();
	void MoveUp();
	void MoveRight();
	void MoveDown();
	void Render();

	int GetX();
	int GetY();
	void SetX(int X);
	void SetY(int Y);

	void UpdateDestinationRect(int X, int Y);

private:
	int xpos;
	int ypos;

	SDL_Texture* objectTexture;
	SDL_Rect sourceRectangle;
	SDL_Rect destinationRectangle;
};

