#include "grasp_backpack.hpp"

vector<bool> constructionPhase(Backpack* backpack, const double alpha, mt19937& gen);
vector<bool> localSearchPhase(Backpack* backpack, vector<bool> solution, const int max_iterations,
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

    vector<bool> solution(n, false);
    int remaining_capacity = backpack->capacity;

    // Lista de candidatos
    vector<int> lc;
    lc.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (backpack->items[i].weight > backpack->capacity) continue;

        lc.push_back(i);
    }
    int lc_size = lc.size();

    while (lc_size) {
        // Calcula g(c) pela razao valor/peso
        vector<double> g_c;
        g_c.reserve(lc_size);
        for (int i = 0; i < lc_size; ++i) {
            int item_idx = lc[i];

            double value = backpack->items[item_idx].value;
            double weight = backpack->items[item_idx].weight;
            double ratio = value / weight;

            g_c.push_back(ratio);
        }

        // LRC por valor
        int c_min = *min_element(g_c.begin(), g_c.end());
        int c_max = *max_element(g_c.begin(), g_c.end());
        vector<int> lrc;
        double threshold = c_min + alpha * (c_max - c_min);

        for (int i = 0; i < lc_size; ++i) {
            if (g_c[i] >= threshold) {
                lrc.push_back(i);
            }
        }

        // Seleciona um item aleatorio da LRC
        int i_new = getRandomInteger(0, lrc.size() - 1, gen);
        int item = lc[lrc[i_new]];
        solution[item] = true;
        remaining_capacity -= backpack->items[item].weight;
        swap(lc[lrc[i_new]], lc[--lc_size]);

        // Atualiza lc somente com os itens viaveis
        for (int i = 0; i < lc_size; ++i) {
            if (backpack->items[lc[i]].weight > remaining_capacity) {
                swap(lc[i], lc[--lc_size]);
            }
        }
    }

    return solution;
}

vector<bool> localSearchPhase(Backpack* backpack, vector<bool> solution, const int max_iterations,
                              mt19937& gen) {
    const int n = backpack->items.size() - 1;

    int max_it_wihtout_improvement = sqrt(max_iterations);

    int it = 0;
    int it_without_improvement = 0;
    while (it++ < max_iterations) {
        if (it_without_improvement > max_it_wihtout_improvement) {
            break;
        }

        bool improvement = false;

        vector<bool> best_improvement(n);
        int best_neighbor_fo;
        tie(best_neighbor_fo, ignore) = objectiveFunctionBackpack(solution, backpack);

        double best_ratio = INT_MIN;
        vector<bool> solution_best_ratio(n);

        for (int item = 0; item < n; ++item) {
            float p = getRandomFloat(gen);

            // Flip
            if (p < 0.50f) {
                solution[item] = solution[item] ^ true;

                int curr_fo;
                tie(curr_fo, ignore) = objectiveFunctionBackpack(solution, backpack);

                if (curr_fo > best_neighbor_fo) {
                    best_neighbor_fo = curr_fo;
                    copy(solution.begin(), solution.end(), best_improvement.begin());
                    improvement = true;
                }

                if (curr_fo >= 0) {
                    int weight = 0;
                    for (int j = 0; j < n; ++j) weight += backpack->items[j].weight;

                    double ratio = (double)curr_fo / weight;

                    if (not improvement and ratio > best_ratio) {
                        best_ratio = ratio;
                        copy(solution.begin(), solution.end(), solution_best_ratio.begin());
                    }
                }

                solution[item] = solution[item] ^ true;
            } else {  // Troca
                int other_item;
                do {
                    if (item == n - 1) {
                        other_item = getRandomInteger(0, max(0, n - 2), gen);
                    } else {
                        other_item = getRandomInteger(item + 1, n - 1, gen);
                    }
                } while (item == other_item);

                swap(solution[item], solution[other_item]);

                int curr_fo;
                tie(curr_fo, ignore) = objectiveFunctionBackpack(solution, backpack);

                if (curr_fo > best_neighbor_fo) {
                    best_neighbor_fo = curr_fo;
                    copy(solution.begin(), solution.end(), best_improvement.begin());
                    improvement = true;
                }

                if (curr_fo >= 0) {
                    int weight = 0;
                    for (int j = 0; j < n; ++j) weight += backpack->items[j].weight;

                    double ratio = (double)curr_fo / weight;

                    if (not improvement and ratio > best_ratio) {
                        best_ratio = ratio;
                        copy(solution.begin(), solution.end(), solution_best_ratio.begin());
                    }
                }

                swap(solution[item], solution[other_item]);
            }
        }

        it_without_improvement = improvement ? 0 : it_without_improvement + 1;

        if (not improvement) {
            copy(solution_best_ratio.begin(), solution_best_ratio.end(), solution.begin());
        } else {
            copy(best_improvement.begin(), best_improvement.end(), solution.begin());
        }
    }

    return solution;
}
