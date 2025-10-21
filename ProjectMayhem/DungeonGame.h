#pragma once
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"

const static std::string path_Hero = "Sprites/Hero_Sword.png";

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	SDL_FRect RectHero;
	SDL_Texture* texHero;
private:
	
	float tileSizeX;
	float tileSizeY;

};

