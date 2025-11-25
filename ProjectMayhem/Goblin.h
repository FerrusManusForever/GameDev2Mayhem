#pragma once
#include "GameCharacter.h"

class DungeonGame;

class Goblin : public GameCharacter
{
public:
	Goblin(DungeonGame& game, SDL_Texture* texture, Tile* tile);
	DungeonGame* GameRef;
	double MoveInterval = 2.0;
	void DoAIMove();
	virtual void Update(double dt);
private:
	double moveTimer = 0;



};

