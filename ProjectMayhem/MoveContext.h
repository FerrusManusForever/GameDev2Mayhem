#pragma once
#include "Tile.h"
#include "GameCharacter.h"
#include "Enums.h"

class MoveContext
{
public:
	Tile* Tile;
	GameCharacter* Character;
	MoveResult Result;
	Direction Direction;
};

