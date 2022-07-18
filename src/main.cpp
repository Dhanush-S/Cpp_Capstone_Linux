#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"
// #include "Timer.h"

int main(int argc, char* argv[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  // Timer timer;

  // std::cout << "Timer started" << std::endl;
  // timer.Start(5);

  // int i = 0;
  // while(i < 100)
  // {
  //   std::cout << "Main working.." << std::endl;
  //   std::this_thread::sleep_for(std::chrono::milliseconds(100));
  //   i++;
  // }
  
  // timer.Stop();
  // std::cout << "Timer stopped" << std::endl;

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  return 0;
}