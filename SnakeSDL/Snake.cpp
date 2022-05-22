#include "Snake.h"

extern bool blockKeys;

int Snake::CheckForCollision(GameObject* apple)
{
	int XsnakeHead = snakeHead->GetX();
	int YsnakeHead = snakeHead->GetY();

	if (XsnakeHead == apple->GetX() &&
		YsnakeHead == apple->GetY()) {
		return 2;
	} else if (XsnakeHead > 780 ||
				XsnakeHead < 0 ||
				YsnakeHead > 580 ||
				YsnakeHead < 0) {
		snakeHead->SetX(-40);
		snakeHead->SetY(-40);
		snakeHead->UpdateDestinationRect(snakeHead->GetX(), snakeHead->GetY());
		return 1;
	} else if (CheckBodyCollision()) {
		return 1;
	}
	else {
		return 0;
	}
	
	return 0;
}

Snake::Snake()
{
	snakeHead = new GameObject("resources/blue.png", 380, 580);
	orientation = UP;
	speed = 20;
}

int Snake::Move(GameObject* apple)
{
	static Uint8 frameCounter = 0;

	int collision_flag = 0; // 0 - No collision; 1 - Wall or snake body; 2 - Apple

	int phReadX = snakeHead->GetX();
	int phReadY = snakeHead->GetY();
	int phWriteX = phReadX;
	int phWriteY = phReadY;

	if (frameCounter == 60 - speed) {
		switch (orientation) {
			case LEFT:
				snakeHead->MoveLeft();
				collision_flag = CheckForCollision(apple);
				break;
			case UP:
				snakeHead->MoveUp();
				collision_flag = CheckForCollision(apple);
				break;
			case RIGHT:
				snakeHead->MoveRight();
				collision_flag = CheckForCollision(apple);
				break;
			case DOWN:
				snakeHead->MoveDown();
				collision_flag = CheckForCollision(apple);
				break;
			default:
				cout << "!Wrong orientation!" << endl;
				break;
		}
		
		if (snakeBody.size() > 0) {
			phReadX = snakeBody[0]->GetX();
			phReadY = snakeBody[0]->GetY();
			snakeBody[0]->SetX(phWriteX);
			snakeBody[0]->SetY(phWriteY);
			snakeBody[0]->UpdateDestinationRect(phWriteX, phWriteY);
			phWriteX = phReadX;
			phWriteY = phReadY;
		}
		for (int i = 1; i < snakeBody.size(); ++i) {
			phReadX = snakeBody[i]->GetX();
			phReadY = snakeBody[i]->GetY();
			snakeBody[i]->SetX(phWriteX);
			snakeBody[i]->SetY(phWriteY);
			snakeBody[i]->UpdateDestinationRect(phWriteX, phWriteY);
			phWriteX = phReadX;
			phWriteY = phReadY;
		}

		frameCounter = 0;
		blockKeys = false;
	}

	++frameCounter;

	return collision_flag;
}

void Snake::Render()
{
	snakeHead->Render();

	if (snakeBody.size() == 0) {
		return;
	}

	for (int i = 0; i < snakeBody.size(); i++) {
		snakeBody[i]->Render();
	}
}

void Snake::SetOrientation(ORIENTATION ori)
{
	orientation = ori;
}

GameObject* Snake::GetSnakeHead()
{
	return snakeHead;
}

vector<GameObject*> Snake::GetSnakeBody()
{
	return snakeBody;
}

void Snake::ExpandBody()
{
	int XsnakeHead = snakeHead->GetX();
	int YsnakeHead = snakeHead->GetY();

	snakeBody.push_back(new GameObject("resources/green.png", -20, -20));

	IncreaseSpeed();
}

void Snake::IncreaseSpeed()
{
	if (speed >= 50) {
		return;
	}
	speed += 5;
}

bool Snake::CheckBodyCollision()
{
	for (int i = 0; i < snakeBody.size(); i++) {
		if (snakeHead->GetX() == snakeBody[i]->GetX() &&
			snakeHead->GetY() == snakeBody[i]->GetY()) {
			return true;
		}
	}
	return false;
}