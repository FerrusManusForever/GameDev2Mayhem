#include "Goblin.h"
#include "DungeonGame.h"
#include "Enums.h"
#include <random>
Goblin::Goblin(DungeonGame& game, SDL_Texture* texture, Tile* tile)
{
	this->GameRef = &game;
	this->Texture = texture;
	this->CurrentTile = tile;
	this->Rect = tile->Rect;

	tile->Resident = this;
}

void Goblin::DoAIMove()
{
	// pick a random direction
	int r = rand() % 3;
	Direction d = (Direction)r;

	MoveContext move;
	move.Result = MoveResult::Pending;
	move.MovingCharacter = this;
	move.Direction = d;
	move.Tile = this->CurrentTile;

	this->GameRef->AddPendingMove(move);

}

void Goblin::Update(double dt)
{
	GameCharacter::Update(dt);
	moveTimer += dt;
	if (moveTimer >= this->MoveInterval)
	{
		moveTimer = 0;
		DoAIMove();
	}
}
