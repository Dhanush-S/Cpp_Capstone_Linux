#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <mutex>
#include <iostream>
class Food;

class Timer
{
    std::thread _thread;
    std::mutex _mutex;
    bool _isTimerRunning;

    public:
    ~Timer();
    static bool _stopThread;
    Food* _food;
    void Start(int timeDuration, Food *food);
    void Stop();
    void Reset();
    bool IsTimerRunning();
};

#endif