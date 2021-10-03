#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>

#include "sketch.h"

void creaeteGrid(
  int const ROW,
  int const COL,
  int * * * const GRID_P
);

void createTexture(
  SDL_Renderer * renderer,
  SDL_Texture ** const TEXTURE_P,
  char const * const DIR
);

void setup(
  int const ROW,
  int const COL,
  int * * * const GRID_P,
  SDL_Renderer * renderer,
  SDL_Texture * * const ZERO_P,
  SDL_Texture * * const ONE_P
) {

  creaeteGrid(ROW, COL, GRID_P);
  createTexture(renderer, ZERO_P, "assets/zero.png");
  createTexture(renderer, ONE_P, "assets/one.png");
}

void clean_up(
  int const ROW,
  int * * grid,
  SDL_Texture * zero,
  SDL_Texture * one
) {
  for (int i = 0; i < ROW; ++i) {
    free(grid[i]);
  }
  free(grid);

  /* clean up textures */
  SDL_DestroyTexture(zero);
  SDL_DestroyTexture(one);
}



void creaeteGrid(
  int const ROW,
  int const COL,
  int * * * const GRID_P
) {

  *GRID_P = calloc(ROW, sizeof **GRID_P);
  if (*GRID_P == NULL) {
    fprintf(stderr, "Failed to allocate memory for grid pointer");
  }
  for (int i = 0; i < ROW; ++i) {
    (*GRID_P)[i] = calloc(COL, sizeof *( (*GRID_P)[0]));
    if ( (*GRID_P)[i] == NULL) {
      fprintf(stderr, "Failed to allocate memory for grid rows");
    }
    for (int j = 0; j < COL; ++j) {
      (*GRID_P)[i][j] = rand() % 2;
    }
  }
}

void createTexture(
  SDL_Renderer *renderer,
  SDL_Texture ** const TEXTURE_P,
  char const * const DIR
) {

  char * path = MEOW_GetPath(DIR);
  SDL_Surface * surface = IMG_Load(path);
  if (surface == NULL) {
    MEOW_Error("Creating surface for life with IMG_Load");
  }
  *TEXTURE_P= SDL_CreateTextureFromSurface(renderer, surface);
  free(path);
  SDL_FreeSurface(surface);
}
