#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "bt_tsp.hpp"
#include "tsp.hpp"

using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());

    string label = "Busca Tabu para o Problema do Caixeiro Viajante (TSP)";
    Timer timer(label);

    Graph* graph = new Graph();
    graph->readInput();

    const int n = graph->getNumVertices() - 1;

    // Solucao inicial gulosa
    vector<int> curr_solution = getGreedySolutionTSP(graph, n, gen, true);
    int curr_fo = objectiveFunctionTSP(curr_solution, graph, false);

    // Criterios de parada
    const int max_iterations = 1000 * n;
    const int max_iterations_without_improvement = sqrt(max_iterations);

    // Tempo de vida de um elemento na lista tabu
    const int tabu_list_ttl = 3;

    auto [best_fo, best_solution] =
        tabuSearchTSP(curr_solution, curr_fo, graph, timer, tabu_list_ttl, max_iterations,
                      max_iterations_without_improvement);

    // Imprime a solução final encontrada e o tempo gasto
    timer.stop();
    cout << endl;

    string title = "Busca Tabu para o TSP";
    printSolutionTSP(best_solution, best_fo, title);

    delete graph;
    return 0;
}
