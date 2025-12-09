#include "Minotaur.h"
#include "DungeonGame.h"
#include "Pathfinder.h"


Minotaur::Minotaur(DungeonGame* game)
{
	this->pathfinder = new Pathfinder(game);
}

Minotaur::~Minotaur()
{
	delete this->pathfinder;
}
