#pragma once
#include "Pickup.h"
#include <SDL3/SDL.h>
class GameCharacter
{
public:
	GameCharacter();
	~GameCharacter();
	void CollectPickup(Pickup& pickup);
	void Attack(GameCharacter& target);

	SDL_Texture* Texture;
	SDL_FRect Rect;
private:


};

