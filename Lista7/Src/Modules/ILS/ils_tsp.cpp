#include "ils.hpp"

pair<int, vector<int>> ilsTsp(Graph* graph, vector<int> solution, const int max_iterations, const int max_iterations_without_improvement, const int max_iterations_local_search, mt19937& gen){
    const int n = graph->getNumVertices() - 1;

    // Aplica busca local à solução inicial
    solution = localSearchTSP(graph, solution, max_iterations_local_search, gen);
    int fo = objetiveFunctionTSP(solution, graph, true);

    int iterations = 0;
    int iterations_without_improvement = 0;

    // Critério de parada por máximo de iterações
    while(iterations++ < max_iterations){

        // Critério de parada por estagnação 
        if(iterations_without_improvement >= max_iterations_without_improvement){
            cout << "Criterio de parada por estagnacao acionado!" << endl << endl;
            break;
        }

        vector<int> new_solution = perturbation(solution, level);                
        new_solution = localSearchTSP(graph, new_solution, max_iterations_local_search, gen);
        
        // Fase de aceitação 
        new_fo = objectiveFunctionTSP(new_solution, graph, true);
        if(new_fo < fo){
            copy(new_solution.begin(), new_solution.end(), solution.begin());
            fo = new_fo;

            iterations_without_improvement = 0;
            level = 1;
        } else {
            iterations_without_improvement += 1; 
            level += 1;
        }
    }

    return make_pair(fo, solution);
}

vector<int> perturbation(vector<int> solution, const int level){
    const int nchanges = level;
    int iterations = 0;    

    while(iterations++ < nchanges){
        // Seleciona um vizinho da solucao atual
        int v = getRandomInteger(0, n - 1, gen);
        int u;
        do {
            u = getRandomInteger(0, n - 1, gen);
        } while (v == u);  

        // Aplica movimento aleatório
        swap(solution[v], solution[u]);
    }

    return solution;
}
