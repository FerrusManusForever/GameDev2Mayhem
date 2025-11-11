#include "DungeonGame.h"
#include <random>

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
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
	if (dir == South && y < RoomSize - 2)
	{
		return &this->Tiles[x][y + 1];
	}
	if (dir == East && x < RoomSize - 2)
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
			RoomLayouts[x][y] = rand() % 5;
		}
	}
}

void DungeonGame::LoadTextures(SDL_Renderer* renderer)
{
	this->Hero = new Player;

	// Load all textures
	this->Hero->Texture = IMG_LoadTexture(renderer, path_Hero.c_str());
	SDL_SetTextureScaleMode(this->Hero->Texture, SDL_SCALEMODE_NEAREST);

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
				result.Character = neighbour->Resident;
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
	

	return result;
}

// Shifts a character a tile.
void DungeonGame::Place(GameCharacter& who, Tile& tile)
{
	tile.Resident = nullptr;
	who.CurrentTile = &tile;
	who.Rect = tile.Rect;
	tile.Resident = &who;
}


void DungeonGame::LoadRoom(int x, int y)
{
	int roomIndex = RoomLayouts[x][y];
	std::string path = roomFiles[roomIndex];
	LoadRoom(path);
}



