#pragma once
#include "GameCharacter.h"

class Pathfinder;
class DungeonGame;

class Minotaur : public GameCharacter
{
public:
	
	Minotaur(DungeonGame* game);
	~Minotaur();

private:
	Pathfinder* pathfinder;
};

