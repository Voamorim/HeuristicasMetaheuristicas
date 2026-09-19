#ifndef TSP_HPP
#define TSP_HPP

#include <vector>
#include <iostream>
#include <random>

#include "graph.hpp"
#include "utils.hpp"

using namespace std;

vector<int> getRandomSolutionTSP(const int n, mt19937& gen);

int objetiveFunctionTSP(const vector<int>& solution, Graph* graph);

void printBestSolutionTSP(const vector<int> &best_solution, const int best_fo);

#endif
