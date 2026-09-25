#ifndef BACKPACK_HPP
#define BACKPACK_HPP

#include <climits>
#include <vector>
#include <algorithm>

struct Item {
    int value, weight;
};

struct Backpack {
    vector<Item> items; 
    int capacity;
};

pair<long long, vector<bool>> greedySolutionBackpack(Backpack* backpack);

Backpack* readInputBackpack(void);

long long objectiveFunctionBackpack(const vector<bool> solution, Backpack* backpack);

bool compItemsCostBenefit(const pair<Item, int>& item1, const pair<Item, int>& item2);

#endif
