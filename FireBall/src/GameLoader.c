#include <stdio.h>

#include "Main.h"
#include "Status.h"

void loadGame(Game *game)
{
    //stars
    SDL_Surface *surface = IMG_Load("src/img/fire.png");
    game->star = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    //player
    surface = IMG_Load("src/img/ball.png");
    game->playerFrames[0] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    surface = IMG_Load("src/img/ball2.png");
    game->playerFrames[1] = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    //bricks
    surface = IMG_Load("src/img/brick.png");
    game->brick = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    // fire
    surface = IMG_Load("src/img/fire.png");
    game->fire = SDL_CreateTextureFromSurface(game->renderer, surface);
    SDL_FreeSurface(surface);

    // Load fonts
    game->font = TTF_OpenFont("src/font/Roboto-LightItalic.ttf", 48);
    if(!game->font)
    {
        printf("Cannot found the Font!\n");
        SDL_Quit();
        exit(1);
    }

    // Load Sounds
    game->dieSound = Mix_LoadWAV("src/music/die.wav");
    game->landSound = Mix_LoadWAV("src/music/land.wav");
    game->jumpSound = Mix_LoadWAV("src/music/jump.wav");


    // Initialization
    game->label = NULL;
    game->player.x = 100;
    game->player.y = 100;
    game->player.dy = 0;
    game->player.onLedge = 0;
    game->player.aniFrame = 0;
    game->player.lives = 3;
    game->statusState = STATUS_STATE_LIVES;
    game->time = 0;
    game->scrollX = 0;
    game->player.isDead = 0;
    game->deathCount = -1;

    init_status_lives(game);

    // Initialization of stars
    for(int i = 0; i < N; i++)
    {
        game->stars[i].x = SCREEN_WIDTH/2+rand()%38400;
        game->stars[i].y = rand()%SCREEN_HEIGHT;
    }

    // Initialization of ledges
    for(int i = 0; i < L-20; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = i*384;
        if(i == 0)
            game->ledges[i].y = 400;
        else
            game->ledges[i].y = 400+100-rand()%200;
    }

    for(int i = L-20; i < L; i++)
    {
        game->ledges[i].w = 256;
        game->ledges[i].h = 64;
        game->ledges[i].x = 450+rand()%38400;
        if(i % 2 == 0)
            game->ledges[i].y = 200;
        else
            game->ledges[i].y = 350;
    }
}



void process(Game *game)
{
    game->time++;
    if(game->time > 120)
    {
        shutdown_status_lives(game);
        game->statusState = STATUS_STATE_GAME;
    }
    else if(game->statusState == STATUS_STATE_GAMEOVER)
    {
        if(game->time > 120)
        {
            SDL_Quit();
            exit(0);
        }
    }
    if(game->statusState == STATUS_STATE_GAME)
    {
        if(!game->player.isDead)
        {
            // player movement
            Player *player = &game->player;
            player->y += player->dy;
            player->dy += GRAVITY;


            if(player->onLedge)
            {
                if(game->time % 60 == 0)
                {
                    if(player->aniFrame == 0)
                    {
                        player->aniFrame = 1;
                    }
                    else
                    {
                        player->aniFrame = 0;
                    }
                }
            }
            player->dy += GRAVITY;
        }
        if (game->player.isDead && game->deathCount < 0)
        {
            game->deathCount = 120;
        }
        if (game->deathCount >= 0 || game->player.y >= SCREEN_HEIGHT)
        {

            game->deathCount--;

            if (game->deathCount < 0 )
            {
                game->player.lives--;
                if (game->player.lives >= 0)
                {
                    init_status_lives(game);
                    game->statusState = STATUS_STATE_LIVES;
                    game->time = 0;

                    //reset
                    game->player.isDead = 0;
                    game->player.x = 120;
                    game->player.y = 120;
                    game->player.dy = 0;
                    game->player.onLedge = 0;
                }
                else
                {
                    game->statusState = STATUS_STATE_GAMEOVER;
                    game->time = 0;
                }

            }
        }
    }

    // Scrolling
    game->scrollX = -game->player.x+SCREEN_WIDTH/2;
    if(game->scrollX > 0)
    {
        game->scrollX = 0;
    }

    // If lives less than 0
    if(game->player.lives < 0)
    {
        game->deathCount = 120;
        SDL_Quit();
        exit(0);
    }
}
