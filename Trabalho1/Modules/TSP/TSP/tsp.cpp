#include "tsp.hpp"

int objectiveFunctionTSP(const vector<int>& solution, Graph* graph, const bool penalty) {
    int fo = 0;
    int v = solution[0];

    for (int u = 1; u < solution.size(); ++u) {
        int w = graph->getEdge(v, solution[u]);

        // Punicao para solucoes que usam arestas inexistentes no grafo (solucoes
        // inviaveis)
        if (w == -1 && penalty) {
            return 100000;
        }

        fo += w;
        v = solution[u];
    }
    int w = graph->getEdge(solution[solution.size() - 1], solution[0]);

    // Punicao para solucoes que usam arestas inexistentes no grafo (solucoes
    // inviaveis)
    if (w == -1 && penalty) {
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

vector<int> getGreedySolutionTSP(Graph* graph, const int n, mt19937& gen,
                                 const bool print_solution) {
    vector<int> solution;

    int starting_node = getRandomInteger(1, n, gen);
    solution.push_back(starting_node);

    vector<bool> vis(n + 1, false);
    vis[starting_node] = true;

    for (int i = 1; i < n; ++i) {
        long long min_edge = LLONG_MAX;
        int next_node = -1;

        for (int v = 1; v <= n; ++v) {
            if (vis[v]) continue;

            int w = graph->getEdge(solution[i - 1], v);

            if (w < min_edge) {
                next_node = v;
                min_edge = w;
            }
        }
        vis[next_node] = true;
        solution.push_back(next_node);
    }

    if (print_solution) {
        string title = "Heuristica Gulosa para o TSP";
        int fo = objectiveFunctionTSP(solution, graph, false);
        printSolutionTSP(solution, fo, title);
    }

    return solution;
}

void printSolutionTSP(const vector<int>& solution, const int fo, const string title) {
    int title_size = title.size();
    int bar_size = 60;

    // Barra superior
    for (int i = 0; i < bar_size; i += 2) cout << "=-";
    cout << endl;

    int n_espaces = (bar_size - title_size) / 2;
    while (n_espaces--) cout << ' ';
    cout << title << endl;

    // Barra inferior
    for (int i = 0; i < bar_size; i += 2) cout << "=-";
    cout << endl;

    cout << "- FO: " << fo << endl;
    cout << "- Caminho: ";
    for (int i = 0; i < solution.size(); ++i) {
        cout << solution[i] << ' ';
    }
    cout << solution[0] << endl;

    // Barra inferior
    for (int i = 0; i < bar_size; i += 2) cout << "=-";
    cout << endl;
}
