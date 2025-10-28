#include "DungeonGame.h"

DungeonGame::DungeonGame(float tileSizeX, float tileSizeY)
{
	this->tileSizeX = tileSizeX;
	this->tileSizeY = tileSizeY;
}

DungeonGame::~DungeonGame()
{
	delete Hero;
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

	// Load carpet textures
	for (int n = 0; n < 3; n++)
	{
		this->CarpetTextures[n] = IMG_LoadTexture(renderer, path_Carpet[n].c_str());
		SDL_SetTextureScaleMode(this->CarpetTextures[n], SDL_SCALEMODE_NEAREST);
	}
	// TODO more tileset textures here.

	

}

void DungeonGame::LoadRoom(char* filename)
{
	SDL_Surface* surface = SDL_LoadBMP(filename);
	//Uint8 r = 0u, g = 0u, b = 0u;
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
			this->Tiles[x][y].Configure(col, x, y, tileSizeX);

		}
	}

}
