#include "gameStateManager.h"

#include <stdio.h>

// Just some bitchy init
void InitializeGame(GameState *gameState) {
    gameState->window = SDL_CreateWindow("GAME", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, 0);
    gameState->renderer = SDL_CreateRenderer(gameState->window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    SDL_Surface *surf = IMG_Load("images/mushroom.png");

    // Player Sprite
    gameState->player.image = SDL_CreateTextureFromSurface(gameState->renderer, surf);

    // Initial Positions
    gameState->player.x = 320 - 64, gameState->player.y = 240 - 64;

    // Player size
    gameState->player.size = 64;

    // Initial Velocity
    gameState->player.x_vel = 0, gameState->player.y_vel = 0;

    // Initial Acceleration
    gameState->player.x_acc = 0, gameState->player.y_acc = 0.1;

    // IDKY
    gameState->player.isGrounded = 0;

    SDL_FreeSurface(surf);
}

void detectCollisions(GameState *gameState) {
    if (gameState->player.y > 480 - gameState->player.size) {
        gameState->player.isGrounded = 1;
        gameState->player.y_vel = 0;
        gameState->player.y = 480 - gameState->player.size;
    }

    if (gameState->player.y < 0) {
        gameState->player.y_vel = 0;
        gameState->player.y = 0;
    }

    if (gameState->player.x > 640 - gameState->player.size) {
        gameState->player.x_vel = 0;
        gameState->player.x = 640 - gameState->player.size;
    }

    if (gameState->player.x < 0) {
        gameState->player.x_vel = 0;
        gameState->player.x = 0;
    }
}

void processPhysics(GameState *gameState) {
    gameState->player.x_vel += gameState->player.x_acc;
    gameState->player.y_vel += gameState->player.y_acc;

    gameState->player.x += gameState->player.x_vel;
    gameState->player.y += gameState->player.y_vel;

    gameState->player.x_acc = 0;
    gameState->player.y_acc = 0;

    gameState->player.y_acc += 0.5;
}

// Do the event stuff
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
    if (state[SDL_SCANCODE_SPACE]) {
        gameState->player.isGrounded = (gameState->player.y > 480 - gameState->player.size) ? 1 : 0;

        if (gameState->player.isGrounded == 1) {
            gameState->player.y_acc -= 10.98;
            gameState->player.isGrounded = 0;
        }

        gameState->player.isGrounded = 0;
    }

    // COLLISION DETECTION
    detectCollisions(gameState);

    // Movement
    processPhysics(gameState);

    return done;
}

// Do the Rendering stuff
void processRendering(GameState *gameState) {
    SDL_SetRenderDrawColor(gameState->renderer, 127, 127, 127, 255);
    SDL_RenderClear(gameState->renderer);

    SDL_Rect rect = {gameState->player.x, gameState->player.y, gameState->player.size, gameState->player.size};
    SDL_RenderCopy(gameState->renderer, gameState->player.image, NULL, &rect);

    SDL_RenderPresent(gameState->renderer);
}