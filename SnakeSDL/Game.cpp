#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Apple.h"
#include "Snake.h"
#include "SDL_ttf.h"
 
SDL_Event event;
extern bool exitFlag;
bool blockKeys;

Snake* P1_Snake;
Map* map;
Apple* apple;

using namespace std;

SDL_Renderer* Game::renderer = nullptr;

Game::Game()
{
	time = 0;
	score = 0;
	pressedKey = UP;
}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height)
{
	int flags = 0;

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		//cout << "Subsystems Initialized!..." << endl;
	
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		/*if (window) {
			cout << "Window created!" << endl;
		}*/

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			//cout << "Renderer created!" << endl;
		}

		isRunning = true;
	} else {
		isRunning = false;
	}

	if (TTF_Init() == -1) {
		cerr << "Failed to initalize TTF" << endl;
		isRunning = false;
	}

	P1_Snake = new Snake();
	map = new Map();
	apple = new Apple(P1_Snake->GetSnakeHead()->GetX(), P1_Snake->GetSnakeHead()->GetY());
	scoreText = new Text(renderer, "resources/arial.ttf", 20, "Score:0", { 30, 30, 30, 255 });
	timeText = new Text(renderer, "resources/arial.ttf", 20, "0:0", { 30, 30, 30, 255 });
	time = 0;
	score = 0;
	pressedKey = UP;
}

void Game::HandleEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			isRunning = false;
			break;
		case SDL_KEYDOWN:
			if (blockKeys) {
				break;
			}
			switch (event.key.keysym.sym) {
				case SDLK_LEFT:
					blockKeys = true;
					if (pressedKey != RIGHT) {
						pressedKey = LEFT;
					}
					break;
				case SDLK_UP:
					blockKeys = true;
					if (pressedKey != DOWN) {
						pressedKey = UP;
					}
					break;
				case SDLK_RIGHT:
					blockKeys = true;
					if (pressedKey != LEFT) {
						pressedKey = RIGHT;
					}
					break;
				case SDLK_DOWN:
					blockKeys = true;
					if (pressedKey != UP) {
						pressedKey = DOWN;
					}
					break;
				case SDLK_a:
					blockKeys = true;
					if (pressedKey != RIGHT) {
						pressedKey = LEFT;
					}
					break;
				case SDLK_w:
					blockKeys = true;
					if (pressedKey != DOWN) {
						pressedKey = UP;
					}
					break;
				case SDLK_d:
					blockKeys = true;
					if (pressedKey != LEFT) {
						pressedKey = RIGHT;
					}
					break;
				case SDLK_s:
					blockKeys = true;
					if (pressedKey != UP) {
						pressedKey = DOWN;
					}
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void Game::Update()
{
	int collision_flag = 0;

	P1_Snake->SetOrientation(pressedKey);
	
	collision_flag = P1_Snake->Move(apple->AsObject());

	if (collision_flag == 1) {
		isRunning = false;
	}
	else if (collision_flag == 2) {
		apple->Move(map->ReturnAvailableSpace(P1_Snake, apple->AsObject()));
		P1_Snake->ExpandBody();
		IncrementScore();
	}
}

void Game::Render()
{
	SDL_RenderClear(renderer);
	// This is where we would add stuff to render
	map->DrawMap();
	P1_Snake->Render();
	apple->Render();
	SetScoreText();
	scoreText->Display(800, 100, renderer);
	SetTimeText();
	timeText->Display(800, 200, renderer);
	// To here
	SDL_RenderPresent(renderer);
}

void Game::Clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	TTF_Quit();
}

bool Game::Running()
{
	return isRunning;
}

void Game::SetScoreText()
{
	ostringstream oss;
	oss << "Score:" << score;
	scoreText = new Text(renderer, "resources/arial.ttf", 20, oss.str(), { 30, 30, 30, 255 });
}

void Game::SetTimeText()
{
	ostringstream oss;
	oss << time / 60 << ":" << time % 60;
	timeText = new Text(renderer, "resources/arial.ttf", 20, oss.str(), { 30, 30, 30, 255 });
}

void Game::IncrementTime()
{
	time++;
}

void Game::IncrementScore()
{
	score++;
}

void Game::EndWindow()
{
	window = SDL_CreateWindow("Menu",
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		200, 100,
		0);;
	renderer = SDL_CreateRenderer(window, -1, 0);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	if (TTF_Init() == -1) {
		cerr << "Failed to initalize TTF" << endl;
		isRunning = false;
	}
}

void Game::EndWindowRender()
{
	SDL_RenderClear(renderer);
	// This is where we would add stuff to render
	SetScoreText();
	scoreText->Display(60, 0, renderer);
	SetTimeText();
	timeText->Display(80, 20, renderer);

	scoreText = new Text(renderer, "resources/arial.ttf", 20, "Press \"Q\" to Quit", {30, 30, 30, 255});
	scoreText->Display(10, 50, renderer);
	scoreText = new Text(renderer, "resources/arial.ttf", 20, "Press \"R\" to Restart", { 30, 30, 30, 255 });
	scoreText->Display(10, 70, renderer);

	// To here
	SDL_RenderPresent(renderer);
}

bool Game::HandleEndWindowEvents()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type) {
		case SDL_QUIT:
			exitFlag = false;
			return false;
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym) {
				case SDLK_q:
					exitFlag = false;
					return false;
				case SDLK_r:
					return false;
				default:
					break;
				}
			break;
		default:
			break;
	}

	return true;
}