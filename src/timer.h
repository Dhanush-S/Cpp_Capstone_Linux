#ifndef TIMER_H
#define TIMER_H

#include <thread>
#include <mutex>
#include <iostream>

// forward decleration
class Food;

class Timer
{
    private:
        // thread object to count down the timeout
        std::thread _thread;
        // mutex object to access critical resource
        std::mutex _mutex;
        // boolean to store if timer is running or not
        bool _isTimerRunning;

    public:
        // destructor
        ~Timer();
        // boolean to check if thread needs to be stopped or not
        static bool _stopThread;
        // reference to food object
        Food* _food;
        
        /*
        * start the timer
        * @param timeDuration duration of the timer
        * @param food point to food object used to inform food object about time expiration
        */
        void Start(int timeDuration, Food *food);

        // stop the timer
        void Stop();

        // reset the timer i.e. wait for thread to finish
        void Reset();

        // returns whether the timer thread is running or not
        bool IsTimerRunning();
};

#endif