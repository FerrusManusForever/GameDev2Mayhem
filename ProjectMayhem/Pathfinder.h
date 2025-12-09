#pragma once
#include <vector>
#include <list>
#include "Tile.h"

class DungeonGame;

class Pathfinder
{
public:
	Pathfinder(DungeonGame* game);
	std::vector<Tile*> FindPath(Tile* start, Tile* destination);
	DungeonGame* Game;
	float Heuristic(Tile* current, Tile* destination);
	float Traversal(Tile* current, Tile* neighbour);
private:
	std::vector<Tile*> Backtrack(Tile* node);
	std::list<Tile*> Open;
	std::list<Tile*> Closed;
	void AssignCosts(Tile* currentNode, Tile* candidate, Tile* destination);
	Tile* GetLowestScored(std::list<Tile*> candidates);
};

