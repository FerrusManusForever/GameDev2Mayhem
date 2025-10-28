#pragma once
#include "Enums.h"
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
const static std::string path_Hero = "Sprites/Hero_Sword.png";
const static std::string path_Carpet[] = {
										"Sprites/Tile_carpet_base.bmp" ,
										"Sprites/Tile_carpet_blood_1.bmp",
										"Tile_carpet_bones.bmp" 
										};

const static int RoomSize = 10;

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(const char* file);
	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];
	SDL_Texture* CarpetTextures[3];

private:
	float tileSizeX;
	float tileSizeY;

};

