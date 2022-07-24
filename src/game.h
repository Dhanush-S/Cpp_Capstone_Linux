#ifndef GAME_H
#define GAME_H

#include <random>
// #include "SDL.h"
#include "food.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "SDL2/SDL.h"


class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height, int game_mode);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetPlayer1Score() const;
  int GetPlayer2Score() const;
  int GetSize() const;

 private:
  std::unique_ptr<Snake> snake1, snake2;
  // Snake snake;
  SDL_Point food;
  Food _food;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score1{0};
  int score2{0};
  int _gameMode;
  void PlaceFood();
  void Update();
  void UpdateSnakes();
  bool CheckIfFoodExpired();
  bool CheckIfSnakesAlive();
  void CheckIfSnakesConsumedFood();
};

#endif