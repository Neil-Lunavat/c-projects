#include <stdio.h>

#include "SDL2/SDL.h"
#include "utility/gameManager.h"
#include "utility/gameState.h"

int main(int argc, char* argv[]) {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    GameState state = {
        window : window,
        renderer : renderer,
        player : {
            x : 300,
            y : 300,
            x_vel : 0,
            y_vel : 0,
            size : 64,
            isGrounded : 0
        },
        platform : {
            x : 100,
            y : 400,
            w : 500,
            h : 40
        }
    };

    int done = 0;
    while (!done) {
        processGame(&state, &done);
    }

    SDL_Quit();
    return 0;
}