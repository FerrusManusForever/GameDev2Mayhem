
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "DungeonGame.h"
#include "MoveContext.h"
#include <cmath>
#include <algorithm>
using namespace std;

#define USE_LIGHTING 0;
#define USE_WOBBLE 0;

const int resX = 1920;
const int resY = 1080;
const int GridSizeX = 10;
const int GridSizeY = 10;
const float tileSize = resY / GridSizeX;


/* We will use this renderer to draw into this window every frame. */
static SDL_Window* window = NULL;
static SDL_Renderer* renderer = NULL;


static const char* ProjectName = "JMC Starter Project";

static DungeonGame* Game;
static const SDL_Color lightStart = { 255, 226.0, 148.0, 255 };
static const SDL_Color lightEnd = { 16.0, 1.00, 89.0, 255 };

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void** appstate, int argc, char* argv[])
{     

    SDL_SetAppMetadata(ProjectName, "1.0", "");

    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(ProjectName, resX, resY, 0, &window, &renderer))
    {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    Game = new DungeonGame(tileSize, tileSize);
    Game->LoadTextures(renderer);
    
    //const char* room = "Data/Rooms/Room01.bmp";
    //Game->LoadRoom(room);
    Game->LoadRoom(0, 0);
    Game->LinkTiles();
    Game->Place(*Game->Hero, Game->Tiles[1][1], true);
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void* appstate, SDL_Event* event)
{
    if (event->type == SDL_EVENT_QUIT)
    {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }

    if (event->type == SDL_EVENT_KEY_DOWN)
    {

        // keyboard events    
        if (event->key.scancode == SDL_SCANCODE_W)
        {
            //Game->Hero->Rect.y -= tileSize;
            MoveContext move = Game->TryMove(Game->Hero, Game->Hero->CurrentTile, Direction::North);
            if (move.Result == MoveResult::OK)
            {
                Game->Place(*Game->Hero, *move.Tile, false);
            }
            else if (move.Result == MoveResult::NewRoom) {
                Game->MoveRoom(Direction::North);
            }
        }
        if (event->key.scancode == SDL_SCANCODE_S)
        {
            //Game->Hero->Rect.y += tileSize;
            MoveContext move = Game->TryMove(Game->Hero, Game->Hero->CurrentTile, Direction::South);
            if (move.Result == MoveResult::OK)
            {
                Game->Place(*Game->Hero, *move.Tile, false);
            }
            else if (move.Result == MoveResult::NewRoom) {
                Game->MoveRoom(Direction::South);
            }

        }
        if (event->key.scancode == SDL_SCANCODE_A)
        {
            //Game->Hero->Rect.x -= tileSize;
            MoveContext move = Game->TryMove(Game->Hero, Game->Hero->CurrentTile, Direction::West);
            if (move.Result == MoveResult::OK)
            {
                Game->Place(*Game->Hero, *move.Tile, false);
            }
            else if (move.Result == MoveResult::NewRoom) {
                Game->MoveRoom(Direction::West);
            }
        }
        if (event->key.scancode == SDL_SCANCODE_D)
        {
            //Game->Hero->Rect.x += tileSize;
            MoveContext move = Game->TryMove(Game->Hero, Game->Hero->CurrentTile, Direction::East);
            if (move.Result == MoveResult::OK)
            {
                Game->Place(*Game->Hero, *move.Tile, false);
            }
            else if (move.Result == MoveResult::NewRoom) {
                Game->MoveRoom(Direction::East);
            }
        }
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */

}

float RandomFloat(float min, float max)
{
    float random = ((float)rand()) / (float)RAND_MAX;
    float range = max - min;
    return (random * range) + min;
}


/*  This function runs once per frame, and is the heart of the program.
    Think of this like Unity's Update() loop */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    

    // draw the grid
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (Game->Tiles[x][y].Walkable)
            {
#if USE_WOBBLE == 1
                float min = -0.1;
                float max = 0.1;

                Game->Tiles[x][y].Rect.w += RandomFloat(-0.1, 0.1);
                Game->Tiles[x][y].Rect.h += RandomFloat(-0.1, 0.1);
                Game->Tiles[x][y].Rect.x += RandomFloat(-0.1, 0.1);
                Game->Tiles[x][y].Rect.y += RandomFloat(-0.1, 0.1);

#endif // USE_WOBBLE

#if USE_LIGHTING == 1
                int dist = Tile::GetDistance(*Game->Hero->CurrentTile, Game->Tiles[x][y]);
                int maxDist = 7;
                float d = std::clamp(dist / (float)maxDist, 0.0f, 1.0f);
                float factor = 1.0f - d;
                factor *= factor;
                int brightness = static_cast<int>(255 * factor);


                // linearize colour
                float lR1 = std::powf(lightStart.r / 255.0, 2.2);
                float lB1 = std::powf(lightStart.b / 255.0, 2.2);
                float lG1 = std::powf(lightStart.g / 255.0, 2.2);
                float lR2 = std::powf(lightEnd.r / 255.0, 2.2);
                float lB2 = std::powf(lightEnd.b / 255.0, 2.2);
                float lG2 = std::powf(lightEnd.g / 255.0, 2.2);


                // lerp colour       
                float t = std::clamp(1.0 - (brightness / 255.0), 0.0, 1.0);
                float r = std::lerp(lR1, lR2, t);
                float g = std::lerp(lG1, lG2, t);
                float b = std::lerp(lB1, lB2, t);

                // convert back to rgb
                float rR = std::powf(r, 1.0 / 2.2) * 255.0;
                float rG = std::powf(g, 1.0 / 2.2) * 255.0;
                float rB = std::powf(b, 1.0 / 2.2) * 255.0;

                SDL_SetTextureColorMod(Game->Tiles[x][y].Texture, rR, rG, rB);
#endif


               
                
                
                
                
                
                

                SDL_RenderTexture(renderer, Game->Tiles[x][y].Texture, NULL, &Game->Tiles[x][y].Rect);
            }            
        }
    }

    // Draw the hero
    //Game->Hero->Rect = Game->Hero->CurrentTile->Rect;
    Game->Hero->UpdateVisual(0.001);
    SDL_RenderTexture(renderer, Game->Hero->Texture, NULL, &Game->Hero->Rect);
    
    // Draw enemies and pickups

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    delete Game;
    /* SDL will clean up the window/renderer for us. */
}