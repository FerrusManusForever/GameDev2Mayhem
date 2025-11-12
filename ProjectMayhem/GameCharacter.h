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
	void UpdateVisual(double dt); // lerps towards its destination
	void StartLerping(float x, float y);
	void SetRect(SDL_FRect& rect);
	Tile* CurrentTile;
	SDL_Texture* Texture;
	SDL_FRect Rect;
	double lerpTimer;
	double LerpInterval = 0.2f;
private:
	float lerpFromX;
	float lerpFromY;
	float lerpToX;
	float lerpToY;

};

