#include "bt_backpack.hpp"

pair<long long, vector<bool>> tabuSearchBackpack(vector<bool>& solution, long long fo,
                                                 Backpack* backpack, Timer& timer) {
    const int n = backpack->items.size();

    vector<bool> best_solution(n);
    copy(solution.begin(), solution.end(), best_solution.begin());
    long long best_fo = fo;

    // Define criterios de parada
    const int max_iterations = 1000 * n;
    const int max_iterations_without_improvement = sqrt(max_iterations);

    // Define o tempo de vida de um elemento na lista tabu
    const int ttl_tabu_list = 3;

    // Inicializa a lista tabu com prazo
    vector<int> tabu_list(n, 0);

    int iterations = 0;
    int iterations_without_improvement = 0;

    while (iterations++ < max_iterations) {
        // Aplica criterio de parada por estagnacao
        if (iterations_without_improvement >= max_iterations_without_improvement) {
            cout << "Criterio de parada por estagnacao acionado!" << endl << endl;
            break;
        }

        long long best_neighbor_fo = -LLONG_MAX;
        int flip_pos = -1;

        // Criterio de Aspiracao por default
        //
        // Verifica se todos os elementos estao na lista tabu
        int min_tabu_list = *min_element(tabu_list.begin(), tabu_list.end());

        if (min_tabu_list != 0) {
            // Caso todos estejam, realizamos o flip do mais antigo
            for (int i = 0; i < n; ++i) {
                if (tabu_list[i] != min_tabu_list) continue;

                flip_pos = i;
                solution[i] = solution[i] ^ 1;
                best_neighbor_fo = objectiveFunctionBackpack(solution, backpack);
                solution[i] = solution[i] ^ 1;
            }
        } else {
            for (int i = 0; i < n; ++i) {
                solution[i] = solution[i] ^ 1;  // flip

                fo = objectiveFunctionBackpack(solution, backpack);
                if ((!tabu_list[i] and fo > best_neighbor_fo) or
                    (fo > best_fo and fo > best_neighbor_fo)) {
                    best_neighbor_fo = fo;
                    flip_pos = i;
                }

                solution[i] = solution[i] ^ 1;  // desfaz flip
            }
        }

        // Decrementa a lista tabu
        for (int i = 0; i < n; ++i) {
            if (not tabu_list[i]) continue;
            tabu_list[i] -= 1;
        }

        // Adiciona o vizinho escolhido na lista tabu
        tabu_list[flip_pos] = ttl_tabu_list;

        // Atualiza a solucao atual
        solution[flip_pos] = solution[flip_pos] ^ 1;
        fo = objectiveFunctionBackpack(solution, backpack);

        // Atualiza a melhor solucao encontrada
        if (fo > best_fo) {
            best_fo = fo;
            copy(solution.begin(), solution.end(), best_solution.begin());
            iterations_without_improvement = 0;

            cout << "Solucao melhor encontrada: " << best_fo << endl;
            timer.elapsed();
            cout << endl;
        } else {
            iterations_without_improvement++;
        }
    }
    return make_pair(best_fo, best_solution);
}
