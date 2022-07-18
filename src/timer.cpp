#include "Timer.h"
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
        while(!_stopThread && localTime < duration)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
            localTime = localTime + 100;
            std::cout << "Thread running.." << std::endl;
        }
        if(!_food->HasFoodExpired())
        {
            std::cout << "----------------------Timer expired----------------------" << std::endl;
            _food->FoodTimerExpired();
        }
    });
}

void Timer::Stop()
{
    if(this->_isTimerRunning)
    {
        this->_isTimerRunning = false;
        this->_stopThread = true;
        Reset();
    }
}

void Timer::Reset()
{
    std::cout << "----------------------Thread stopped----------------------" << std::endl;
    if(this->_thread.joinable())
        this->_thread.join();
        // this->_thread.detach();
}

bool Timer::IsTimerRunning()
{
    return _isTimerRunning; 
}

Timer::~Timer()
{
    Stop();
}