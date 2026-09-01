#include "timer.hpp"

Timer::Timer(string _name) : name(_name), start(chrono::steady_clock::now()), running(true) {}

Timer::~Timer() {
	if (running) {
		stop();
	}
}

void Timer::elapsed() {
	auto now = chrono::steady_clock::now();
	chrono::duration<double, milli> duration = now - start;
	cout << "[" << name << "] levou " << duration.count() << " milissegundos (ms) ate aqui."
		 << endl;
}

void Timer::stop() {
	auto end = chrono::steady_clock::now();
	chrono::duration<double, milli> duration = end - start;
	cout << "\"" << name << "\" levou " << duration.count() << " milissegundos (ms) para rodar."
		 << endl;
	running = false;
}
