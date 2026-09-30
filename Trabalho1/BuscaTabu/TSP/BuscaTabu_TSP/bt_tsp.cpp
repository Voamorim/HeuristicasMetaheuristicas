#include "bt_tsp.hpp"

#include "tsp.hpp"

pair<int, vector<int>> tabuSearchTSP(vector<int>& solution, long long fo, Graph* graph,
                                     Timer& timer, const int ttl_tabu_list,
                                     const int max_iterations,
                                     const int max_iterations_without_improvement) {
    const int n = graph->getNumVertices() - 1;

    vector<int> best_solution(n);
    copy(solution.begin(), solution.end(), best_solution.begin());
    long long best_fo = fo;

    // Inicializa a Lista Tabu com prazo
    vector<vector<int>> tabu_list(n + 1, vector<int>(n + 1, 0));

    int iterations = 0;
    int iterations_without_improvement = 0;

    while (iterations++ < max_iterations) {
        // Aplica critério de parada por estagnação
        if (iterations_without_improvement >= max_iterations_without_improvement) {
            cout << "Criterio de parada por estagnacao acionado!" << endl << endl;
            break;
        }

        int best_neighbor_fo = INT_MAX;
        pair<int, int> swap_pos = {-1, -1};

        // Criterio de aspiracao por default
        //
        // Verifica se todos os elementos estao na lista tabu
        int min_tabu_list = INT_MAX;
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                min_tabu_list = min(min_tabu_list, tabu_list[i][j]);
            }
        }

        if (min_tabu_list != 0) {
            // Caso todos estejam na lista tabu, realizamos a troca do mais antigo
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j < i; ++j) {
                    if (tabu_list[i][j] != min_tabu_list) continue;

                    swap_pos = make_pair(i, j);
                    swap(solution[i], solution[j]);
                    best_neighbor_fo = objectiveFunctionTSP(solution, graph, false);
                    swap(solution[i], solution[j]);
                }
            }
        } else {
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j < i; ++j) {
                    swap(solution[i], solution[j]);  // troca

                    fo = objectiveFunctionTSP(solution, graph, false);
                    if ((!tabu_list[i][j] and fo < best_neighbor_fo) or
                        (fo < best_fo and fo > best_neighbor_fo)) {
                        best_neighbor_fo = fo;
                        swap_pos = make_pair(i, j);
                    }

                    swap(solution[i], solution[j]);  // desfaz troca
                }
            }
        }

        // Decrementa a lista tabu
        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j < i; ++j) {
                if (not tabu_list[i][j]) continue;
                tabu_list[i][j] -= 1;
            }
        }

        // Adiciona a troca na lista tabu
        int i = swap_pos.first;
        int j = swap_pos.second;
        tabu_list[i][j] = ttl_tabu_list;

        // Atualiza a solucao atual
        swap(solution[i], solution[j]);
        fo = objectiveFunctionTSP(solution, graph, false);

        // Atualiza a meior solucao encontrada
        if (fo < best_fo) {
            best_fo = fo;
            copy(solution.begin(), solution.end(), best_solution.begin());
            iterations_without_improvement = 0;

            cout << "Solucao melhor encontrada: " << best_fo << endl;
            timer.elapsed();
            cout << endl;
        } else {
            iterations_without_improvement += 1;
        }
    }
    return make_pair(best_fo, best_solution);
}
