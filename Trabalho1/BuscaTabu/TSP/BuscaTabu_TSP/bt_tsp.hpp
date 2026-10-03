#ifndef BT_TSP_HPP
#define BT_TSP_HPP

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "graph.hpp"
#include "timer.hpp"
#include "tsp.hpp"
#include "utils.hpp"

using namespace std;

pair<int, vector<int>> tabuSearchTSP(vector<int> curr_solution, long long fo, Graph* graph,
                                     const int ttl_tabu_list, const int max_iterations,
                                     const int max_iterations_without_improvement);

#endif
