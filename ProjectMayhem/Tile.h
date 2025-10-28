#pragma once
#include <SDL3/SDL.h>
class Tile
{
	static bool CompareColours(SDL_Color& col1, SDL_Color& col2);

public:
	bool Walkable;
	SDL_Texture* Texture;
	SDL_FRect Rect;
	void Configure(SDL_Color& color, float x , float y, float size);
private:

};

