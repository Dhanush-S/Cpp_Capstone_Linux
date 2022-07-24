#include "game.h"
#include <iostream>
// #include "SDL.h"
#include "SDL2/SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, int game_mode)
    : _gameMode(game_mode),
      _food(grid_width,grid_height)
{ 

  // allocate memory for snake1
  _snake1 = std::make_unique<Snake>(grid_width, grid_height, (grid_width-1)/2, (grid_height-1)/2); 

  // allocate memory to snake2 only if game_mode is 2 player      
  if(game_mode == 2)
    _snake2 = std::make_unique<Snake>(grid_width, grid_height, (grid_width+1)/2, (grid_height+1)/2);

  // place a food in the grid
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
      controller.HandleInput(running, _snake1.get(), nullptr);
      
      // update only if the game is not paused
      if(_snake1->isSnakeActive)
        Update();
      
      // render
      renderer.Render(_snake1.get(), nullptr, _food);
    }
    else
    {
      controller.HandleInput(running, _snake1.get(), _snake2.get());
      
      // update only if the game is not paused
      if(_snake1->isSnakeActive || _snake2->isSnakeActive)
        Update();
      
      renderer.Render(_snake1.get(), _snake2.get(), _food);
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
        renderer.UpdateWindowTitle(_score1, frame_count);
      else
        renderer.UpdateWindowTitle(_score1,_score2,frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    /* 
    *  If the time for this frame is too small (i.e. frame_duration is
    *  smaller than the target ms_per_frame), delay the loop to
    *  achieve the correct frame rate.
    */ 
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

    // Check that the location is not occupied by a snake item before placing food
    if(_gameMode == 1)
    {
      if(_snake1->SnakeCell(x,y))
      _food.GenerateNewFoodLocation();
      else  
        return;
    }
    else
    {
      if(_snake1->SnakeCell(x,y) || _snake2->SnakeCell(x,y))
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

int Game::GetPlayer1Score() const { return _score1; }
int Game::GetPlayer2Score() const { return _score2; }

void Game::UpdateSnakes()
{
  // update snake if it is alive
  if(_snake1->alive)
    _snake1->Update();

  if(_gameMode == 2)
  {
    // update snake if it is alive
    if(_snake2->alive)
      _snake2->Update();
  }
    
}

bool Game::CheckIfFoodExpired()
{
  if(_gameMode == 1)
  {
    // place a new food if food timer has expired and game is not paused
    if(_food.HasFoodExpired() && _snake1->isSnakeActive)
    {
      PlaceFood();
      return true;
    }  
  }
  else
  {
    // place a new food if food timer has expired and game is not paused
    if(_food.HasFoodExpired() && (_snake1->isSnakeActive || _snake2->isSnakeActive))
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
    return _snake1->alive;
  return (_snake1->alive || _snake2->alive);
}

void Game::CheckIfSnakesConsumedFood()
{
  // check if Snake1 has consumed food
  int snake_x = static_cast<int>(_snake1->head_x);
  int snake_y = static_cast<int>(_snake1->head_y);

  /* 
  * Check if there's food over here
  * if consumed, place a new food, inform snake about food type and update snake's score 
  */
  if (_food.GetFoodLocation().x == snake_x && _food.GetFoodLocation().y == snake_y)
  {
    _snake1->SetFoodTypeConsumed(_food.GetFoodType());
    _food.FoodConsumed();
    PlaceFood();   
    _snake1->GrowBody();
  }
  _score1 = _snake1->size;

  if(_gameMode == 2)
  {
    // check if Snake2 has consumed food
    snake_x = static_cast<int>(_snake2->head_x);
    snake_y = static_cast<int>(_snake2->head_y);

    // Check if there's food over here
    if (_food.GetFoodLocation().x == snake_x && _food.GetFoodLocation().y == snake_y)
    {
      _snake2->SetFoodTypeConsumed(_food.GetFoodType());
      _food.FoodConsumed();
      PlaceFood();   
      _snake2->GrowBody();
    }
    _score2 = _snake2->size;
  }
  else
    return;

}