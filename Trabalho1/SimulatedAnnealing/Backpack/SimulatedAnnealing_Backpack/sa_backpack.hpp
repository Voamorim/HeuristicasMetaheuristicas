#ifndef SA_BACKPACK_HPP
#define SA_BACKPACK_HPP

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <tuple>
#include <vector>

#include "backpack.hpp"
#include "timer.hpp"
#include "utils.hpp"

using namespace std;

pair<int, vector<bool>> simulatedAnnealingBackpack(vector<bool> curr_solution, double temperature,
                                                   const double alpha, const int sa,
                                                   Backpack* backpack, mt19937& gen);

#endif
