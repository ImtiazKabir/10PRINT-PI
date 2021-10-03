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
  int * * * const GRID_P
);
void clean_up(
  int const ROW,
  int * * grid
);

/* loop.c */
void update(void);
void draw(
  SDL_Renderer * renderer,
  int const ROW,
  int const COL,
  int const * const * const GRID
);

#endif /* LIB_MEOW_SKETCH_H */
