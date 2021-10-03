#include <SDL2/SDL.h>
#include "MEOW.h"

int main(void) {
  SDL_Window * window;
  SDL_Renderer * renderer;
  int const WIDTH = 800;
  int const HEIGHT = 500;
  char const TITLE[] = "10PRINT PI WITH LIGHTSABERS";

  MEOW_Init(&window, &renderer, WIDTH, HEIGHT, TITLE);

  int const ROW = 40;
  int const COL = WIDTH/(HEIGHT/ROW);
  int const FPS = 60;
  MEOW_Repeat(renderer, WIDTH, HEIGHT, ROW, COL, FPS);

  MEOW_Destroy(window, renderer);
  return 0;
}
