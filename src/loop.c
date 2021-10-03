#include <SDL2/SDL.h>
#include <stdio.h>
#include "sketch.h"

void draw(
  SDL_Renderer * renderer,
  int const ROW,
  int const COL,
  int const * const * const GRID
) {
  if (SDL_SetRenderDrawColor(renderer, 55, 55, 55, 255) == -1) {
    MEOW_Error("Setting the background color with SDL_SetRenderDrawColor");
  }
  if (SDL_RenderClear(renderer) == -1) {
    MEOW_Error("Clearing the window for background with SDL_RenderClear");
  }
}


void update(void) {}
