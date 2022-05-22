#include "GameObject.h"
#include "TextureManager.h"
#include "SDL.h"

GameObject::GameObject(const char* texturesheet, int x, int y)
{
	objectTexture = TextureManager::LoadTexture(texturesheet);
	xpos = x;
	ypos = y;

	sourceRectangle.h = 20;
	sourceRectangle.w = 20;
	sourceRectangle.x = 0;
	sourceRectangle.y = 0;

	destinationRectangle.x = xpos;
	destinationRectangle.y = ypos;
	destinationRectangle.w = sourceRectangle.w;
	destinationRectangle.h = sourceRectangle.h;
}

void GameObject::MoveLeft()
{
	xpos -= 20;

	destinationRectangle.x = xpos;
}

void GameObject::MoveUp()
{
	ypos -= 20;

	destinationRectangle.y = ypos;
}

void GameObject::MoveRight()
{
	xpos += 20;

	destinationRectangle.x = xpos;
}

void GameObject::MoveDown()
{
	ypos += 20;

	destinationRectangle.y = ypos;
}

void GameObject::Render()
{
	SDL_RenderCopy(Game::renderer, objectTexture, &sourceRectangle, &destinationRectangle);
}

int GameObject::GetX()
{
	return xpos;
}

int GameObject::GetY()
{
	return ypos;
}

void GameObject::SetX(int X)
{
	xpos = X;
}

void GameObject::SetY(int Y)
{
	ypos = Y;
}

void GameObject::UpdateDestinationRect(int X, int Y)
{
	destinationRectangle.x = X;
	destinationRectangle.y = Y;
}