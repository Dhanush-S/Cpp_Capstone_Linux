#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

// determine game play type - single or two player mode
int GameModeSelection()
{
  int choice = 0;

  while(1)
  {
  std::cout << "Select Game Mode or two player game" << std::endl;
  std::cout << "Press 1 for  single player" << std::endl;
  std::cout << "Press 2 for  two players" << std::endl;
  std::cin >> choice;

  if(choice != 1 && choice != 2)
    std::cout << "Invalid selection, please select valid option" << std::endl;
  else
    return choice;
  }
}

// print scores at the end of the game
void PrintScore(int score1, int score2, int gameMode)
{
  if(gameMode == 1)
  {
    std::cout << "-----------------------------Results-----------------------------" << std::endl;
    std::cout << "Player score = " << score1 << std::endl;
    std::cout << "-----------------------------------------------------------------" << std::endl;
  }
  else
  {
    std::cout << "-----------------------------Results-----------------------------" << std::endl;
    std::cout << "Player 1 score = " << score1 << std::endl << "Player 2 score = " << score2 << std::endl;
    score1 > score2 ? std::cout << "Winner : Player 1\n" : score1 < score2 ? std::cout << "Winner : Player 2\n" : std::cout << "Game is a Draw\n";
    std::cout << "-----------------------------------------------------------------" << std::endl;

  }
}

// print game mode options and instructions
void PrintGameInstructions(int gameMode)
{
  std::cout << "-----------------------------Player 1 Controls-----------------------------" << std::endl;
  std::cout << "Top   : Up arrow key" << std::endl; 
  std::cout << "Down  : Down arrow key" << std::endl; 
  std::cout << "Left  : Left arrow key" << std::endl; 
  std::cout << "Right : Right arrow key" << std::endl;
  std::cout << "Player color : Blue" << std::endl << std::endl;

  if(gameMode == 2)
  {
    std::cout << "-----------------------------Player 2 Controls-----------------------------" << std::endl;
    std::cout << "Top   : W key" << std::endl; 
    std::cout << "Down  : S key" << std::endl; 
    std::cout << "Left  : A key" << std::endl; 
    std::cout << "Right : D key" << std::endl;
    std::cout << "Player color : Yellow" << std::endl << std::endl;

    std::cout << "Game will end if both player's snake is dead or game is closed" << std::endl;
  }

  std::cout << "---------------------------------Game Details---------------------------------" << std::endl;
  std::cout << "Different types of food will be provided which have its buffs and nerfs" << std::endl;
  std::cout << "Green : Good food, normal speed boost + 1 increase in score " << std::endl;
  std::cout << "Red   : Bad food, no speed boost + no increase in score " << std::endl;
  std::cout << "Blue  : Power food, increased speed boost + 2 increase in score " << std::endl;
  std::cout << "Pink  : Slow food, low speed boost + 1 increase in score " << std::endl << std::endl;
  std::cout << "Every food will have a random timer between 5 and 10sec. Once expired, food will be replaced with new food" << std::endl;

  std::cout << "Press spacebar at any point in the game to pause/resume" << std::endl;
  std::cout << "Game has begun, enjoy!!" << std::endl;
}

// entry point
int main(int argc, char* argv[]) {

  int choice = GameModeSelection() ;
  PrintGameInstructions(choice);

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};
  
  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight, choice);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  PrintScore(game.GetPlayer1Score(), game.GetPlayer2Score(), choice);
  return 0;
}