#include "sa_backpack.hpp"

pair<int, vector<bool>> simulatedAnnealingBackpack(vector<bool> curr_solution, double temperature,
                                                   const double alpha, const int sa,
                                                   Backpack* backpack, mt19937& gen) {
    const int n = backpack->items.size();

    int curr_fo;
    tie(curr_fo, ignore) = objectiveFunctionBackpack(curr_solution, backpack);

    // Salva a solução atual como melhor solução
    int best_fo = curr_fo;

    vector<bool> best_solution(n);
    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());

    // Simulated Annealing
    int i = 0;

    // Define temperatura mínima para evitar loops infinitos
    const double min_temperature = 0.0001;

    while (temperature > min_temperature) {
        while (i < sa) {
            // Seleciona um vizinho da solução atual
            int item_idx = getRandomInteger(0, n - 1, gen);

            curr_solution[item_idx] = curr_solution[item_idx] ^ 1;  // flip

            auto [new_fo, viable] = objectiveFunctionBackpack(curr_solution, backpack);

            if (new_fo > curr_fo) {
                curr_fo = new_fo;

                if (new_fo > best_fo and viable) {
                    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
                    best_fo = new_fo;
                }
            } else {
                double r = getRandomFloat(gen);
                double delta = curr_fo - new_fo;
                double p = exp(-delta / temperature);

                if (r < p) {
                    curr_fo = new_fo;
                } else {
                    // Desfaz flip
                    curr_solution[item_idx] = curr_solution[item_idx] ^ 1;
                }
            }
            i++;
        }
        temperature = alpha * temperature;
        i = 0;
    }

    return make_pair(best_fo, best_solution);
}
