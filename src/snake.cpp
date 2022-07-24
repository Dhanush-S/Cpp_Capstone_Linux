#include "snake.h"
#include <cmath>
#include <iostream>

void Snake::Update() 
{
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new cell
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  WrapSnakeHead();
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } 
  else {
    growing = false;

    ProcessFoodConsumed();
    
    // capture updated head cell
    current_head_cell.x = static_cast<int>(head_x);
    current_head_cell.y = static_cast<int>(head_y);
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

void Snake::SetFoodTypeConsumed(FoodType foodType)
{
  _foodTypeConsumed = foodType;
}

void Snake::ProcessFoodConsumed()
{
  switch(_foodTypeConsumed)
  {
    case FoodType::GOOD:
          size++;
          speed += 0.02;
          break;
    case FoodType::BAD:
          body.erase(body.begin());
          break;
    case FoodType::POWER:
          size+=2;
          GrowBody(1);
          speed += 0.04;
          break;
    case FoodType::SLOW:
          size++;
          speed += 0.01;
          break;
    default: break;
  }
}

void Snake::GrowBody(int bodySize)
{
  for(int i=0; i<bodySize; i++)
  {
    if(body.size() == 1)
    {
      SDL_Point point;
      switch (direction)
      {
      case Direction::kDown :
        point.x = body.at(0).x;
        point.y = body.at(0).y + 1;
        UpdateHead(0,1);
        break;
      case Direction::kUp :
        point.x = body.at(0).x;
        point.y = body.at(0).y - 1;
        UpdateHead(0,-1);
        break;
      case Direction::kLeft :
        point.x = body.at(0).x - 1;
        point.y = body.at(0).y;
        UpdateHead(-1,0);
        break;
      case Direction::kRight :
        point.x = body.at(0).x + 1;
        point.y = body.at(0).y;
        UpdateHead(1,0);
        break;
      default:
        break;
      }
      body.insert(body.begin(),point);
    }
    else
    {
      SDL_Point point;
      if( body.at(0).x == body.at(1).x)
      {
        // grow body in y-direction   
        point.x = body.at(0).x;
        body.at(0).y > body.at(1).y ? point.y = body.at(0).y+1 :  point.y = body.at(0).y-1;
       }
      else
      {
        // grow body in x-direction
        point.y = body.at(0).y;
        body.at(0).x > body.at(1).x ? point.x = body.at(0).x+1 :  point.x = body.at(0).x-1;
      }
      body.insert(body.begin(),point);
    }
  }
}

void Snake::UpdateHead(int deltaX, int deltaY)
{
  head_x += deltaX;
  head_y += deltaY;

  WrapSnakeHead();
}

void Snake::WrapSnakeHead()
{
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}