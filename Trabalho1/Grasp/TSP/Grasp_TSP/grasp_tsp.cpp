#include "grasp_tsp.hpp"

vector<int> constructionPhase(Graph* graph, const double alpha, mt19937& gen);
void addNewRandomCity(vector<int>& solution, int& solution_len, vector<int>& lc, int& lc_size,
                      vector<int>& lrc, mt19937& gen);
vector<int> localSearchPhase(Graph* graph, vector<int> solution, const int max_iterations,
                             mt19937& gen);

pair<int, vector<int>> grasp(Graph* graph, const int grasp_max, const double alpha,
                             const int max_iterations_local_search, mt19937& gen) {
    const int n = graph->getNumVertices() - 1;

    vector<int> best_solution(n);
    int best_fo = INT_MAX;

    for (int i = 0; i < grasp_max; ++i) {
        vector<int> solution = constructionPhase(graph, alpha, gen);
        solution = localSearchPhase(graph, solution, max_iterations_local_search, gen);

        int fo = objectiveFunctionTSP(solution, graph, true);
        if (fo < best_fo) {
            best_fo = fo;
            copy(solution.begin(), solution.end(), best_solution.begin());
        }
    }

    return make_pair(best_fo, best_solution);
}

vector<int> constructionPhase(Graph* graph, const double alpha, mt19937& gen) {
    const int n = graph->getNumVertices() - 1;

    vector<int> solution;
    int solution_len = 0;

    // Lista de candidatos
    vector<int> lc(n);
    iota(lc.begin(), lc.end(), 1);
    int lc_size = n;

    // Seleciona-se um vertice aleatorio da lc para a cidade inicial
    {
        vector<int> lrc(n);
        iota(lrc.begin(), lrc.end(), 0);
        addNewRandomCity(solution, solution_len, lc, lc_size, lrc, gen);
    }

    while (lc_size) {
        // Calcula g(c)
        vector<int> g_c;
        for (int i = 0; i < lc_size; ++i) {
            int v = lc[i];
            g_c.push_back(graph->getEdge(solution[solution_len - 1], v));
        }

        // LRC por valor
        int c_min = *min_element(g_c.begin(), g_c.end());
        int c_max = *max_element(g_c.begin(), g_c.end());
        vector<int> lrc;
        double threshold = c_min + alpha * (c_max - c_min);
        for (int i = 0; i < lc_size; ++i) {
            if (g_c[i] <= threshold) {
                lrc.push_back(i);
            }
        }

        // Seleciona uma cidade aleatoria da LRC
        addNewRandomCity(solution, solution_len, lc, lc_size, lrc, gen);
    }

    return solution;
}

void addNewRandomCity(vector<int>& solution, int& solution_len, vector<int>& lc, int& lc_size,
                      vector<int>& lrc, mt19937& gen) {
    int i_next = getRandomInteger(0, lrc.size() - 1, gen);
    int v = lc[lrc[i_next]];
    solution.push_back(v);
    solution_len += 1;
    swap(lc[lrc[i_next]], lc[--lc_size]);
}

vector<int> localSearchPhase(Graph* graph, vector<int> solution, const int max_iterations,
                             mt19937& gen) {
    const int n = graph->getNumVertices() - 1;

    for (int it = 0; it < max_iterations; ++it) {
        bool improvement = false;
        vector<int> best_improvement(n);
        int best_neighbor_fo = objectiveFunctionTSP(solution, graph, true);

        for (int v = 0; v < n - 1; ++v) {
            // Obtem outra posicao aleatoria para fazer a troca
            int u;
            do {
                u = getRandomInteger(v + 1, n - 1, gen);
            } while (u == v);

            // Troca
            swap(solution[u], solution[v]);
            int new_fo = objectiveFunctionTSP(solution, graph, true);

            if (new_fo < best_neighbor_fo) {
                best_neighbor_fo = new_fo;
                copy(solution.begin(), solution.end(), best_improvement.begin());
                improvement = true;
            }

            // Desfaz alteracao
            swap(solution[u], solution[v]);
        }

        if (not improvement) break;

        solution = best_improvement;
    }
    return solution;
}
