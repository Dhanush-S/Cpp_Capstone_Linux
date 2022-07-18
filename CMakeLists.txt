cmake_minimum_required(VERSION 3.7)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(SDL2Test)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

# set(SDL2_INCLUDE_DIR C:/Dhanush/Project/Nanodegree_Workspace/SDL2/SDL2-devel-2.0.22-mingw.tar/SDL2-devel-2.0.22-mingw/SDL2-2.0.22/x86_64-w64-mingw32/include/SDL2)
# set(SDL2_LIBRARY C:/Dhanush/Project/Nanodegree_Workspace/SDL2/SDL2-devel-2.0.22-mingw.tar/SDL2-devel-2.0.22-mingw/SDL2-2.0.22/x86_64-w64-mingw32/lib)
# set(SDL_DIR C:/Dhanush/Project/Nanodegree_Workspace/SDL2/SDL2-devel-2.0.22-mingw.tar/SDL2-devel-2.0.22-mingw/SDL2-2.0.22/x86_64-w64-mingw32/lib/cmake/SDL2)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS} src)

add_executable(SnakeGame src/main.cpp src/game.cpp src/controller.cpp src/renderer.cpp src/snake.cpp)
string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES)
target_link_libraries(SnakeGame ${SDL2_LIBRARIES})
