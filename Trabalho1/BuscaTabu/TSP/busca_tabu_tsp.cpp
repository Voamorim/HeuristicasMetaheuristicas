#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>
#include <random>

#include "tsp.hpp"
#include "utils.hpp"
#include "timer.hpp"
#include "graph.hpp"

using namespace std;

pair<int, vector<int>> tabuSearchTSP(vector<int>& curr_solution, long long fo,
                                     Graph* graph, Timer& timer, const int ttl_tabu_list, 
                                     const int max_iterations, 
                                     const int max_iteration_without_improvement);

int main(){
    random_device rd;
    mt19937 gen(rd());

    string label = "Busca Tabu para o Problema do Caixeiro Viajante (TSP)";
    Timer timer(label);

    Graph* graph = new Graph();
    graph->readInput();

    const int n = graph->getNumVertices() - 1;

    // TODO: Implementar isso direito. Imprimindo a saída da sol inicial
    //
    // Solucao inicial aleatoria
    auto [fo, curr_solution] = getRandomSolutionTSP(n, gen);

    // TODO: Fazer teste fatorial para os parâmetros
    
    // Define criterios de parada
    const int max_iterations = 1000 * n;
    const int max_iterations_without_improvement = sqrt(max_iterations);

    // Define o tempo de vida de um elemento na lista tabu
    const int ttl_tabu_list = 3;

    auto [best_fo, best_solution] = tabuSearchTSP(curr_solution, fo, graph, timer,
                                                  ttl_tabu_list, max_iterations,
                                                  max_iterations_without_improvement);

    // Imprime a solução final encontrada e o tempo gasto
    timer.stop();  
    cout << endl; 

    // TODO: implementar essa funcao para o TSP
    printSolution(best_solution, best_fo);

    delete graph;
    return 0;
}

pair<int, vector<int>> tabuSearchTSP(vector<int>& curr_solution, long long fo,
                                     Graph* graph, Timer& timer, const int ttl_tabu_list, 
                                     const int max_iterations, 
                                     const int max_iteration_without_improvement){
    const int n = graph->getNumVertices() - 1;
   
    vector<int> best_solution(n);
    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
    long long best_fo = fo;

    // Inicializa a Lista Tabu com prazo
    vector<vector<int>> tabu_list (n+1, 0);

    int iterations = 0;
    int iterations_without_improvement = 0;

    while(iterations++ < max_iterations){
        // Aplica critério de parada por estagnação
        if(iterations_without_improvement >= max_iterations_without_improvement){
            cout << "Criterio de parada por estagnacao acionado!" << endl << endl;
            break;
        }

        long long best_neighbor_fo = LLONG_MAX;
        pair<int, int> swapped_nodes = {-1, -1}
        
        // TODO: terminar isso daqui  

    }

}
