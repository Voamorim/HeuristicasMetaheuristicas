#ifndef TSP_HPP
#define TSP_HPP

#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

#include "graph.hpp"
#include "utils.hpp"

using namespace std;

vector<int> getRandomSolutionTSP(const int n, mt19937& gen);

int objectiveFunctionTSP(const vector<int>& solution, Graph* graph);

void printBestSolutionTSP(const vector<int>& best_solution, const int best_fo);

#endif
