#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
// #include "SDL.h"
#include "SDL2/SDL.h"
#include "snake.h"
#include "food.h"

class Renderer {
 public:

  /*
  * constructor
  * @param screen_width width of the screen window
  * @param screen_height height of the screen window
  * @param grid_width width of the grid within the screen
  * @param grid_height height of the grid within the screen
  */
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  
  // destructor
  ~Renderer();

  /*
  * render all game objects
  * @param snake1 snake object of player 1 to be rendered 
  * @param snake2 snake object of player 2 to be rendered 
  * @param food food to be rendered in the grid within the screen
  */
  void Render(Snake const *snake1, Snake const *snake2, Food &food);

  /*
  * update window title in 1 player game mode
  * @param score score of player 1 to be rendered 
  * @param fps fps of the game
  */
  void UpdateWindowTitle(int score, int fps);
  
  /*
  * update window title in 1 player game mode
  * @param score1 score of player 1 to be rendered
  * @param score2 score of player 2 to be rendered 
  * @param fps fps of the game
  */
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