#define _CRT_SECURE_NO_WARNINGS // for sprintf exception handling

#include <stdio.h>
#include "Main.h"

void init_status_lives(Game *game)
{
    char str[100] = "";
    sprintf(str, "  remaining -> %d", (int)game->player.lives);

    SDL_Color white = {255, 255, 255, 255};
    SDL_Surface *tmp = TTF_RenderText_Blended(game->font, str, white);
    game->labelW = tmp->w;
    game->labelH = tmp->h;

    game->label = SDL_CreateTextureFromSurface(game->renderer, tmp);
    SDL_FreeSurface(tmp);

    char myself[100] = "Created By Joy Saha";

    SDL_Color whiteText = {255, 255, 255, 255};
    SDL_Surface *my = TTF_RenderText_Blended(game->font, myself, whiteText);
    game->myselfW = my->w - 72;
    game->myselfH = my->h;
    game->myself = SDL_CreateTextureFromSurface(game->renderer, my);
    SDL_FreeSurface(my);
}

void draw_status_lives(Game *game)
{
    SDL_SetRenderDrawColor(game->renderer, 0, 0, 0, 0);
    SDL_RenderClear(game->renderer);

    // player position drawing
    SDL_Rect rect = {320-140, 240-40, 28, 28};
    if(game->time % 60 == 0)
    {
        if(game->player.aniFrame == 0)
        {
            game->player.aniFrame = 1;
        }
        else
        {
            game->player.aniFrame = 0;
        }
    }
    SDL_RenderCopyEx(game->renderer, game->playerFrames[game->player.aniFrame], NULL, &rect, 0, NULL, 0);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_Rect textRect = {220, 240-game->labelH, game->labelW, game->labelH};
    SDL_RenderCopy(game->renderer, game->label, NULL, &textRect);

    SDL_SetRenderDrawColor(game->renderer, 255, 255, 255, 255);
    SDL_Rect myRect = {0, 0, game->myselfW, game->myselfH};
    SDL_RenderCopy(game->renderer, game->myself, NULL, &myRect);
}


void shutdown_status_lives(Game *game)
{
    SDL_DestroyTexture(game->label);
    SDL_DestroyTexture(game->myself);
    game->label = NULL;
    game->myself = NULL;
}
