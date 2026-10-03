#ifndef GRASP_TSP_HPP
#define GRASP_TSP_HPP

#include <algorithm>
#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

#include "graph.hpp"
#include "tsp.hpp"
#include "utils.hpp"

pair<int, vector<int>> grasp(Graph* graph, const int grasp_max, const double alpha,
                             const int max_iterations_local_search, mt19937& gen);

#endif
