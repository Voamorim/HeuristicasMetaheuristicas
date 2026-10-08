#include "sa_tsp.hpp"

pair<int, vector<int>> simulatedAnnealingTSP(vector<int> curr_solution, float temperature,
											 const float alpha, const int sa, Graph* graph,
											 mt19937& gen) {
	const int n = graph->getNumVertices() - 1;

	int curr_fo = objectiveFunctionTSP(curr_solution, graph, false);

	// Salva a solucao atual como melhor solucao
	int best_fo = curr_fo;
	vector<int> best_solution(n);
	copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());

	// Simulated Annealing
	int i = 0;

	// Define temperatura minima para evitar loops infinitos
	const double min_temperature = 0.0001;

	while (temperature > min_temperature) {
		while (i < sa) {
			// Seleciona um vizinho da solucao atual
			int v = getRandomInteger(0, n - 1, gen);
			int u;
			do {
				u = getRandomInteger(0, n - 1, gen);
			} while (v == u);

			swap(curr_solution[v], curr_solution[u]);
			int new_fo = objectiveFunctionTSP(curr_solution, graph, false);

			if (new_fo < curr_fo) {
				curr_fo = new_fo;

				if (new_fo < best_fo) {
					copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
					best_fo = new_fo;
				}
			} else {
				double r = getRandomFloat(gen);
				double delta = new_fo - curr_fo;
				double p = exp(-delta / temperature);

				if (r < p) {
					curr_fo = new_fo;
				} else {
					// Desfaz a troca
					swap(curr_solution[v], curr_solution[u]);
				}
			}
			i++;
		}
		temperature = alpha * temperature;
		i = 0;
	}
	return make_pair(best_fo, best_solution);
}