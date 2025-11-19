#pragma once
#include <map>
#include "Enums.h"
#include <string>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include "GameCharacter.h"
#include "Player.h"
#include "Tile.h"
#include "MoveContext.h"
#include <vector>
#include <list>
#include "Goblin.h"
const static std::string path_Hero = "Sprites/Hero_Sword.png";
const static std::string path_Hero_Unarmed = "Sprites/Hero_no_Sword.png";

const static std::string path_Goblins[] = { 
											"Sprites/Enemy_orc_purple.png",
											"Sprites/Enemy_orc_blue.png",
											"Sprites/Enemy_orc_red.png",
											"Sprites/Enemy_orc_orange.png"

};

const static std::string path_Pickups[] = {
										"Sprites/Pickup_Health.png",
										"Sprites/Pickup_Sword.png"										
};


const static std::string path_Carpet[] = {
										"Sprites/Tile_carpet_base.bmp" ,
										"Sprites/Tile_carpet_blood_1.bmp",
										"Sprites/Tile_carpet_bones.bmp" 
										};

const static std::string path_Grey[] = {
										"Sprites/Tile_Grey_base.bmp" ,
										"Sprites/Tile_Grey_blood_1.bmp",
										"Sprites/Tile_Grey_bones.bmp",
										"Sprites/Tile_Grey_crack_1.bmp",
										"Sprites/Tile_Grey_crack_2.bmp",
										"Sprites/Tile_Grey_crack_3.bmp",
										"Sprites/Tile_Grey_crack_4.bmp"

};

const static std::string path_Check[] = {
										"Sprites/Tile_checker_base.bmp" ,
										"Sprites/Tile_checker_blood.bmp",
										"Sprites/Tile_checker_bones_1.bmp",
										"Sprites/Tile_checker_crack_1.bmp"

};

const static std::string roomFiles[7] = {
										"Data/Rooms/Room01.bmp",
										"Data/Rooms/Room02.bmp",
										"Data/Rooms/Room03.bmp",
										"Data/Rooms/Room04.bmp",
										"Data/Rooms/Room05.bmp",
										"Data/Rooms/Room06.bmp",
										"Data/Rooms/Room07.bmp"	
};

const static int RoomSize = 10;
const static int NumRooms = 10;

class DungeonGame
{
public:
	DungeonGame(float tileSizeX, float tileSizeY);
	~DungeonGame();	
	void LoadTextures(SDL_Renderer* renderer);
	void LoadRoom(int x, int y);
	void UnloadRoom();
	Player* Hero;
	Tile Tiles[RoomSize][RoomSize];
	int RoomLayouts[NumRooms][NumRooms];
	SDL_Texture* CarpetTextures[3];
	SDL_Texture* GreyTextures[7];
	SDL_Texture* CheckTextures[4];
	SDL_Texture* GoblinTextures[4];
	std::map<Pickup, SDL_Texture*> PickupTextures;
	std::list<Goblin*> Goblins;


	Tile* GetNeighbour(Tile* origin, Direction dir);
	void LinkTiles();
	MoveContext TryMove(GameCharacter* whoMove, Tile* tile, Direction dir);
	void Place(GameCharacter& who, Tile& tile, bool immediate);
	void MoveRoom(Direction dir);

private:
	float tileSizeX;
	float tileSizeY;
	void RandomizeLayout();
	void LoadRoom(std::string file);	
	int currentRoomX;
	int currentRoomY;
	void SpawnGoblins();
	void SpawnPickups();
	void ClearGoblins();
	void ClearPickups();
	std::vector<Tile*> GetEmptyTiles();

};

