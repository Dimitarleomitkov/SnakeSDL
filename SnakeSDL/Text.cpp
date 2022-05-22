#include "Text.h"
#include <iostream>
#include "Game.h"
#include "TextureManager.h"

Text::Text(SDL_Renderer* renderer, const string& font_path, int font_size, const string& message_text, const SDL_Color& color)
{
	textTexture = LoadFont(renderer, font_path, font_size, message_text, color);
	SDL_QueryTexture(textTexture, nullptr, nullptr, &textRectangle.w, &textRectangle.h);
}

void Text::Display(int x, int y, SDL_Renderer* renderer) const
{
	textRectangle.x = x;
	textRectangle.y = y;
	SDL_RenderCopy(renderer, textTexture, nullptr, &textRectangle);
	SDL_DestroyTexture(textTexture);
}

SDL_Texture* Text::LoadFont(SDL_Renderer* renderer, const string& font_path, int font_size, const string& message_text, const SDL_Color& color)
{
	TTF_Font* font = TTF_OpenFont(font_path.c_str(), font_size);
	SDL_Surface* text_surface = TTF_RenderText_Solid(font, message_text.c_str(), color);
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);


	TTF_CloseFont(font);
	SDL_FreeSurface(text_surface);
	return text_texture;
}