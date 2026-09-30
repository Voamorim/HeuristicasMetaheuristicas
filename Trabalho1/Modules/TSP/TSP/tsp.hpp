#ifndef TSP_HPP
#define TSP_HPP

#include <algorithm>
#include <climits>
#include <iostream>
#include <random>
#include <vector>

#include "graph.hpp"
#include "utils.hpp"

using namespace std;

vector<int> getRandomSolutionTSP(const int n, mt19937& gen, const bool print_solution);
vector<int> getGreedySolutionTSP(Graph* graph, const int n, mt19937& gen,
                                 const bool print_solution);

int objectiveFunctionTSP(const vector<int>& solution, Graph* graph, const bool penalty);

void printSolutionTSP(const vector<int>& solution, const int fo, const string title);

#endif
