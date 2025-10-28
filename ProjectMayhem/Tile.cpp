#include "Tile.h"

bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return col1.r == col2.r &&
		col1.b == col2.b &&
		col1.g == col2.g &&
		col1.a == col2.a;
}

void Tile::Configure(SDL_Color& color, float x, float y, float size)
{
	SDL_Color black = { 0, 0, 0, 255 };
	if (CompareColours(color, black))
	{
		Walkable = false;
	}
	else
	{
		Walkable = true;
	}

	this->Rect = { x * size, y * size, size, size };



}
