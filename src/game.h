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

    /*
    *   constructor
    *   @param grid_width max width of the grid where food can be placed
    *   @param grid_height max height of the grid where food can be placed 
    *   @param game_mode single player of two player game mode
    */
    Game(std::size_t grid_width, std::size_t grid_height, int game_mode);

    /*
    *   @param controller input handler to receive player inputs
    *   @param renderer renderer object to render different objects using SDL
    *   @param target_frame_duration to have desired fps 
    */
    void Run(Controller const &controller, Renderer &renderer,
            std::size_t target_frame_duration);

    // returns player 1 score
    int GetPlayer1Score() const;

    // returns player 2 score
    int GetPlayer2Score() const;

 private:

    // unique_ptr to two snake objects
    std::unique_ptr<Snake> _snake1, _snake2;

    // food object
    Food _food;

    // variable for tracking player 1 score
    int _score1{0};

    // variable for tracking player 2 score
    int _score2{0};

    // game play mode - 1 player or 2 player
    int _gameMode;

    // place a new food in the gameplay within the grid dimensions
    void PlaceFood();

    // update the game states and objects
    void Update();

    // update snake objects
    void UpdateSnakes();

    /*
    * check if food duration has expired
    * if duration has expirted, place a new food 
    */
    bool CheckIfFoodExpired();

    // returns true if a snake is alive 
    bool CheckIfSnakesAlive();

    /*
    * check if any of the snake has consumed food
    * if food is consumed, place a new food and update score of the corresponding player
    */
    void CheckIfSnakesConsumedFood();
};

#endif