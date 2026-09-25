#include <vector>
#include <iostream>
#include <climits>
#include <cmath>

#include "backpack.hpp"
#include "timer.hpp"

using namespace std;

pair<long long, vector<bool>> tabuSearchBackpack(Backpack* backpack);
void printSolution(const vector<bool>& solution, const long long fo);

int main(){
    string label = "Busca Tabu para o o Problema da Mochila 0/1";
    Timer timer(label);

    // Le o problema da entrada
    Backpack* backpack = readInputBackpack();

    // Busca Tabu
    auto [fo, solution] = tabuSearchBackpack(backpack);
   
    // Imprime solucao encontrada e tempo gasto
    timer.stop();
    cout << endl;
    printSolution(solution, fo);

    delete backpack;
    return 0;
}

pair<long long, vector<bool>> tabuSearchBackpack(Backpack* backpack){
    const int n = backpack->items.size();

    // Solucao inicial gulosa
    auto [fo, solution] = greedySolutionBackpack(backpack);  

    vector<bool> best_solution (n);
    copy(solution.begin(), solution.end(), best_solution.begin());
    long long best_fo = fo;

    // Define criterios de parada
    const int max_iterations = 1000;
    const int max_iterations_without_improvement = sqrt(max_iterations);

    // Define o tempo de vida de um elemento na lista tabu
    const int ttl_tabu_list = 3;

    // Inicializa a lista tabu com prazo
    vector<int> tabu_list (n, 0);
   
    int iterations = 0;
    int iteration_without_improvement = 0;

    while((iterations++ < max_iterations) && 
          (iteration_without_improvement < max_iterations_without_improvement)){
      
        long long best_neighbor_fo = -LLONG_MAX;
        int flip_pos = -1;

        // Criterio de Aspiracao por default
        // Verifica se todos os elementos estao na lista tabu
        int min_tabu_list = min_element(tabu_list.begin(), tabu_list.end());
        if(min_tabu_list != 0){
            // Caso todos estejam, realizamos o flip do mais antigo 
            for(int i = 0; i < n; ++i){
                if(tabu_list[i] != min_tabu_list) continue;

                flip_pos = i;
                solution[i] ^= 1;
                best_neighbor_fo = objectiveFunctionBackpack(solution, backpack);
                solution[i] ^= 1;
            }
        } else {
            for(int i = 0; i < n; ++i){
                solution[i] ^= 1; // flip
                
                fo = objectiveFunctionBackpack(solution, backpack);
                if((!tabu_list[i] and fo > best_neighbor_fo) or (fo > best_fo)){
                    best_neighbor_fo = fo;
                    flip_pos = i;
                }

                solution[i] ^= 1; // desfaz flip
            }
        }

        // Decrementa a lista tabu
        for(int i = 0; i < n; ++i){
            if(not tabu_list[i]) continue;
            tabu_list[i] -= 1;
        }

        // Adiciona o vizinho escolhido na lista tabu
        tabu_list[flip_pos] = ttl_tabu_list;

        // Atualiza a solucao atual 
        solution[flip_pos] ^= 1;
        fo = objectiveFunctionBackpack(solution, backpack);

        // Atualiza a melhor solucao encontrada
        if(fo > best_fo){
            best_fo = fo;
            copy(solution.begin(), solution.end(), best_solution.begin());
        }
    }
    return make_pair(best_fo, best_solution);
} 

void printSolution(const vector<bool>& solution, const long long fo){
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "       Busca Tabu para o Problema da Mochila       " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "- FO encontrada: " << fo << endl;
    cout << "- Itens escolhidos: ";
    for (int i = 0; i < solution.size(); ++i) {
        if(not solution[i]) continue;
        cout << i << ' ';
    }
    cout << endl;
}
