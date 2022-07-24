#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
// #include "SDL.h"
#include "SDL2/SDL.h"
#include "snake.h"
#include "food.h"

class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Render(Snake const snake, SDL_Point const &food);
  void Render(Snake const *snake1, Snake const *snake2, Food &food);
  void UpdateWindowTitle(int score, int fps);
  void UpdateWindowTitle(int score1, int score2, int fps);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;
};

#endif