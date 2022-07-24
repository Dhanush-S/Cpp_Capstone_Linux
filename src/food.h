#ifndef FOOD_H
#define FOOD_H

#include "SDL.h"
#include <random>
#include <future>
#include <mutex>
#include "timer.h"

// types of food
enum FoodType {GOOD, BAD, POWER, SLOW};

class Food
{
    public:
        /*
        *   constructor
        *   @param gridWidth max width of the grid where food can be placed
        *   @param gridHeight max height of the grid where food can be placed 
        */
        Food(int gridWitdh, int gridHeight);

        /*
        *   generates a new random food type in a random location within grid width and grid height
        *   generated food will also have a random timer between 5-10 seconds set
        */
        void GenerateNewFood();
     
        //  generates new location for the food type
        void GenerateNewFoodLocation();
        
        // returns the location of the food within grid width and grid height
        SDL_Point GetFoodLocation();

        // return whether timer for the food has expired or not
        bool HasFoodExpired();

        // starts the timer attached to the food once the food is placed in the grid
        void FoodPlaced();

        // returns the type of food
        FoodType GetFoodType();

        // stops the timer once the food is consumed
        void FoodConsumed();

        // called by timer call to inform timer expiration of food
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

        // used for random x location
        std::uniform_int_distribution<int> random_w;

        // used for random y location
        std::uniform_int_distribution<int> random_h;

        // used for random food type
        std::uniform_int_distribution<int> random_foodType;

        // used for random duration for food between 5 - 10seconds
        std::uniform_int_distribution<int> random_duration;
};

#endif