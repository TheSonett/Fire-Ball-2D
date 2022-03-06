// Created on: October 4, 2021 by Joy Saha
// Author: @TheSonett
// My First Game :)


#include <stdio.h>
#include <time.h>
#include <conio.h>

#include "Main.h"
#include "Status.h"
#include "GameLoader.h"


int SDL_main(int argc, char *argv[])
{
     // Random number init
    srand(time(NULL));

    // SDL2 Init
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    TTF_Init();

    // Creating Game structure
    Game game;

    // Creating Window
    SDL_Window *window = SDL_CreateWindow("FireBall", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE);
    SDL_Surface *icon = IMG_Load("src/img/ball.png");
    SDL_SetWindowIcon(window, icon);
    SDL_FreeSurface(icon);

    // Creating Renderer
    game.renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    // Opening music
    Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096);
    loadGame(&game);

    // Game Loop
    int quit = 0;
    while(!quit)
    {
        quit = processEvents(window, &game);
        process(&game);
        collisionDetection(&game);
        doRender(game.renderer, &game);
    }


    // Destroy Staffs
    TTF_CloseFont(game.font);
    SDL_DestroyTexture(game.star);
    SDL_DestroyTexture(game.playerFrames[0]);
    SDL_DestroyTexture(game.playerFrames[1]);
    SDL_DestroyTexture(game.brick);
    SDL_DestroyTexture(game.fire);
    if(game.label != NULL)
        SDL_DestroyTexture(game.label);
    if(game.myself != NULL)
        SDL_DestroyTexture(game.myself);

    Mix_FreeChunk(game.landSound);
    Mix_FreeChunk(game.jumpSound);
    Mix_FreeChunk(game.dieSound);

    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(game.renderer);

    TTF_Quit();
    SDL_Quit();
    return 0;
}
