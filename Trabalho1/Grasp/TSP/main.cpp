#include <fstream>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "build_csv.hpp"
#include "graph.hpp"
#include "grasp_tsp.hpp"
#include "io.hpp"
#include "timer.hpp"
#include "tsp.hpp"

using namespace std;

#define DEFAULT_INPUT_FILE "bier127.tsp"

void factorialTest(Graph* graph, Timer& timer, mt19937& gen);
void solve(Graph* graph, Timer& timer, mt19937& gen);

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
    string input_path = "../../Input/TSP/" + input_file_name;
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

    // Obtem o ID da solucao
    int solution_id = io->getSolutionId(argc, argv);

    if (solution_id == 1) {
        cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
        solve(graph, timer, gen);
    } else if (solution_id == 2) {
        cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
        factorialTest(graph, timer, gen);
    } else {
        cout << "[ERROR] ID de solucao invalido! As solucoes disponiveis sao: [1] Solucao Simples "
                "e [2] Teste Fatorial."
             << endl;
        return 1;
    }

    delete graph;
    return 0;
}

void factorialTest(Graph* graph, Timer& timer, mt19937& gen) {
    const int n = graph->getNumVertices() - 1;

    // Define criterios de parada
    const vector<int> grasp_maxes = {n * 10, n * 100, n * 1000};
    const vector<int> max_iterations_local_search = {(int)(0.5 * n), n, 2 * n};

    // Define alphas
    const vector<double> alphas = {0.01, 0.05, 0.1, 0.2};

    // Inicializa csv
    const vector<string> csv_labels = {"GraspMAX", "Iterações Busca Local", "Alpha", "FO",
                                       "Duração (ms)"};
    string csv_path = "Tables/grasp_tsp.csv";
    CsvBuilder* csv_builder = new CsvBuilder(csv_path, csv_labels);

    int i = 0;

    // Grasp Max
    for (const auto& grasp_max : grasp_maxes) {
        // Iteracoes Busca Local
        for (const auto& max_iteration_local_search : max_iterations_local_search) {
            // Alpha
            for (const auto& alpha : alphas) {
                const auto grasp_start = chrono::steady_clock::now();

                // Grasp
                auto [best_fo, best_solution] =
                    grasp(graph, grasp_max, alpha, max_iteration_local_search, gen);

                cout << "[INFO] Configuracao " << ++i << " concluida!" << endl;

                const auto grasp_end = chrono::steady_clock::now();
                const chrono::duration<double, milli> grasp_duration = grasp_end - grasp_start;

                vector<double> csv_values = {(double)grasp_max, (double)max_iteration_local_search,
                                             alpha, (double)best_fo,
                                             (double)grasp_duration.count()};
                csv_builder->addLine(csv_values);
            }
        }
    }

    cout << "[INFO] Tabela " << csv_path << " construida com sucesso!" << endl;
    timer.stop();
    cout << endl;

    delete csv_builder;
    return;
}

void solve(Graph* graph, Timer& timer, mt19937& gen) {
    const int n = graph->getNumVertices() - 1;

    // Define criterios de parada
    const int grasp_max = 2000;
    const int max_iterations_local_search = 50;

    // Define alpha
    const double alpha = 0.02;

    // Grasp
    int best_fo;
    vector<int> best_solution;
    tie(best_fo, best_solution) = grasp(graph, grasp_max, alpha, max_iterations_local_search, gen);

    timer.stop();
    cout << endl;
    string title = "Grasp para o TSP";
    printSolutionTSP(best_solution, best_fo, title);

    return;
}
