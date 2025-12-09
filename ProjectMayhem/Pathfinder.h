#pragma once
#include <vector>
#include "Tile.h"

class DungeonGame;

class Pathfinder
{
public:
	std::vector<Tile*> FindPath(Tile* from, Tile* to);
	DungeonGame* Game;
private:
	std::vector<Tile*> Backtrack(Tile* node);
};

