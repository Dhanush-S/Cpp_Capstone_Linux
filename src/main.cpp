#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
// #include "Timer.h"


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

int main(int argc, char* argv[]) {

  int choice = GameModeSelection() ;

  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}