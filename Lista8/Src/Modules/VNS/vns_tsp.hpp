#ifndef VNS_TSP
#define VNS_TSP

#include "utils.hpp"
#include "graph.hpp"
#include "tsp.hpp"
#include "timer.hpp"

#include <random>
#include <algorithm>
#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

pair<int, vector<int>> vnsTSP(Graph* graph, vector<int> solution, const int VNSMax, const int VMax, const int max_iterations_local_search, mt19937& gen, Timer& timer);

#endif
