#include <fstream>
#include <iostream>
#include <random>
#include <string>

#include "graph.hpp"
#include "grasp_tsp.hpp"
#include "io.hpp"
#include "timer.hpp"
#include "tsp.hpp"

#define DEFAULT_INPUT_FILE "bier127.tsp"

int main(int argc, char** argv) {
    random_device rd;
    mt19937 gen(rd());

    string label = "Grasp para o Problema do Caixeiro Viajante (TSP)";
    Timer timer(label);

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
        return 1;
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

    // -=-=-=-=-=--= Grasp =-=-=-=-=-=-=-
    const int grasp_max = 2000;
    const int max_iterations_local_search = 50;
    const double alpha = 0.02;

    int best_fo;
    vector<int> best_solution;
    tie(best_fo, best_solution) = grasp(graph, grasp_max, alpha, max_iterations_local_search, gen);

    string title = "Grasp para o Problema do Caixeiro Viajante (TSP)";
    printSolutionTSP(best_solution, best_fo, title);
    cout << endl;
    timer.stop();
    return 0;
}
