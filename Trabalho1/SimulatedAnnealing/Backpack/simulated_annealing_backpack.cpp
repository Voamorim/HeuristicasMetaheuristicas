#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "backpack.hpp"
#include "timer.hpp"
#include "utils.hpp"

using namespace std;

pair<int, vector<bool>> simulatedAnnealingBackpack(vector<bool>& curr_solution, float temperature,
												   float alpha, int sa, Backpack* backpack,
												   mt19937& gen);

int main() {
	random_device rd;
	mt19937 gen(rd());

	string label = "Simulated Annealing para o o Problema da Mochila 0/1";
	Timer timer(label);

	// Le o problema da entrada
	Backpack* backpack = readInputBackpack();
	const int n = backpack->items.size();

	// Solucao inicial gulosa
	auto [greedy_fo, greedy_solution] = greedySolutionBackpack(backpack);

	// TODO: fazer teste fatorial para encontrar os melhores valores para os parâmetros
	vector<double> temperatures = {1000.0, 10000.0, 100000.0, 1000000.0};
	vector<double> alphas = {0.9, 0.95, 0.99};

	// Iterações por temperatura
	const int sa = n;

	// Temperatura inicial
	for (const auto& temperature : temperatures) {
		// Fator de esfriamento
		for (const auto& alpha : alphas) {
			// Simulated Annealing
			auto [best_fo, best_solution] =
				simulatedAnnealingBackpack(greedy_solution, temperature, alpha, sa, backpack, gen);

			// Imprime solucao encontrada e tempo gasto
			timer.stop();
			cout << endl;
			string title = "Simulated Annealing para Mochila 0/1";
			printSolutionBackpack(best_solution, best_fo, title);
		}
	}
	delete backpack;
	return 0;
}

pair<int, vector<bool>> simulatedAnnealingBackpack(vector<bool>& curr_solution, float temperature,
												   float alpha, int sa, Backpack* backpack,
												   mt19937& gen) {
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
