#pragma once
#include "Enums.h"
#include "Pickup.h"
#include <SDL3/SDL.h>
#include "MoveContext.h"

class GameCharacter
{
public:
	GameCharacter();
	~GameCharacter();
	void CollectPickup(Pickup& pickup);
	void Attack(GameCharacter& target);
	MoveContext TryMove(Tile* fromTile, Direction direction);

	SDL_Texture* Texture;
	SDL_FRect Rect;
private:


};

