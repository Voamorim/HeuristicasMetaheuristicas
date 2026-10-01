#ifndef SA_TSP_HPP
#define SA_TSP_HPP

#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "graph.hpp"
#include "timer.hpp"
#include "tsp.hpp"
#include "utils.hpp"

using namespace std;

pair<int, vector<int>> simulatedAnnealingTSP(vector<int> curr_solution, float temperature,
											 const float alpha, const int sa, Graph* graph,
											 mt19937& gen);

#endif
