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

  Snake(int grid_width, int grid_height, int head_x, int head_y)
      : grid_width(grid_width),
        grid_height(grid_height),
        head_x(head_x),
        head_y(head_y), isSnakeActive(true){}

  void Update();

  void GrowBody();
  bool SnakeCell(int x, int y);

  bool isSnakeActive;

  Direction direction = Direction::kUp;

  float speed{0.1f};
  int size{1};
  bool alive{true};
  float head_x;
  float head_y;
  std::vector<SDL_Point> body;
  void SetFoodTypeConsumed(FoodType foodType);

 private:
  void UpdateHead();
  void UpdateHead(int deltaX, int deltaY);
  void UpdateBody(SDL_Point &current_cell, SDL_Point &prev_cell);
  void WrapSnakeHead();
  
  bool growing{false};
  int grid_width;
  int grid_height;
  FoodType _foodTypeConsumed{FoodType::GOOD};
  void GrowBody(int bodySize);
  void ProcessFoodConsumed();
};

#endif