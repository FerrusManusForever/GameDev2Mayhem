#pragma once
#include <SDL3/SDL.h>
#include "Enums.h"
#include <list>

class GameCharacter;

class Tile
{
	static bool CompareColours(SDL_Color& col1, SDL_Color& col2);

public:
	Tile();
	int XCoord, YCoord;
	bool Walkable;
	SDL_Texture* Texture;
	SDL_FRect Rect;
	void Configure(SDL_Color& color, float x , float y, float size, SDL_Texture* tilesetA[], SDL_Texture* tilesetB[], SDL_Texture* tilesetC[]);
	Tile* NeighbourNorth;
	Tile* NeighbourSouth;
	Tile* NeighbourEast;
	Tile* NeighbourWest;
	Tile* GetNeighbour(Direction dir);
	GameCharacter* Resident;
	static int GetDistance(Tile& t1, Tile& t2);
	Pickup Pickup;
	std::list<Tile*> GetAllNeighbours();
	void StoreNeighbours();

	// Pathfinding vars
	float G;
	float H;

private:	
	std::list<Tile*> AllNeighbours;


};

