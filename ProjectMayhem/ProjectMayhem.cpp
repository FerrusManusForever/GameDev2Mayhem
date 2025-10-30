
#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_image/SDL_image.h>
#include <iostream>
#include "DungeonGame.h"

using namespace std;

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

    const char* room = "Data/Rooms/Room01.bmp";
    Game->LoadRoom(room);
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
            Game->Hero->Rect.y -= tileSize;
        }
        if (event->key.scancode == SDL_SCANCODE_S)
        {
            Game->Hero->Rect.y += tileSize;
        }
        if (event->key.scancode == SDL_SCANCODE_A)
        {
            Game->Hero->Rect.x -= tileSize;
        }
        if (event->key.scancode == SDL_SCANCODE_D)
        {
            Game->Hero->Rect.x += tileSize;
        }

    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */

}

/*  This function runs once per frame, and is the heart of the program.
    Think of this like Unity's Update() loop */
SDL_AppResult SDL_AppIterate(void* appstate)
{
    /* as you can see from this, rendering draws over whatever was drawn before it. */
    SDL_SetRenderDrawColor(renderer, 33, 33, 33, SDL_ALPHA_OPAQUE);  /* dark gray, full alpha */
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    // Your Update code goes here.

    //SDL_RenderTexture(renderer, Game->texHero, NULL, &Game->RectHero);
   

    // draw the grid
    for (int x = 0; x < 10; x++)
    {
        for (int y = 0; y < 10; y++)
        {
            if (Game->Tiles[x][y].Walkable)
            {
                SDL_RenderTexture(renderer, Game->Tiles[x][y].Texture, NULL, &Game->Tiles[x][y].Rect);
            }
            
        }
    }


    SDL_RenderTexture(renderer, Game->Hero->Texture, NULL, &Game->Hero->Rect);

    SDL_RenderPresent(renderer);  /* put it all on the screen! */

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void* appstate, SDL_AppResult result)
{
    delete Game;
    /* SDL will clean up the window/renderer for us. */
}