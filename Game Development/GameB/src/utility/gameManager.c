#include "gameManager.h"

#include <stdio.h>

#include "SDL2/SDL.h"
#include "gameState.h"
#include "utils.h"

void jump(GameState* state) {
    if (state->player.isGrounded == 1) {
        state->player.y_vel = -13;
        state->player.isGrounded = 0;
    }
}

void physics(GameState* state) {
    state->player.x += state->player.x_vel;
    state->player.y += state->player.y_vel;

    state->player.y_vel += 0.5;
}

void collisions(GameState* state) {
    if (checkForIntersect(state->player.y, state->player.size, state->platform.y, state->platform.h)) {
        if (state->player.x < state->platform.x + state->platform.w &&
            state->player.x + state->player.size < state->platform.x + state->platform.w &&
            state->player.x + state->player.size > state->platform.x &&
            state->player.x < state->platform.x) {
            state->player.x = state->platform.x - state->player.size;
        } else if (state->player.x > state->platform.x &&
                   state->player.x + state->player.size > state->platform.x &&
                   state->player.x + state->player.size > state->platform.x + state->platform.w &&
                   state->player.x < state->platform.x + state->platform.w) {
            state->player.x = state->platform.x + state->platform.w;
        }
    }

    if (checkForIntersect(state->player.x, state->player.size, state->platform.x, state->platform.w)) {
        if (state->player.y + state->player.size > state->platform.y &&
            state->player.y > state->platform.y &&
            state->player.y < state->platform.y + state->platform.h &&
            state->player.y + state->player.size > state->platform.y + state->platform.h) {
            state->player.y = state->platform.y + state->platform.h;
            state->player.y_vel = 0;
        } else if (state->player.y + state->player.size < state->platform.y + state->platform.h &&
                   state->player.y < state->platform.y + state->platform.h &&
                   state->player.y < state->platform.y &&
                   state->player.y + state->player.size > state->platform.y) {
            state->player.isGrounded = 1;
            state->player.y = state->platform.y - state->player.size;
            state->player.y_vel = 0;
        }
    }

    if (state->player.y > 600 - state->player.size) {
        state->player.isGrounded = 1;
        state->player.y = 600 - state->player.size;
        state->player.y_vel = 0;
    }
}

void movement(GameState* state) {
    const Uint8* key = SDL_GetKeyboardState(NULL);
    if (key[SDL_SCANCODE_A]) {
        state->player.x -= 10;
        collisions(state);
    }
    if (key[SDL_SCANCODE_D]) {
        state->player.x += 10;
        collisions(state);
    }
    if (key[SDL_SCANCODE_W] || key[SDL_SCANCODE_SPACE]) {
        jump(state);
        collisions(state);
    }
}

int processEvents(GameState* state) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT: {
                return 1;
            } break;
            case SDL_WINDOWEVENT_CLOSE: {
                return 1;
            } break;
        }
    }

    collisions(state);
    movement(state);
    physics(state);

    return 0;
}

void processRender(GameState* state) {
    SDL_SetRenderDrawColor(state->renderer, 12, 231, 124, 255);
    SDL_RenderClear(state->renderer);

    SDL_SetRenderDrawColor(state->renderer, 255, 255, 255, 200);
    SDL_Rect pBox = {state->player.x, state->player.y,
                     state->player.size, state->player.size};
    SDL_RenderFillRect(state->renderer, &pBox);

    SDL_SetRenderDrawColor(state->renderer, 0, 0, 0, 150);
    SDL_Rect plf = {state->platform.x, state->platform.y,
                    state->platform.w, state->platform.h};
    SDL_RenderFillRect(state->renderer, &plf);

    SDL_RenderPresent(state->renderer);
}

void processGame(GameState* state, int* done) {
    *done = processEvents(state);
    processRender(state);
}
