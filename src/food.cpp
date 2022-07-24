#include "food.h"

// constructor to create a new GOOD food object
Food::Food(int gridWidth, int gridHeight ) : _foodType(FoodType::GOOD), 
                                             _foodDuration(5), 
                                             _durationExpired(false),
                                             engine(dev()),
                                             random_w(0, static_cast<int>(gridWidth - 1)),
                                             random_h(0, static_cast<int>(gridHeight - 1)),
                                             random_foodType(0,3),
                                             random_duration(5,10)
                                             {
    _foodLocation.x = random_w(engine);
    _foodLocation.y = random_h(engine);
}

void Food::GenerateNewFood()
{
    // _durationExpired is the critical resource used in order to check if food is to be used or not in game.cpp
    std::unique_lock<std::mutex> unqGuard(_mutex);
    _durationExpired = false;
    unqGuard.unlock();

    _timer.Stop();

    _foodType = FoodType(random_foodType(engine));
    _foodDuration = random_duration(engine);
    _foodLocation.x = random_w(engine);
    _foodLocation.y = random_h(engine);
}

void Food::GenerateNewFoodLocation()
{
    _foodLocation.x = random_w(engine);
    _foodLocation.y = random_h(engine);
}

SDL_Point Food::GetFoodLocation()
{
    // send by value 
    return _foodLocation;
}

FoodType Food::GetFoodType()
{
    return _foodType;
}

bool Food::HasFoodExpired()
{
    std::lock_guard<std::mutex> lckGuard(_mutex);
    return _durationExpired;
}

void Food::FoodPlaced()
{
    if(!_timer.IsTimerRunning())
    {
        _timer.Start(_foodDuration, this);
    }
}

void Food::FoodConsumed()
{
    std::unique_lock<std::mutex> unqGuard(_mutex);
    _durationExpired = false;
    unqGuard.unlock();

    _timer.Stop();    
}

void Food::FoodTimerExpired()
{
    std::lock_guard<std::mutex> lckGuard(_mutex);
    _durationExpired = true;
}

