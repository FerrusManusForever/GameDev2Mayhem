#include "Pathfinder.h"
#include "DungeonGame.h"
#include <math.h>

Pathfinder::Pathfinder(DungeonGame* game)
{
    this->Game = game;
}

std::vector<Tile*> Pathfinder::FindPath(Tile* start, Tile* destination)
{   
    Open.clear();
    Closed.clear();


    return std::vector<Tile*>();
}

float Pathfinder::Heuristic(Tile* current, Tile* destination)
{    
    return std::abs(current->XCoord - destination->XCoord) + std::abs(current->YCoord - destination->YCoord);    
}

float Pathfinder::Traversal(Tile* current, Tile* neighbour)
{
    return 1.0f;
}

std::vector<Tile*> Pathfinder::Backtrack(Tile* node)
{
    return std::vector<Tile*>();
}

void Pathfinder::AssignCosts(Tile* currentNode, Tile* candidate, Tile* destination)
{
    float g = Traversal(currentNode, candidate);
    float h = Heuristic(currentNode, destination);
    candidate->G = g;
    candidate->H = h;
}

Tile* Pathfinder::GetLowestScored(std::list<Tile*> candidates)
{

    return nullptr;
}
