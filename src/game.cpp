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

  snake1 = std::make_unique<Snake>(grid_width, grid_height, (grid_width-1)/2, (grid_height-1)/2);       
  if(game_mode == 2)
    snake2 = std::make_unique<Snake>(grid_width, grid_height, (grid_width+1)/2, (grid_height+1)/2);

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

    if(_gameMode == 1)
    {
      // Input, Update, Render - the main game loop.
      controller.HandleInput(running, snake1.get(), nullptr);
      // update
      if(snake1->isSnakeActive)
        Update();
      // render
      renderer.Render(snake1.get(), nullptr, _food);
    }
    else
    {
      controller.HandleInput(running, snake1.get(), snake2.get());
      if(snake1->isSnakeActive || snake2->isSnakeActive)
        Update();
      renderer.Render(snake1.get(), snake2.get(), _food);
    }

    // start the timer on the food once it is rendered to the user
    _food.FoodPlaced();

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      if(_gameMode == 1)
        renderer.UpdateWindowTitle(score1, frame_count);
      else
        renderer.UpdateWindowTitle(score1,score2,frame_count);
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

void Game::PlaceFood() 
{
  int x, y;
  _food.GenerateNewFood();
  while (true) 
  {
    x = _food.GetFoodLocation().x;
    y = _food.GetFoodLocation().y;

    // Check that the location is not occupied by a snake item before placing
    // food.
    if(_gameMode == 1)
    {
      if(snake1->SnakeCell(x,y))
      _food.GenerateNewFoodLocation();
      else  
        return;
    }
    else
    {
      if(snake1->SnakeCell(x,y) || snake2->SnakeCell(x,y))
        _food.GenerateNewFoodLocation();
      else  
        return;
    }
  }
}

void Game::Update() {

  if(!CheckIfSnakesAlive())
    return;

  UpdateSnakes();

  if(CheckIfFoodExpired())
    return;  

  CheckIfSnakesConsumedFood();
}

int Game::GetPlayer1Score() const { return score1; }
int Game::GetPlayer2Score() const { return score2; }
int Game::GetSize() const { return snake1->size; }

void Game::UpdateSnakes()
{
  if(snake1->alive)
    snake1->Update();

  if(_gameMode == 2)
  {
    if(snake2->alive)
      snake2->Update();
  }
    
}

bool Game::CheckIfFoodExpired()
{
  if(_gameMode == 1)
  {
    if(_food.HasFoodExpired() && snake1->isSnakeActive)
    {
      PlaceFood();
      return true;
    }  
  }
  else
  {
    if(_food.HasFoodExpired() && (snake1->isSnakeActive || snake2->isSnakeActive))
    {
      PlaceFood();
      return true;
    }
  }
  return false;
}

bool Game::CheckIfSnakesAlive()
{
  if(_gameMode == 1)
    return snake1->alive;
  return (snake1->alive || snake2->alive);
}

void Game::CheckIfSnakesConsumedFood()
{
  // check if Snake1 has consumed food
  int snake_x = static_cast<int>(snake1->head_x);
  int snake_y = static_cast<int>(snake1->head_y);

  // Check if there's food over here
  if (_food.GetFoodLocation().x == snake_x && _food.GetFoodLocation().y == snake_y)
  {
    snake1->SetFoodTypeConsumed(_food.GetFoodType());
    _food.FoodConsumed();
    PlaceFood();   
    snake1->GrowBody();
  }
  score1 = snake1->size;

  if(_gameMode == 2)
  {
        // check if Snake1 has consumed food
    snake_x = static_cast<int>(snake2->head_x);
    snake_y = static_cast<int>(snake2->head_y);

    // Check if there's food over here
    if (_food.GetFoodLocation().x == snake_x && _food.GetFoodLocation().y == snake_y)
    {
      snake2->SetFoodTypeConsumed(_food.GetFoodType());
      _food.FoodConsumed();
      PlaceFood();   
      snake2->GrowBody();
    }
    score2 = snake2->size;
  }
  else
    return;

}