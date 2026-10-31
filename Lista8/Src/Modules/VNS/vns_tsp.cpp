#include "vns_tsp.hpp"

vector<int> perturbation(const vector<int>& solution, int n, mt19937& gen);

void updateNeighborhood(vector<int>& solution, int &fo, const vector<int>& new_solution, const int new_fo, int& k, bool &improvement, Timer& timer);

pair<int, vector<int>> vnsTSP(Graph* graph, vector<int> solution, const int VNSMax, const int VMax, const int max_iterations_local_search, mt19937& gen, Timer& timer){
    const int n = graph->getNumVertices() - 1;

    int fo = objectiveFunctionTSP(solution, graph, false);

    int iterations_without_improvement = 0;

    while (true){
        if(iterations_without_improvement >= VNSMax){
            cout << "Criterio de parada por estagnacao acionado!" << endl;
            timer.elapsed();
            cout << endl;
            break;
        }

        bool improvement = false;
        
        int k = 1;
        while(k <= VMax){
            vector<int> new_sol = perturbation(solution, n, gen);
            
            new_sol = localSearchTSP(graph, new_sol, max_iterations_local_search, gen);
            int new_fo = objectiveFunctionTSP(new_sol, graph, false);

            updateNeighborhood(solution, fo, new_sol, new_fo, k, improvement, timer);
        }

        if(not improvement){
            iterations_without_improvement += 1;
        } else {
            iterations_without_improvement = 0;
        }
    }

    return make_pair(fo, solution);
}

vector<int> perturbation(const vector<int>& solution, int n, mt19937& gen){
    vector<int> new_solution = solution;

    // Seleciona um vizinho da solucao atual
    int v = getRandomInteger(0, n - 1, gen);
    int u;
    do {
        u = getRandomInteger(0, n - 1, gen);
    } while (v == u);  

    // Aplica movimento aleatório
    swap(new_solution[v], new_solution[u]);

    return new_solution;
}

void updateNeighborhood(vector<int>& solution, int &fo, const vector<int>& new_solution, const int new_fo, int& k, bool &improvement, Timer& timer){
    if(new_fo < fo){
        solution = new_solution;
        fo = new_fo;
        k = 1;

        improvement = true;

        cout << "Solucao melhor encontrada! Nova FO: " << new_fo << endl;
        timer.elapsed();
    } else {
        k += 1;
    }
    return;
}