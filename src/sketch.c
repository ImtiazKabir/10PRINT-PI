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
} MainLoopParam_t;

void main_loop(void *v_param);
int gcd(int const A, int const B);


void MEOW_Repeat(
  SDL_Renderer *renderer,
  int const WIDTH,
  int const HEIGHT,
  int const FPS
) {
  int const GCD = gcd(WIDTH, HEIGHT);
  int const SIDE = GCD < WIDTH/20? WIDTH/20 : GCD;
  int const ROW = HEIGHT/SIDE;
  int const COL = WIDTH/SIDE;

  int * * grid;

  /* Definition and setting variables for sketch */
  setup(ROW, COL, &grid);

  MainLoopParam_t param = {
    .renderer = renderer,
    .quit_flag = false,
    .FPS = FPS,
    .ROW = ROW,
    .COL = COL,
    .grid = grid
  };

  #ifdef __EMSCRIPTEN__
  emscripten_set_main_loop_arg(main_loop, &param, 0, 1);
  #else
  while (!param.quit_flag) {
    main_loop(&param);
  }
  #endif

  /* cleaning up sekcth "things" */
  clean_up(ROW, grid);
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
  update();

  draw(
    param->renderer,
    param->ROW,
    param->COL,
    (int const * const * const) param->grid
  );
  SDL_Delay(1000 / (unsigned)param->FPS);
  SDL_RenderPresent(param->renderer);
}


int gcd(int const A, int const B) {
  if (B == 0) {
    return A;
  }
  return gcd(B, A%B);
}
