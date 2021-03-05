#ifndef UTILS_H_
#define UTILS_H_

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct {
    float x, y, size;
    float x_vel, y_vel;
    float x_acc, y_acc;
    char isGrounded;
    SDL_Texture *image;
} Player;

typedef struct {
    Player player;

    SDL_Renderer *renderer;
    SDL_Window *window;
} GameState;

void InitializeGame(GameState *gameState);
int processEvents(GameState *gameState);
void processRendering(GameState *gameState);

#endif