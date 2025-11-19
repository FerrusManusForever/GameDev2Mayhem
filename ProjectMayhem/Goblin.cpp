#include "Goblin.h"
#include "DungeonGame.h"
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

}
