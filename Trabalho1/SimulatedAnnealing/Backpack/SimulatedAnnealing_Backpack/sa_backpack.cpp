#include "sa_backpack.hpp"

pair<int, vector<bool>> simulatedAnnealingBackpack(vector<bool>& curr_solution, double temperature,
												   const double alpha, const int sa,
												   Backpack* backpack, mt19937& gen) {
	const int n = backpack->items.size();

	int curr_fo = objectiveFunctionBackpack(curr_solution, backpack);

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
			int item_idx =
		}
	}
}
