#pragma once
#include "GameObject.h"

using namespace std;

class Apple
{
public:
	Apple(int XsnakeHead, int YsnakeHead);
	~Apple();

	void Move(vector<int> avSpace);
	void Render();

	GameObject* AsObject();

private:
	GameObject* apple;
};

