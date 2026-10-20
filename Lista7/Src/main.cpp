#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "graph.hpp"
#include "ils_tsp.hpp"
#include "io.hpp"
#include "timer.hpp"
#include "tsp.hpp"

using namespace std;

#define DEFAULT_INPUT_FILE "bier127.tsp"

Graph* readInput(int argc, char** argv);

int main(int argc, char** argv) {
    random_device rd;
    mt19937 gen(rd());

    string label = "ILS para o Problema do Caixeiro Viajante (TSP)";
    Timer timer(label);

    Graph* graph = readInput(argc, argv);
    if(graph == NULL){
        return 1;
    }

    const int n = graph->getNumVertices() - 1;

    // Solucao inicial gulosa
    vector<int> greedy_solution = getGreedySolutionTSP(graph, n, gen, true);
    int greedy_fo = objectiveFunctionTSP(greedy_solution, graph, false);
    cout << endl;

    // -=-=-=-=-=--= ILS =-=-=-=-=-=-=-
    const int max_iterations = n * 1000;
    const int max_iterations_wihtout_improvement = max_iterations / 100;
    const int max_iterations_local_search = n;

    int best_fo;
    vector<int> best_solution;
    tie(best_fo, best_solution) = ilsTSP(graph, greedy_solution, max_iterations, max_iterations_wihtout_improvement, max_iterations_local_search, gen, timer);

    string title = "ILS para o Problema do Caixeiro Viajante (TSP)";
    printSolutionTSP(best_solution, best_fo, title);
    cout << endl;
    timer.stop();

    delete graph;
    return 0;
}

Graph* readInput(int argc, char** argv){
    // Coleta o arquivo de entrada
    Io* io = new Io();
    string input_file_name = io->getInputFileName(argc, argv);
    if (input_file_name == "") {
        input_file_name = DEFAULT_INPUT_FILE;
        cerr << "[INFO] Arquivo de entrada nao especificado. Utilizando o arquivo "
             << input_file_name << endl;
    }
    string input_path = "../Input/" + input_file_name;
    ifstream input_file(input_path);
    streambuf* cin_buffer = cin.rdbuf();
    cin.rdbuf(input_file.rdbuf());
    if (not input_file.is_open()) {
        cerr << "[ERROR] Erro ao tentar abrir o arquivo de entrada fornecido." << endl;
        delete io;
        return NULL;
    } else {
        cout << "[INFO] Arquivo de entrada " << input_file_name << " lido com sucesso!" << endl;
    }
    delete io;

    // Le o problema da entrada
    Graph* graph = new Graph();
    graph->readInput();
    const int n = graph->getNumVertices() - 1;
    cout << "[INFO] Grafo lido com sucesso!" << endl << endl;
    cin.rdbuf(cin_buffer);
    
    return graph;
}
