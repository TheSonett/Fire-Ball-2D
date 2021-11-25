#ifndef LOADGAME_H
#define LOADGAME_H

void loadGame(Game *game);
void process(Game *game);

// rendering
void doRender(SDL_Renderer *renderer, Game *game);

// collision detection
int collide2d(float x1, float y1, float x2, float y2, float wt1, float ht1, float wt2, float ht2);
void collisionDetection(Game *game);

// events
int processEvents(SDL_Window *window, Game *game);

#endif // LOADGAME_H
