#include <SDL2/SDL.h>
#include <stdio.h>

#include "sketch.h"

void setup(
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

void clean_up(
  int const ROW,
  int * * grid
) {
  for (int i = 0; i < ROW; ++i) {
    free(grid[i]);
  }
  free(grid);
}

