#include "timer.h"
#include "food.h"

bool Timer::_stopThread = false;

void Timer::Start(int duration, Food *food)
{
    this->_food = food;
    this->_isTimerRunning = true;
    this->_stopThread = false;
    duration = duration*1000;
    this->_thread = std::thread([=]()mutable{
        int localTime = 0;
        
        bool stopThread = false;
        while(!_stopThread && localTime < duration)
        {
            std::unique_lock<std::mutex> unqGuard(_mutex);
            stopThread = _stopThread;
            unqGuard.unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            localTime = localTime + 100;
        }
        if(!_food->HasFoodExpired())
        {
            _food->FoodTimerExpired();
        }
    });
}

void Timer::Stop()
{
    if(this->_isTimerRunning)
    {
        this->_isTimerRunning = false;
        std::unique_lock<std::mutex> unqGuard(_mutex);
        this->_stopThread = true;
        unqGuard.unlock();
        Reset();
    }
}

void Timer::Reset()
{
    if(this->_thread.joinable())
        this->_thread.join();
}

bool Timer::IsTimerRunning()
{
    return _isTimerRunning; 
}

Timer::~Timer()
{
    Stop();
}