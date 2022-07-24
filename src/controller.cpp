#include "controller.h"
#include <iostream>
// #include "SDL.h"
#include "SDL2/SDL.h"
#include "snake.h"

// update direction input of the snake
void Controller::ChangeDirection(Snake *snake, Snake::Direction input,
                                 Snake::Direction opposite) const {
  if (snake->direction != opposite || snake->size == 1) snake->direction = input;
  return;
}

// handle inputs from 2 players
void Controller::HandleInput(bool &running, Snake *snake1, Snake *snake2) const {
  SDL_Event e;
  while (SDL_PollEvent(&e)) {
    if (e.type == SDL_QUIT) {
      running = false;
    } else if (e.type == SDL_KEYDOWN) {
      switch (e.key.keysym.sym) {
        case SDLK_UP:
          ChangeDirection(snake1, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;
          
        case SDLK_DOWN:
          ChangeDirection(snake1, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;

        case SDLK_LEFT:
          ChangeDirection(snake1, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;

        case SDLK_RIGHT:
          ChangeDirection(snake1, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        
        case SDLK_w:
          if(snake2 != nullptr)
          ChangeDirection(snake2, Snake::Direction::kUp,
                          Snake::Direction::kDown);
          break;
        case SDLK_s:
          if(snake2 != nullptr)
          ChangeDirection(snake2, Snake::Direction::kDown,
                          Snake::Direction::kUp);
          break;
        case SDLK_a:
          if(snake2 != nullptr)
          ChangeDirection(snake2, Snake::Direction::kLeft,
                          Snake::Direction::kRight);
          break;
        case SDLK_d:
          if(snake2 != nullptr)
          ChangeDirection(snake2, Snake::Direction::kRight,
                          Snake::Direction::kLeft);
          break;
        case SDLK_SPACE:
          snake1->isSnakeActive ? snake1->isSnakeActive = false : snake1->isSnakeActive = true;
          if(snake2 != nullptr)
            snake2->isSnakeActive ? snake2->isSnakeActive = false : snake2->isSnakeActive = true;
          break;
      }
    }
  }
}