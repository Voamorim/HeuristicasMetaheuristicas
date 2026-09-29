#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
	int value, weight;
};

struct Backpack {
	vector<Item> items;
	int capacity;
};

pair<long long, vector<bool>> greedySolutionBackpack(Backpack* backpack);

Backpack* readInputBackpack(void);

long long objectiveFunctionBackpack(const vector<bool> solution, Backpack* backpack,
									const bool penalty = true);

bool compItemsCostBenefit(const pair<Item, int>& item1, const pair<Item, int>& item2);

void printSolutionBackpack(const vector<bool>& solution, const long long fo, const string title);

#endif
