#include <SDL2/SDL.h>
#include <stdio.h>
#include "sketch.h"

void draw(
  SDL_Renderer * renderer,
  int const ROW,
  int const COL,
  int const * const * const GRID,
  int const WIDTH,
  int const HEIGHT,
  SDL_Texture * zero,
  SDL_Texture * one,
  int const INDEX,
  bool const NOLOOP
) {
  if (NOLOOP == true) return;

  if (SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255) == -1) {
    MEOW_Error("Setting the background color with SDL_SetRenderDrawColor");
  }
  if (SDL_RenderClear(renderer) == -1) {
    MEOW_Error("Clearing the window for background with SDL_RenderClear");
  }

  for (int n = 0; n < INDEX; ++n) {
    int const I = n / COL;
    int const J = n % COL;
    SDL_Rect cell = {
      .w = WIDTH/COL,
      .h = HEIGHT/ROW,
    };
    cell.x = J * cell.w;
    cell.y = I * cell.h;
    SDL_Texture *state = GRID[I][J]? one:zero;
    if (SDL_RenderCopy(renderer, state, NULL, &cell) < 0) {
      MEOW_Error("Drawing state with SDL_RenderCopy");
    }
  }
}


void update(
  int * const INDEX_P,
  int const ROW,
  int const COL,
  bool * const NOLOOP_P
) {
  if (*NOLOOP_P == true) {
    return;
  }
  if (*INDEX_P == ROW * COL) {
    *NOLOOP_P = true;
  }
  else {
    *INDEX_P += 1;
  }
}
