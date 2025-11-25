#include "DungeonGame.h"
#include <random>
#include <vector>
#include <iostream>

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
	this->currentRoomX = 0;
	this->currentRoomY = 0;

	RandomizeLayout();
}

DungeonGame::~DungeonGame()
{
	delete Hero;
}

Tile* DungeonGame::GetNeighbour(Tile* origin, Direction dir)
{
	int x = origin->XCoord;
	int y = origin->YCoord;

	if (dir == North && y > 0)
	{
		return &this->Tiles[x][y - 1];
	}
	if (dir == South && y < RoomSize - 1)
	{
		return &this->Tiles[x][y + 1];
	}
	if (dir == East && x < RoomSize - 1)
	{
		return &this->Tiles[x + 1][y];
	}
	if (dir == West && x > 0)
	{
		return &this->Tiles[x - 1][y];
	}

	return nullptr;
}

void DungeonGame::RandomizeLayout()
{
	for (int x = 0; x < NumRooms; x++)
	{
		for (int y = 0; y < NumRooms; y++)
		{
			RoomLayouts[x][y] = rand() % 7;
		}
	}
	RoomLayouts[0][0] = 0;
}

std::vector<Tile*> DungeonGame::GetEmptyTiles()
{
	std::vector<Tile*> result;
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			if (Tiles[x][y].Walkable && Tiles[x][y].Resident == nullptr)
			{
				result.push_back(&Tiles[x][y]);
			}
		}
	}

	return result;
}



void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;

	// Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);
	this->Hero->UnarmedTexture = IMG_LoadTexture(renderer, path_Hero_Unarmed.c_str());
	SDL_SetTextureScaleMode(this->Hero->UnarmedTexture, SDL_SCALEMODE_NEAREST);

	this->Hero->Rect.x = 0;
	this->Hero->Rect.y = 0;
	this->Hero->Rect.w = tileSizeX;
	this->Hero->Rect.h = tileSizeY;

	// Load carpet textures		// TODO probably want a better system to handle these.
	for (int n = 0; n < 3; n++)
	{
		this->CarpetTextures[n] = IMG_LoadTexture(renderer, path_Carpet[n].c_str());
		SDL_SetTextureScaleMode(this->CarpetTextures[n], SDL_SCALEMODE_NEAREST);
	}

	// Load grey tile textures
	for (int n = 0; n < 7; n++)
	{
		this->GreyTextures[n] = IMG_LoadTexture(renderer, path_Grey[n].c_str());
		SDL_SetTextureScaleMode(this->GreyTextures[n], SDL_SCALEMODE_NEAREST);
	}

	// Load check textures
	for (int n = 0; n < 4; n++)
	{
		this->CheckTextures[n] = IMG_LoadTexture(renderer, path_Check[n].c_str());
		SDL_SetTextureScaleMode(this->CheckTextures[n], SDL_SCALEMODE_NEAREST);
	}

	// Load pickup textures
	this->PickupTextures.clear();
	this->PickupTextures[Pickup::Potion] = IMG_LoadTexture(renderer, path_Pickups[0].c_str());
	SDL_SetTextureScaleMode(this->PickupTextures[Pickup::Potion], SDL_SCALEMODE_NEAREST);
	this->PickupTextures[Pickup::Sword] = IMG_LoadTexture(renderer, path_Pickups[1].c_str());
	SDL_SetTextureScaleMode(this->PickupTextures[Pickup::Sword], SDL_SCALEMODE_NEAREST);


	// Load Goblin textures
	for (int n = 0; n < 4; n++)
	{
		this->GoblinTextures[n] = IMG_LoadTexture(renderer, path_Goblins[n].c_str());
		SDL_SetTextureScaleMode(this->GoblinTextures[n], SDL_SCALEMODE_NEAREST);
	}	

}

void DungeonGame::LoadRoom(std::string fileName)
{

	SDL_Surface* surface = SDL_LoadBMP(fileName.c_str());

	const SDL_PixelFormatDetails* pixelDetails = SDL_GetPixelFormatDetails(surface->format);
	const Uint8 bpp = SDL_BYTESPERPIXEL(surface->format);
	SDL_Color col;
	for (int y = 0; y < surface->h; y++)
	{
		for (int x = 0; x < surface->w; x++)
		{
			Uint8* pixel = static_cast<Uint8*>(surface->pixels) + y * surface->pitch + x * bpp;
			SDL_GetRGB(*reinterpret_cast<Uint32*>(pixel), pixelDetails, NULL, &col.r, &col.g,
				&col.b);

			// now configure the tile at x,y with col
			this->Tiles[x][y].Configure(col, x, y, tileSizeX, this->CarpetTextures, this->GreyTextures, this->CheckTextures);
		}
	}

	ClearPickups();
	ClearGoblins();
	SpawnPickups();
	SpawnGoblins();
}

void DungeonGame::SpawnGoblins()
{
	int numGoblins = rand() % 4;
	auto availableTiles = GetEmptyTiles();

	for (int n = 0; n < numGoblins; n++)
	{
		int max = availableTiles.size();
		int index = rand() % max;
		auto tile = availableTiles[index];

		int texmax = 4;
		auto texture = GoblinTextures[rand() % texmax];
		

		Goblin* g = new Goblin(*this, texture, tile);
		Goblins.push_back(g);
		availableTiles.erase(availableTiles.begin() + index);
	}


}

void DungeonGame::SpawnPickups()
{	
	int min = 2;
	int max = 5;
	int numPickups = rand() % (max - min + 1) + min;

	auto availableTiles = GetEmptyTiles();	
	
	for (int n = 0; n < numPickups; n++)
	{
		int randomIndex = rand() % availableTiles.size();

		if (rand() % 10 <= 2)
		{
			availableTiles[randomIndex]->Pickup = Pickup::Sword;
		}
		else
		{
			availableTiles[randomIndex]->Pickup = Pickup::Potion;
		}
		availableTiles.erase(availableTiles.begin() + randomIndex);
	}
}

void DungeonGame::ClearGoblins()
{
	for (int y = 0; y < RoomSize; y++)
	{
		for (int x = 0; x < RoomSize; x++)
		{
			this->Tiles[x][y].Resident = nullptr;
		}
	}


	for (auto itr = Goblins.begin(); itr != Goblins.end();)
	{
		
		delete *itr;
		itr = Goblins.erase(itr);		
	}
		

}

void DungeonGame::ClearPickups()
{
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			this->Tiles[x][y].Pickup = Pickup::None;
		}
	}
}



void DungeonGame::LinkTiles()
{
	for (int x = 0; x < RoomSize; x++)
	{
		for (int y = 0; y < RoomSize; y++)
		{
			this->Tiles[x][y].NeighbourNorth = GetNeighbour(&Tiles[x][y], Direction::North);
			this->Tiles[x][y].NeighbourSouth = GetNeighbour(&Tiles[x][y], Direction::South);
			this->Tiles[x][y].NeighbourEast = GetNeighbour(&Tiles[x][y], Direction::East);
			this->Tiles[x][y].NeighbourWest = GetNeighbour(&Tiles[x][y], Direction::West);
		}
	}
}

MoveContext DungeonGame::TryMove(GameCharacter* whoMove, Tile* tile, Direction dir)
{
	MoveContext result;
	result.Direction = dir;
	result.MovingCharacter = whoMove;


	Tile* neighbour = tile->GetNeighbour(dir);
	if (neighbour != nullptr)
	{
		result.Tile = neighbour;

		// there is a tile in that direction
		if (neighbour->Walkable == false)
		{
			result.Result = MoveResult::Blocked;
		}
		else
		{
			// walkable tile, check for a resident character
			if (neighbour->Resident != nullptr)
			{
				result.Result = MoveResult::Combat;
				result.BlockingCharacter = neighbour->Resident;
			}
			else
			{
				// No resident, OK to move to the tile
				result.Result = MoveResult::OK;
			}
		}
	}
	else
	{
		// no neighbour in that direction, try to load a new room
		result.Result = MoveResult::NewRoom;
	}	
	std::cout << result.Result << std::endl;
	return result;
}

// Shifts a character a tile.
void DungeonGame::Place(GameCharacter& who, Tile& tile, bool immediate)
{
	if (who.CurrentTile != nullptr) {
		who.CurrentTile->Resident = nullptr;
	}
	
	tile.Resident = &who;
	if (immediate)
	{
		who.SetRect(tile.Rect);		
	}
	else
	{
		who.StartLerping(tile.Rect.x, tile.Rect.y);
	}
	
	who.CurrentTile = &tile;

	if (tile.Pickup != Pickup::None)
	{
		who.CollectPickup(tile);
	}	

}

void DungeonGame::MoveRoom(Direction dir)
{
	bool doChange = false;
	int tileX = this->Hero->CurrentTile->XCoord;
	int tileY = this->Hero->CurrentTile->YCoord;

	if (dir == Direction::North && currentRoomY > 0) {
		currentRoomY--;
		doChange = true;
		tileY = RoomSize - 1;
	}
	else if (dir == Direction::South && currentRoomY < NumRooms - 1) 
	{
		currentRoomY++;
		doChange = true;
		tileY = 0;
	}
	else if (dir == Direction::East && currentRoomX < NumRooms - 1) 
	{
		currentRoomX++;
		doChange = true;
		tileX = 0;
	}
	else if (dir == Direction::West && currentRoomX > 0) 
	{
		currentRoomX--;
		doChange = true;
		tileX = RoomSize - 1;
	}

	if (doChange) {
		UnloadRoom();
		LoadRoom(currentRoomX, currentRoomY);

		// Reset the player's position
		this->Place(*this->Hero, this->Tiles[tileX][tileY], true);
	}
}

void DungeonGame::AddPendingMove(MoveContext move)
{
	this->pendingMoves.push_back(move);

}

void DungeonGame::DoPendingMoves()
{
	for (auto pendingMove : pendingMoves)
	{
		auto moveResult = TryMove(pendingMove.MovingCharacter, pendingMove.Tile, pendingMove.Direction);
		if (moveResult.Result == MoveResult::OK)
		{
			Place(*moveResult.MovingCharacter, *moveResult.Tile, false);
		}
	}
	pendingMoves.clear();

}

void DungeonGame::Combat(GameCharacter& attacker, GameCharacter& defender)
{
	std::cout << "Phwoar, combat!" << std::endl;

}


void DungeonGame::LoadRoom(int x, int y)
{
	int roomIndex = RoomLayouts[x][y];
	std::string path = roomFiles[roomIndex];
	LoadRoom(path);
}

void DungeonGame::UnloadRoom()
{

}



