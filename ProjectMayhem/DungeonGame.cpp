#include "DungeonGame.h"

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
}

DungeonGame::~DungeonGame()
{
}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	// Load all textures
	this->texHero = IMG_LoadTexture(renderer, path_Hero.c_str());

	this->RectHero = { 0, 0, tileSizeX, tileSizeY };

}
