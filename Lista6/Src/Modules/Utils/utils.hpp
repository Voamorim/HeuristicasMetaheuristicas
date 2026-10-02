#ifndef UTILS_HPP
#define UTILS_HPP

#include <random>

using namespace std;

int getRandomInteger(int l, int r, mt19937& gen);
float getRandomFloat(mt19937& gen);

#endif
