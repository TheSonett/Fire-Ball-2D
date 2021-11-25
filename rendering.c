#include "main.h"
#include "status.h"

void doRender(SDL_Renderer *renderer, Game *game)
{
    if(game->statusState == STATUS_STATE_LIVES)
    {
        draw_status_lives(game);
    }
    else
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


        // ledges position drawing
        for(int i = 0; i < L; i++)
        {
            SDL_Rect ledgeRect = {game->scrollX + game->ledges[i].x, game->ledges[i].y, game->ledges[i].w, game->ledges[i].h};
            SDL_RenderCopy(renderer, game->brick, NULL, &ledgeRect);
        }


        // player position drawing
        SDL_Rect rect = { game->scrollX + game->player.x, game->player.y, 28, 28};
        SDL_RenderCopyEx(renderer, game->playerFrames[game->player.aniFrame], NULL, &rect, 0, NULL, 0);

        if(game->player.isDead)
        {
            SDL_Rect rect = { game->scrollX + game->player.x-5, game->player.y-50, 38, 83};
            SDL_RenderCopyEx(renderer, game->fire, NULL, &rect, 0, NULL, (game->time%20 < 10));
        }

        // star positions drawing
        for(int i = 0; i < N; i++)
        {
            SDL_Rect starRect = { game->scrollX + game->stars[i].x + rand()%4, game->stars[i].y + rand()%4, 35, 40 };
            SDL_RenderCopy(renderer, game->star, NULL, &starRect);
        }
    }

    SDL_RenderPresent(renderer);
}
