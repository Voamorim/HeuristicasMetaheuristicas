#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "backpack.hpp"
#include "simulated_annealing_backpack.hpp"
#include "timer.hpp"
#include "utils.hpp"

using namespace std;

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

    // Valores a serem testados
	const vector<double> temperatures = {1000.0, 10000.0, 100000.0, 1000000.0};
	const vector<double> alphas = {0.9, 0.95, 0.99};

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
