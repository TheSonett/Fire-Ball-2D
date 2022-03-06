#ifndef MAIN_H
#define MATH_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#define N 100
#define L 100
#define PLAYER_FRAME 2
#define STATUS_STATE_LIVES 0
#define STATUS_STATE_GAME 1
#define STATUS_STATE_GAMEOVER 2


#define GRAVITY 0.12f
#define SCREEN_WIDTH 850
#define SCREEN_HEIGHT 580

// structures
typedef struct
{
    float x, y;
    float dy;
    short lives;
    char *name;
    int onLedge;
    int isDead;
    int aniFrame;
} Player;


typedef struct
{
    int x, y;
} Star;

typedef struct
{
    int x, y, w, h;
} Ledge;

typedef struct
{
    //player
    float scrollX;
    Player player;

    // enemies
    Star stars[N];
    Ledge ledges[L];

    // images
    SDL_Texture *star;
    SDL_Texture *playerFrames[PLAYER_FRAME];
    SDL_Texture *brick;
    SDL_Texture *fire;
    SDL_Texture *myself;
    int myselfW, myselfH;
    SDL_Texture *label;
    int labelW, labelH;
    SDL_Renderer *renderer;

    //font
    TTF_Font *font;

    //time
    int time;
    int deathCount;
    int statusState;

    //sounds
    Mix_Chunk *jumpSound, *landSound, *dieSound;

} Game;

void doRender(SDL_Renderer *renderer, Game *game);
#endif // MAIN_H
