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

  int const I = INDEX / COL;
  int const J = INDEX % COL;
  SDL_Rect const cell = {
    .w = WIDTH/COL,
    .h = HEIGHT/ROW,
    .x = J * cell.w,
    .y = I * cell.h
  };
  SDL_Texture *state = GRID[I][J]? one:zero;
  if (SDL_RenderCopy(renderer, state, NULL, &cell) < 0) {
    MEOW_Error("Drawing state with SDL_RenderCopy");
  }
}


void update(
  int * const INDEX_P,
  int const ROW,
  int const COL,
  bool * const NOLOOP_P
) {
  if (*NOLOOP_P == true) return;
  *INDEX_P += 1;
  if (*INDEX_P == ROW * COL) {
    *NOLOOP_P = true;
  }
}