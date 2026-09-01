#include <bits/stdc++.h>

#include <chrono>

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
