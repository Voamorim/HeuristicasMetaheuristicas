#ifndef ILS_TSP
#define ILS_TSP

#include <random>
#include <algorithm>
#include <climits>
#include <iostream>
#include <tuple>
#include <vector>

using namespace std;

pair<int, vector<int>> ilsTsp(Graph* graph, vector<int> solution, const int max_iterations, const int max_iterations_without_improvement, const int max_iterations_local_search, mt19937& gen);

#endif
