#include "SDL.h"
#include "Game.h"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>
#include <Windows.h>

using namespace std;

Game* game = nullptr;
extern bool exitFlag = 1;

int main(int argc, char* argv[])
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);

    const int FPS = 60;
    const int frameDelay = 1000 / FPS;
    Uint32 frameStart;
    int frameTime;
    bool menuSelectFlag = true;

    game = new Game();

    while (exitFlag) {
        menuSelectFlag = true;
        game->init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 900, 600);
        chrono::steady_clock::time_point begin = chrono::steady_clock::now();
        while (game->Running()) {
            frameStart = SDL_GetTicks();
            game->HandleEvents();
            game->Update();
            game->Render();
    
            frameTime = SDL_GetTicks() - frameStart;

            if (frameDelay > frameTime) {
                SDL_Delay(frameDelay - frameTime);
            }
            chrono::steady_clock::time_point end = chrono::steady_clock::now();
            if (chrono::duration_cast<chrono::seconds>(end - begin).count() == 1) {
                game->IncrementTime();
                begin = chrono::steady_clock::now();
            }
        }
        game->Clean();
        game->EndWindow();
        while (menuSelectFlag) {
            menuSelectFlag = game->HandleEndWindowEvents();
            game->EndWindowRender();
        }
        game->Clean();
    }

    return 0;
}