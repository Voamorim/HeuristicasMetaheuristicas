#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>
#include <iostream>
#include <string>

using namespace std;

class Timer {
   public:
    void stop();
    void elapsed();

    Timer(string _name);
    ~Timer();

   private:
    string name;
    bool running;
    chrono::steady_clock::time_point start;
};

#endif
