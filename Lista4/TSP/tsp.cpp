#include "tsp.hpp"

int objetiveFunctionTSP(const vector<int>& solution, Graph* graph) {
    int fo = 0;
    int v = solution[0];

    for (int u = 1; u < solution.size(); ++u) {
        int w = graph->getEdge(v, solution[u]);

        // Punicao para solucoes que usam arestas inexistentes no grafo (solucoes
        // inviaveis)
        if (w == -1) {
            return 100000;
        }

        fo += w;
        v = solution[u];
    }
    int w = graph->getEdge(solution[solution.size() - 1], solution[0]);

    // Punicao para solucoes que usam arestas inexistentes no grafo (solucoes
    // inviaveis)
    if (w == -1) {
        return 100000;
    }

    fo += w;
    return fo;
}

vector<int> getRandomSolutionTSP(const int n, mt19937& gen) {
        vector<int> solution(n);
        iota(solution.begin(), solution.end(), 1);
        shuffle(solution.begin(), solution.end(), gen);
        return solution;
}

void printBestSolutionTSP(const vector<int> &best_solution, const int best_fo){
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "         Problema do Caixeiro Viajante (TSP)       " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "- Melhor FO encontrada: " << best_fo << endl;
    cout << "- Caminho encontrado: ";
    for (int i = 0; i < n; ++i) {
        cout << best_solution[i] << ' ';
    }
    cout << best_solution[0] << endl;
}
