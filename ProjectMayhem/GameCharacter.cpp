#include "GameCharacter.h"
#include <cmath>
#include <algorithm>
#include "Tile.h"
#include <iostream>
GameCharacter::GameCharacter()
{
	lerpTimer = 0;
	LerpInterval = 0.15;
	
}
GameCharacter::~GameCharacter()
{

}

void GameCharacter::CollectPickup(Tile& tile)
{
	auto pickup = tile.Pickup;
	if (pickup != Pickup::None)
	{
		std::cout << "Collected " << pickup << std::endl;
		tile.Pickup = Pickup::None;
	}

}



void GameCharacter::Attack(GameCharacter& target)
{
}

void GameCharacter::UpdateVisual(double dt)
{
	lerpTimer = std::clamp(lerpTimer + dt, 0.0, LerpInterval);

	if (lerpTimer < LerpInterval)
	{
		float t = lerpTimer / LerpInterval;

		float x = std::lerp(lerpFromX, lerpToX, t);
		float y = std::lerp(lerpFromY, lerpToY, t);

		this->Rect.x = x;
		this->Rect.y = y;
	}
}

void GameCharacter::StartLerping(float x, float y)
{
	lerpFromX = this->Rect.x;
	lerpFromY = this->Rect.y;
	lerpToX = x;
	lerpToY = y;
	lerpTimer = 0;
}

void GameCharacter::SetRect(SDL_FRect& rect)
{
	this->Rect = rect;
	this->lerpFromX = rect.x;
	this->lerpFromY = rect.y;
	this->lerpToX = rect.x;
	this->lerpToY = rect.y;
	lerpTimer = LerpInterval;
}

void GameCharacter::Update(double dt)
{
	UpdateVisual(dt);
}




