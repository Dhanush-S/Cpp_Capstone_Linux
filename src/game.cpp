#include "game.h"
#include <iostream>
// #include "SDL.h"
#include "SDL2/SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int game_mode)
    : _gameMode(game_mode),
      engine(dev()),
      _food(grid_width,grid_height),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {

  snake1 = std::make_unique<Snake>(grid_width, grid_height);       
  if(game_mode == 2)
    snake2 = std::make_unique<Snake>(grid_width, grid_height);

  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake1.get(), snake2.get());
    
    // update
    if(snake.isSnakeActive)
      Update();

    // render
    renderer.Render(snake, _food);
    
    // start the timer on the food once it is rendered to the user
    _food.FoodPlaced();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  int x, y;
  _food.GenerateNewFood();
  while (true) {
    x = _food.GetFoodLocation().x;
    y = _food.GetFoodLocation().y;

    // Check that the location is not occupied by a snake item before placing
    // food.
    if(snake.SnakeCell(x,y))
      _food.GenerateNewFoodLocation();
    else  
      return;
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  if(_food.HasFoodExpired() && snake.isSnakeActive)
  {
    PlaceFood();
    return;
  }  

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here
  if (_food.GetFoodLocation().x == new_x && _food.GetFoodLocation().y == new_y){

    // score++; tied to the size of the snake
    snake.SetFoodTypeConsumed(_food.GetFoodType());

    _food.FoodConsumed();
    PlaceFood();

    // Grow snake     
    snake.GrowBody();
    // snake.speed += 0.02; handled within snake class
  }
  score = snake.size;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }