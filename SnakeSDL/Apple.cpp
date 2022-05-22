#include "Apple.h"
#include <random>
#include <time.h>
#include <iostream>

Apple::Apple(int XsnakeHead, int YsnakeHead)
{
	srand(time(NULL));

	int x = ((rand() % (800 - 20)) / 20) * 20;
	int y = ((rand() % (600 - 20)) / 20) * 20; 

	while (x == XsnakeHead && y == YsnakeHead) {
		x = ((rand() % (800 - 20)) / 20) * 20;
		y = ((rand() % (600 - 20)) / 20) * 20; 
	}

	apple = new GameObject("resources/darkred.png", x, y);
}

void Apple::Render()
{
	apple->Render();
}

GameObject* Apple::AsObject()
{
	return apple;
}

void Apple::Move(vector<int> avSpace)
{
	int newPos = rand() % avSpace.size();

	apple->SetX(((int)avSpace[newPos] % 40) * 20);
	apple->SetY(((int)avSpace[newPos] / 40) * 20);

	apple->UpdateDestinationRect(apple->GetX(), apple->GetY());
}