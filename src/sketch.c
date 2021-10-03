#include <SDL2/SDL.h>
#include <stdbool.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "sketch.h"

typedef struct MainLoopParam {
  SDL_Renderer * renderer;
  bool quit_flag;
  int const FPS;

  int const ROW;
  int const COL;
  int * * grid;

  int const WIDTH;
  int const HEIGHT;

  SDL_Texture * zero;
  SDL_Texture * one;

  int index;
  bool noLoop;
} MainLoopParam_t;

void main_loop(void *v_param);

void MEOW_Repeat(
  SDL_Renderer *renderer,
  int const WIDTH,
  int const HEIGHT,
  int const ROW,
  int const COL,
  int const FPS
) {
  int * * grid;

  SDL_Texture * zero;
  SDL_Texture * one;

  /* Definition and setting variables for sketch */
  setup(ROW, COL, &grid, renderer, &zero, &one);

  MainLoopParam_t param = {
    .renderer = renderer,
    .quit_flag = false,
    .FPS = FPS,
    .ROW = ROW,
    .COL = COL,
    .grid = grid,
    .WIDTH = WIDTH,
    .HEIGHT = HEIGHT,
    .zero = zero,
    .one = one,
    .index = 0,
    .noLoop = false
  };

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(main_loop, &param, 0, 1);
  #else
  while (!param.quit_flag) {
    main_loop(&param);
  }
  #endif

  /* cleaning up sekcth "things" */
  clean_up(ROW, grid, zero, one);
}


void main_loop(void *v_param) {
  MainLoopParam_t * param = (MainLoopParam_t *) v_param;

  /* handle event */
  if (event_handler()) {
    #ifdef __EMSCRIPTEN__
    emscripten_cancel_main_loop();
    #else
    param->quit_flag = true;
    return;
    #endif /* __EMSCRIPTEN__ */
  }

  /* update and draw */
  draw(
    param->renderer,
    param->ROW,
    param->COL,
    (int const * const * const) param->grid,
    param->WIDTH,
    param->HEIGHT,
    param->zero,
    param->one,
    param->index,
    param->noLoop
  );

  update(
    &param->index,
    param->ROW,
    param->COL,
    &param->noLoop
  );
  SDL_Delay(1000 / (unsigned)param->FPS);
  SDL_RenderPresent(param->renderer);
}

