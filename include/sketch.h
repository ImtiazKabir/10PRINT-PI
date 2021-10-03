#ifndef LIB_MEOW_SKETCH_H
#define LIB_MEOW_SKETCH_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>

static inline void MEOW_Error(char const * const func_name) {
  fprintf(stderr, "~~IM~~ %s did not work\n"
                  "----------------------\n"
                  "%s", func_name, SDL_GetError());
  SDL_ClearError();
}
char * MEOW_GetPath(char const * const child);  /* lib/getpath.c */


/* event.c */
bool event_handler(void);

/* once.c */
void setup(
  int const ROW,
  int const COL,
  int * * * const GRID_P,

  SDL_Renderer * renderer,
  SDL_Texture * * const ZERO_P,
  SDL_Texture * * ONE_P
);

void clean_up(
  int const ROW,
  int * * grid,
  SDL_Texture * zero,
  SDL_Texture * one
);

/* loop.c */
void update(
  int * const INDEX_P,
  int const ROW,
  int const COL,
  bool * const NOLOOP_P
);

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
);

#endif /* LIB_MEOW_SKETCH_H */
