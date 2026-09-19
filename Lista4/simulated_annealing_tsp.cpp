#include "graph.hpp"
#include "utils.hpp"
#include "tsp.hpp"
#include "timer.hpp"

#include <set>
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

pair<int, vector<int>> simulatedAnnealingTSP(vector<int> &curr_solution, int temperature, double alpha, int sa, Graph* graph, mt19937& gen){
    const int n = graph->getNumVertices() - 1; 

    int curr_fo = objectiveFunctionTSP(curr_solution, graph);

    // Salva a solucao atual como melhor solucao 
    int best_fo = curr_fo;
    vector<int> best_solution;
    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());

    // Simulated Annealing
    int i = 0;
    while(temperature > 0){
        while(i < sa){
            // Seleciona um vizinho da solucao atual
            int v = getRandomInteger(0, n-1, gen); 
            int u;
            do{
                u = getRandomInteger(0, n-1, gen); 
            } while(v == u);

            vector<int> new_solution (n);
            copy(curr_solution.begin(), curr_solution.end(), new_solution.begin());

            swap(new_solution[v], new_solution[u]);
            int new_fo = objectiveFunctionTSP(new_slution, graph); 

            if(new_fo > curr_fo){
                copy(new_solution.begin(), new_solution.end(), curr_solution.begin()); 
                curr_fo = new_fo;

                if(new_fo > best_fo){
                    copy(new_solution.begin(), new_solution.end(), best_solution.begin());
                    best_fo = new_fo;
                }
            } else {
                float r = getRandomFloat(gen);
                float p = 1.0f / (1.0f + exp(((float) new_fo - curr_fo) / temperature);

                if(r < p){
                    copy(new_solution.begin(), new_solution.end(), curr_solution.begin()); 
                    curr_fo = new_fo;
                }
            }
            i++; 
        }
        temperature = alpha * temperature;
        i = 0;
    }

    return make_pair(best_fo, best_solution);
}

int main(){
    random_device rd;
    mt19937 gen(rd());

    string label = "Simulated Annealing para o Problema do Caixeiro Viajante (TSP)";
    Timer timer (label);

    Graph* graph = new Graph();
    graph->readInput();

    const int n = graph->getNumVertices() - 1;

    // Solucao inicial aleatoria
    vector<int> curr_solution = getRandomSolutionTSP(n, gen);

    // Temperatura inicial
    int temperature = 10000;  

    // Fator de esfriamento
    double alpha = 0.15;

    // Iteracoes por temperatura
    int sa = ceil((double) sqrt(n));

    auto [best_fo, best_solution] = simulatedAnnealingTSP(curr_solution, temperature, alpha, sa, graph, gen);

    timer.stop();
    cout << endl;

    printBestSolutionTSP(best_solution, best_fo);

    delete graph;
    return 0
}
