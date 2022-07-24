#ifndef SNAKE_H
#define SNAKE_H

#include <vector>
// #include "SDL.h"
// #include "SDL2/SDL.h"
#include "../src/include/SDL2/SDL.h"
#include "food.h"

class Snake {
 public:
  enum class Direction { kUp, kDown, kLeft, kRight };

  /*
  * constructor
  * @param grid_width max width of the grid
  * @param grid_height max height of the grid
  * @param head_x x-location of the snake head
  * @param head_y y-location of the snake head
  */
  Snake(int grid_width, int grid_height, int head_x, int head_y)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_x),
        head_y(head_y), isSnakeActive(true){}

  void Update();

  void GrowBody();

  /*
  * @param int x x-location of food to compare
  * @param int y y-location of food to compare
  */
  bool SnakeCell(int x, int y);

  // check if gameplay is active or not
  bool isSnakeActive;

  // direction of the snake
  Direction direction = Direction::kUp;

  // speed of the snake
  float speed{0.1f};

  // size of the snake
  int size{1};

  // snake living status
  bool alive{true};

  // x position of head
  float head_x;

  // y position of head
  float head_y;

  // body of the snake
  std::vector<SDL_Point> body;

  /*
  * type of food consumed
  * @param foodType type of food consumed by snake
  */
  void SetFoodTypeConsumed(FoodType foodType);

 private:

  // update head of the snake based on User input
  void UpdateHead();

  /*
  * update head relative to current head position
  * @param deltaX x-location that should be added to current head x position
  * @param deltaX y-location that should be added to current head y position 
  */
  void UpdateHead(int deltaX, int deltaY);

  /*
  * update body of the snake based on food consumed
  * @param current_cell current-location of snake head
  * @param prev_cell previous-location of snake head 
  */
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);

  // Wrap the Snake around to the beginning if going off of the screen.
  void WrapSnakeHead();
  
  // whether food is consumed and thus snake needs to grow
  bool growing{false};

  // width of the grid
  int grid_width;

  // height of the grid
  int grid_height;

  // type of food consumed by snake
  FoodType _foodTypeConsumed{FoodType::GOOD};

  /*
  * increase bodysize of the snake if special food is consumed
  * @param bodySize body size by which snake's body should be increased
  */
  void GrowBody(int bodySize);

  // update body and score based on the food consumed
  void ProcessFoodConsumed();
};

#endif