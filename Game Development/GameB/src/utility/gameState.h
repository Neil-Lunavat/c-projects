#ifndef _GAME_STATE_H_
#define _GAME_STATE_H_

#include "SDL2/SDL.h"

typedef struct {
    float x, y;
    float x_vel, y_vel;
    float size;
    char isGrounded;
} Player;

typedef struct {
    int x, y, w, h;
} Platform;

typedef struct {
    SDL_Window *window;
    SDL_Renderer *renderer;
    Player player;

    Platform platform;
} GameState;

#endif  //_GAME_STATE_H_