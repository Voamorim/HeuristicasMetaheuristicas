#include "grasp_backpack.hpp"

vector<bool> constructionPhase(Backpack* backpack, const double alpha, mt19937& gen);
vector<bool> localSearchPhase(Backpack* backpack, vector<bool> solution, const double alpha,
                              mt19937& gen);

pair<int, vector<bool>> graspBackpack(Backpack* backpack, const int grasp_max, const double alpha,
                                      const int max_iterations_local_search, mt19937& gen) {
    const int n = backpack->items.size() - 1;

    vector<bool> best_solution(n);
    int best_fo = INT_MIN;

    for (int i = 0; i < grasp_max; ++i) {
        vector<bool> solution = constructionPhase(backpack, alpha, gen);
        solution = localSearchPhase(backpack, solution, max_iterations_local_search, gen);

        int fo;
        tie(fo, ignore) = objectiveFunctionBackpack(solution, backpack, true);
        if (fo > best_fo) {
            best_fo = fo;
            copy(solution.begin(), solution.end(), best_solution.begin());
        }
    }

    return make_pair(best_fo, best_solution);
}

vector<bool> constructionPhase(Backpack* backpack, const double alpha, mt19937& gen) {
    const int n = backpack->items.size() - 1;

    vector<bool> solution;
}

vector<bool> localSearchPhase(Backpack* backpack, vector<bool> solution, const double alpha,
                              mt19937& gen) {
    const int n = backpack->items.size() - 1;
}
