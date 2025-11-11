#pragma once
#include "Enums.h"
#include "Pickup.h"
#include <SDL3/SDL.h>

class Tile;

class GameCharacter
{
public:
	GameCharacter();
	~GameCharacter();
	void CollectPickup(Pickup& pickup);
	void Attack(GameCharacter& target);

	Tile* CurrentTile;
	SDL_Texture* Texture;
	SDL_FRect Rect;
private:


};

