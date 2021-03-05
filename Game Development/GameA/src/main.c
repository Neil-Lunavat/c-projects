
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "utility/gameStateManager.h"

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