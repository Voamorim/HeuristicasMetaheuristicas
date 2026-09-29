#include <cmath>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include <algorithm>

#include "graph.hpp"
#include "timer.hpp"
#include "tsp.hpp"
#include "utils.hpp"

using namespace std;

pair<int, vector<int>> simulatedAnnealingTSP(vector<int>& curr_solution, float temperature,
                                             float alpha, int sa, Graph* graph, mt19937& gen) {
    const int n = graph->getNumVertices() - 1;

    int curr_fo = objectiveFunctionTSP(curr_solution, graph);

    // Salva a solucao atual como melhor solucao
    int best_fo = curr_fo;
    vector<int> best_solution(n);
    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());

    // Simulated Annealing
    int i = 0;
    while (temperature > 0.0001) {
        while (i < sa) {
            // Seleciona um vizinho da solucao atual
            int v = getRandomInteger(0, n - 1, gen);
            int u;
            do {
                u = getRandomInteger(0, n - 1, gen);
            } while (v == u);

            swap(curr_solution[v], curr_solution[u]);
            int new_fo = objectiveFunctionTSP(curr_solution, graph);

            if (new_fo < curr_fo) {
                curr_fo = new_fo;

                if (new_fo < best_fo) {
                    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
                    best_fo = new_fo;
                }
            } else {
                float r = getRandomFloat(gen);
                float p = 1.0f / (1.0f + exp(((float)new_fo - curr_fo) / temperature));

                if (r < p) {
                    curr_fo = new_fo;
                } else {  // Desfaz a troca
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

int main() {
    random_device rd;
    mt19937 gen(rd());

    string label = "Simulated Annealing para o Problema do Caixeiro Viajante (TSP)";
    Timer timer(label);

    Graph* graph = new Graph();
    graph->readInput();

    const int n = graph->getNumVertices() - 1;

    // Solucao inicial aleatoria
    vector<int> curr_solution = getRandomSolutionTSP(n, gen);

    // Temperatura inicial
    float temperature = 10000000.0f;

    // Fator de esfriamento
    float alpha = 0.95f;

    // Iteracoes por temperatura
    int sa = n;

    auto [best_fo, best_solution] =
        simulatedAnnealingTSP(curr_solution, temperature, alpha, sa, graph, gen);

    timer.stop();
    cout << endl;

    printBestSolutionTSP(best_solution, best_fo);

    delete graph;
    return 0;
}
