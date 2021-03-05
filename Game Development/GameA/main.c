
#include <stdio.h>
#include <stdlib.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

typedef struct {
    int x, y, size;
    SDL_Texture *image;
} Player;

typedef struct {
    Player player;

    SDL_Renderer *renderer;
    SDL_Window *window;
} GameState;

int processEvents(GameState *gameState) {
    int done = 0;
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_WINDOWEVENT_CLOSE: {
                SDL_DestroyWindow(gameState->window);
                gameState->window = NULL;
                done = 1;
            } break;

            case SDL_QUIT: {
                done = 1;
            } break;
        }
    }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_A]) {
        gameState->player.x -= 10;
    }
    if (state[SDL_SCANCODE_D]) {
        gameState->player.x += 10;
    }
    if (state[SDL_SCANCODE_W]) {
        gameState->player.y -= 10;
    }
    if (state[SDL_SCANCODE_S]) {
        gameState->player.y += 10;
    }

    return done;
}

void InitializeGame(GameState *gameState) {
    gameState->window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    gameState->renderer = SDL_CreateRenderer(gameState->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface *surf = IMG_Load("mushroom.png");
    gameState->player.image = SDL_CreateTextureFromSurface(gameState->renderer, surf);
    gameState->player.x = 320 - 64, gameState->player.y = 240 - 64, gameState->player.size = 64;
    SDL_FreeSurface(surf);
}

void processRendering(GameState *gameState) {
    SDL_SetRenderDrawColor(gameState->renderer, 127, 127, 127, 255);
    SDL_RenderClear(gameState->renderer);

    SDL_Rect rect = {gameState->player.x, gameState->player.y, gameState->player.size, gameState->player.size};
    SDL_RenderCopy(gameState->renderer, gameState->player.image, NULL, &rect);

    SDL_RenderPresent(gameState->renderer);
}

int main(int argc, char *argv[]) {
    
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    GameState gameState;
    InitializeGame(&gameState);

    int done = 0;
    while (!done) {
        done = processEvents(&gameState);
        processRendering(&gameState);
    }

    IMG_Quit();
    SDL_Quit();

    return 0;
}