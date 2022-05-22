#pragma once
#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <iostream>
#include "Text.h"
#include <sstream>


enum ORIENTATION {
	LEFT,
	UP,
	RIGHT,
	DOWN
};

class Game
{
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height);
	
	void HandleEvents();
	bool HandleEndWindowEvents();
	void Update();
	bool Running();
	void Render();
	void Clean();

	void EndWindow();
	void EndWindowRender();

	void SetScoreText();
	void SetTimeText();

	void IncrementTime();
	void IncrementScore();

	static SDL_Renderer* renderer;

private:
	bool isRunning;
	SDL_Window* window;
	ORIENTATION pressedKey;
	int time;
	int score;
	Text* scoreText;
	Text* timeText;
};

