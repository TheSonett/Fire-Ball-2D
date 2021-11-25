#include "main.h"

int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2)
{
    return (!((x1 > (x2+wt2)) || (x2 > (x1+wt1)) || (y1 > (y2+ht2)) || (y2 > (y1+ht1))));
}


// Collision Detection
void collisionDetection(Game *game)
{
    for(int i = 0; i < L; i++)
    {
        if(collide2d(game->player.x, game->player.y, game->stars[i].x, game->stars[i].y, 48, 48, 32, 32))
        {
            if(!game->player.isDead)
            {
                game->player.isDead = 1;
                Mix_PlayChannel(-1, game->dieSound, 0);
            }
        }
    }
    // check for collision with any ledges (any bricks)
    for(int i = 0; i < N; i++)
    {
        float playerW = 32;
        float playerH = 32;
        float playerX = game->player.x;
        float playerY = game->player.y;
        float brickX = game->ledges[i].x;
        float brickY = game->ledges[i].y;
        float brickW = game->ledges[i].w;
        float brickH = game->ledges[i].h;

        if(playerY + playerH > brickY && playerY < brickY + brickH)
        {
            // right edge
            if(playerX < brickX + brickW && playerX + playerW > brickX + brickW)
            {
                game->player.x = brickX + brickW;
                playerX = brickX + brickW;
            }
            // left edge
            else if(playerX + playerW > brickX && playerX < brickX)
            {
                game->player.x = brickX - playerW;
                playerX = brickX - playerW;
            }
        }

        if(playerX + playerW > brickX && playerX < brickX + brickW)
        {
            if(playerY < brickY + brickH && playerY > brickY)
            {
                game->player.y = brickY + brickH;
                game->player.dy = 0;
                game->player.onLedge = 1;
            }
            // landing on the ledge
            else if(playerY + playerH > brickY && playerY < brickY)
            {
                game->player.y = brickY - playerH + 4;
                game->player.dy = 0;
                if(!game->player.onLedge)
                {
                    Mix_PlayChannel(-1, game->landSound, 1);
                    game->player.onLedge = 1;
                }
            }
        }
    }
}


// Keyboard Events
int processEvents(SDL_Window *window, Game *game)
{
    SDL_Event event;
    int done = 0;

    while(SDL_PollEvent(&event))
    {
        switch(event.type)
        {
        case SDL_WINDOWEVENT_CLOSE:
        {
            if(window)
            {
                SDL_DestroyWindow(window);
                window = NULL;
                done = 1;
            }
        }
        break;
        case SDL_KEYDOWN:
        {
            switch(event.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                done = 1;
                break;
            case SDLK_UP:
                if(game->player.onLedge)
                {
                    game->player.dy = -10;
                    game->player.onLedge = 0;
                    Mix_PlayChannel(-1, game->jumpSound, 0);
                }
                break;
            }
        }
        break;
        case SDL_QUIT:
            done = 1;
            break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if(state[SDL_SCANCODE_LEFT])
    {
        game->player.x -= 10;
    }
    if(state[SDL_SCANCODE_RIGHT])
    {
        game->player.x += 10;
    }

    return done;
}

