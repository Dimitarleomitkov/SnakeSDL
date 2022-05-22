#pragma once
#include "GameObject.h"

using namespace std;

static int CheckForCollision();

class Snake
{
public:
	Snake();
	~Snake();

	int Move(GameObject* apple);
	void Render();

	void SetOrientation(ORIENTATION ori);
	int CheckForCollision(GameObject* apple);

	GameObject* GetSnakeHead();
	vector<GameObject*> GetSnakeBody();

	void ExpandBody();
	void IncreaseSpeed();
	bool CheckBodyCollision();

private:
	GameObject* snakeHead;
	vector<GameObject*> snakeBody;
	ORIENTATION orientation;
	int speed; // maximum 59 because of the game's FPS
};

