#pragma once
#include "Tile.h"
#include "GameCharacter.h"
#include "Enums.h"

class MoveContext
{
public:
	Tile* Tile;
	GameCharacter* Blocker;
	MoveResult Result;
	Direction Direction;
};

