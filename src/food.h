#ifndef FOOD_H
#define FOOD_H

#include "SDL2/SDL.h"
#include <random>
#include <future>
#include <mutex>
#include "timer.h"

enum FoodType {GOOD, BAD, POWER, SLOW};
class Food
{
    public:
        Food(int gridWitdh, int gridHeight);
        void GenerateNewFood();
        void GenerateNewFoodLocation();
        SDL_Point GetFoodLocation();
        bool HasFoodExpired();
        void FoodPlaced();
        FoodType GetFoodType();
        void FoodConsumed();
        void FoodTimerExpired();

    private :
        // assign the type of food
        FoodType _foodType;
        // duration of time where food is retained
        int _foodDuration;
        // location in the grid
        SDL_Point _foodLocation;
        // has the _foodDuration timer expired
        bool _durationExpired;
        // mutex object to access critical resource
        std::mutex _mutex;
        // timer object to track duration of the food
        Timer _timer;

        //moved from game.h
        std::random_device dev;
        std::mt19937 engine;
        std::uniform_int_distribution<int> random_w;
        std::uniform_int_distribution<int> random_h;
        std::uniform_int_distribution<int> random_foodType;
        std::uniform_int_distribution<int> random_duration;
};

#endif