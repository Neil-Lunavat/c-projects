
#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct {
    int x, y, size;
    SDL_Texture *playerImage;
} Player;

typedef struct {
    Player player;
} GameState;

int processEvents(SDL_Window *window) {
    int done = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                SDL_DestroyWindow(window);
                window = NULL;
                done = 1;
            } break;

            case SDL_QUIT: {
                done = 1;
            } break;
        }
    }

    return done;
}

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window;
    SDL_Renderer *renderer;

    window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    int done = 0;
    while (!done) {
        done = processEvents(window);
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}