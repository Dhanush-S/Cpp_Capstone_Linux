# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.

## Rubrics

### README

#### A README with instructions is included with the project
- Refer to section Basic Build Instructions for building and running the project
- Refer to section Dependencies for running the project locally

#### The README indicates which project is chosen.
- Snake game is chose as base project and additional features are introduced to the game
- Additional features include:
  - 1 player mode or 2 player mode
  - Different types of food introduced (Good, Bad, Power, Slow)
  - Everytime a food is placed, a random timer between 5-10sec is associated with it
  - Once the timer of the food expires, a new food is placed
  - User can pause and resume the game at any point in time using 'space bar'
  
##### Project Structure 
- main.cpp : entry point of the game
- controller.h and controller.cpp : class to receive input from user required for the operation of the game
- game.h and game.cpp : class which handles operation of the game and also updates game state and different game objects (snake and food). Owns game objects Snake and Food
- renderer.h and renderer.cpp : class to render the different game objects using SDL
- snake.h and snake.cpp : class for the snake object of the game
- food.h and food.cpp : new class introduced which produces different types of food each associated with a timer. On expiration of the timer, food will be replaced by the game class.
- timer.h and timer.cpp : new timer class introduced which will be used by food class for maintaining the timer of the food. Once the timer is expired, it informs the food class about the expiration which in turn will be used by game class.

#### Program output
- Possibility to play single player game mode or 2 player game mode 
- Below gifs show the gameplay

##### 1 Player Game Mode

<img src="1_Player_GameMode.gif"/>

##### 2 Player Game Mode

<img src="2_Player_GameMode.gif"/>

### Compiling and Testing 
- The program can be compiled with the instructions in the section Basic Build Instructions

### Rubric Points Covered (11)

#### Loops, Functions, I/O

##### The project demonstrates an understanding of C++ functions and control structures.
- A variety of control structures are used throughout the project. Following lines show a few examples.
- In file timer.cpp : inside the function Timer::Start(), we can see usage of 'if' and 'while' in line 25 and line 16 respectively. 
- In file snake.cpp : inside the function Snake::ProcessFoodConsumed(), we can see the usage of 'switch' case in line 93.

##### The project accepts user input and processes the input.
- In main.cpp : inside the function GameModeSelection(), the type of game mode is requested as input from user to start the game in line 16.
- In controller.cpp : inside the function Controller::HandleInput(), key inputs from user 'w', 's', 'a', 'd', 'space' is continuously read starting from lines 42 through line 62.

#### Object Oriented Programming

##### The project uses Object Oriented Programming techniques.
- Oops concept is used through out the project.
- Some examples are food.h and timer.h files

##### Classes use appropriate access specifiers for class members.
- In food.h, line 15 onwards indicates variables and methods under public specifier and line 50 onwards indicates variables and methods under private access specifier
- In timer.h, line 13 onwards indicates variables under private specifier and line 21 onwards indicates variables and methods under public access specifier

##### Class constructors utilize member initialization lists.
- Some examples include: 
  - In food.cpp, in line 4
  - In snake.h, in line 21
  
##### Classes encapsulate behavior.
- Some examples include:
  - In food.h, member variables are exposed only through 'set' functions. Data members are marked private and thus encapsulated (lines 15 and 50).
  - In timer.h, member variables are exposed only through 'set' functions. Data members are marked private and thus encapsulated (lines 13 and 21).

##### Overloaded functions allow the same function to operate on different parameters.
- In snake.h (lines 70 and 77) and snake.cpp (llines 22 and 169), we can see same function name but with different parameters for the function Snake::UpdateHead.  

#### Memory Management

##### The project uses destructors appropriately.
- In timer.cpp, to reset the timer state and destory the wait thread in line 55

##### The project uses smart pointers instead of raw pointers.
- In game.h(line 41) and game.cpp(line 12 and 16), the snake objects are declared and later initialized as unique_ptr. 

#### Concurrency

##### The project uses multithreading.
- In timer.cpp, inside the function Timer::Start(), a new thread is created (line 12)

##### A mutex or lock is used in the project.
- In timer.cpp, inside the functions: Timer::Start() (line 18), Timer::Stop() (line 37), unique_lock is used to protect the data
- In food.cpp, inside the functions: Food::GenerateNewFood() (line 20), Food::HasFoodExpired (line 49), Food::FoodConsumed (line 63) and Food::FoodTimerExpired (line 74)

## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg
