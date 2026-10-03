#ifndef GRASP_BACKPACK_HPP
#define GRASP_BACKPACK_HPP

#include <algorithm>
#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

#include "backpack.hpp"
#include "utils.hpp"

using namespace std;

pair<int, vector<bool>> graspBackpack(Backpack* backpack, const int grasp_max, const double alpha,
                                      const int max_iterations_local_search, mt19937& gen);

#endif
