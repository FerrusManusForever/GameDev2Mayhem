#pragma once
#include "Enums.h"
#include <SDL3/SDL.h>

class Tile;
class DungeonGame;

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
	SDL_Texture* UnarmedTexture;
	SDL_FRect Rect;
	double lerpTimer;
	double LerpInterval;
	void Update(double dt);
private:
	float lerpFromX;
	float lerpFromY;
	float lerpToX;
	float lerpToY;

};

