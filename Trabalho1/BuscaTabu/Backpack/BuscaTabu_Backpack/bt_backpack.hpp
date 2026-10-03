#ifndef BT_BACKPACK_HPP
#define BT_BACKPACK_HPP

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

#include "backpack.hpp"
#include "timer.hpp"

using namespace std;

pair<long long, vector<bool>> tabuSearchBackpack(vector<bool> solution, long long fo,
                                                 const int max_iterations,
                                                 const int max_iterations_without_improvement,
                                                 const int ttl_tabu_list, Backpack* backpack,
                                                 Timer& timer);

#endif
