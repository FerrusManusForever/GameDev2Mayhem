#include "Tile.h"
#include <random>
#include <iostream>
#include "Enums.h"
bool Tile::CompareColours(SDL_Color& col1, SDL_Color& col2)
{
	return col1.r == col2.r &&
		col1.b == col2.b &&
		col1.g == col2.g ;
}

void Tile::Configure(SDL_Color& color, float x, float y, float size,
	SDL_Texture* tilesetA[],SDL_Texture* tilesetB[],SDL_Texture* tilesetC[])
{

	XCoord = (int)x;
	YCoord = (int)y;


	SDL_Color black = { 0, 0, 0, 255 };
	SDL_Color red = { 255, 0, 0, 255 };
	SDL_Color green = { 0, 255, 0, 255 };
	SDL_Color blue = { 0, 0, 255, 255 };


	if (CompareColours(color, black))
	{
		Walkable = false;
		this->Texture = nullptr;
	}
	else
	{
		Walkable = true;
		
		
		// Check if it's red, green or blue and choose the right tileset.

		if (CompareColours(color, red))	// carpet, tileset A, max 3
		{
			if (rand() % 10 == 1)
			{
				this->Texture = tilesetA[0];
			}
			else
			{
				int max = 3;
				int index = rand() % max;
				this->Texture = tilesetA[index];
			}			
			
		}
		else if (CompareColours(color, green))		// grey, tileset B, max 7
		{
			if (rand() % 10 == 1)
			{
				this->Texture = tilesetB[0];
			}
			else
			{
				int max = 7;
				int index = rand() % max;
				this->Texture = tilesetB[index];
			}			
		}
		else
		{
			if (rand() % 10 == 1)
			{
				this->Texture = tilesetC[0];
			}
			else
			{
				// checker, tileset C, max 4
				int max = 4;
				int index = rand() % max;
				this->Texture = tilesetC[index];
			}
			
		}

		
	}

	//this->Rect = { x * size, y * size, size, size };
	SDL_FRect rect;
	rect.x = x * size;
	rect.y = y * size;
	rect.w = size;
	rect.h = size;
	this->Rect = rect;


	

}

Tile* Tile::GetNeighbour(Direction dir)
{
	if (dir == Direction::North)
	{
		return NeighbourNorth;
	}
	if (dir == Direction::South)
	{
		return NeighbourSouth;
	}
	if (dir == Direction::East)
	{
		return NeighbourEast;
	}
	if (dir == Direction::West)
	{
		return NeighbourWest;
	}

	return nullptr;
}
