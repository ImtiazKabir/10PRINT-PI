#ifndef LIB_MEOW_H
#define LIB_MEOW_H

#include <SDL2/SDL.h>

void MEOW_Init(
  SDL_Window **window,
  SDL_Renderer **renderer,
  int const WIDTH,
  int const HEIGHT,
  char const * const TITLE
);

/* sketch.c */
void MEOW_Repeat(
  SDL_Renderer *renderer,
  const int WIDTH,
  const int HEIGHT,
  const int FPS
);

void MEOW_Destroy(SDL_Window *window, SDL_Renderer *renderer);

#endif /* LIB_MEOW_H */
