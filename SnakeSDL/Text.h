#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>

using namespace std;

class Text
{
public:
	Text();
	Text(SDL_Renderer* renderer, const string &font_path, int font_size, const string &message_text, const SDL_Color &color);

	void Display(int x, int y, SDL_Renderer* renderer) const;

	static SDL_Texture* LoadFont(SDL_Renderer* renderer, const string& font_path, int font_size, const string& message_text, const SDL_Color& color);

private:
	SDL_Texture* textTexture = nullptr;
	mutable SDL_Rect textRectangle;
};

