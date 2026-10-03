#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

#include "bt_tsp.hpp"
#include "build_csv.hpp"
#include "io.hpp"
#include "timer.hpp"
#include "tsp.hpp"

using namespace std;

#define DEFAULT_INPUT_FILE "bier127.tsp"

void factorialTest(const vector<int>& curr_solution, const int curr_fo, Graph* graph, Timer& timer);
void solve(const vector<int>& curr_solution, const int curr_fo, Graph* graph, Timer& timer);

int main(int argc, char** argv) {
    random_device rd;
    mt19937 gen(rd());

    string label = "Busca Tabu para o Problema do Caixeiro Viajante (TSP)";
    Timer timer(label);

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
        cout << "[INFO] Arquivo de entrada " << input_file_name << " lido com sucesso!" << endl
             << endl;
    }
    delete io;

    // Le o grafo da entrada
    Graph* graph = new Graph();
    graph->readInput();
    cout << "[INFO] Grafo lido com sucesso!" << endl << endl;
    cin.rdbuf(cin_buffer);

    const int n = graph->getNumVertices() - 1;

    // Solucao inicial gulosa
    vector<int> greedy_solution = getGreedySolutionTSP(graph, n, gen, true);
    int greedy_fo = objectiveFunctionTSP(greedy_solution, graph, false);

    // Obtem o ID da solucao
    int solution_id = io->getSolutionId(argc, argv);

    if (solution_id == 1) {  // Solucao normal
        cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
        solve(greedy_solution, greedy_fo, graph, timer);
    } else if (solution_id == 2) {  // Teste fatorial
        cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
        factorialTest(greedy_solution, greedy_fo, graph, timer);
    } else {
        cout << "[ERROR] ID de solucao invalido! As solucoes disponiveis sao: [1] Solucao Simples "
                "e [2] Teste Fatorial."
             << endl;
        return 1;
    }

    delete graph;
    return 0;
}

void factorialTest(const vector<int>& curr_solution, const int curr_fo, Graph* graph,
                   Timer& timer) {
    const int n = graph->getNumVertices() - 1;

    // Crterio de parada
    const vector<int> max_iterations = {n, 10 * n, 100 * n, 1000 * n};

    // Tempo de vida de um elemento na lista tabu
    const vector<int> tabu_list_ttls = {1, 3, 5, 10};

    // Inicializa csv
    const vector<string> csv_labels = {"Iterações", "Iterações sem Melhora", "TTL", "FO",
                                       "Duração (ms)"};
    string csv_path = "Tables/bt_tsp.csv";
    CsvBuilder* csv_builder = new CsvBuilder(csv_path, csv_labels);

    int i = 0;

    // Iteracoes
    for (const auto& max_iteration : max_iterations) {
        // Duracoes tabu
        for (const auto& ttl : tabu_list_ttls) {
            // Maximo de iteracoes sem melhora (usar/nao usar)
            for (int use = 0; use <= 1; ++use) {
                int iterations_without_improvement;
                if (use) {
                    iterations_without_improvement = sqrt(max_iteration);
                } else {
                    iterations_without_improvement = max_iteration;
                }

                const auto bt_start = chrono::steady_clock::now();

                // Busca Tabu
                auto [best_fo, best_solution] =
                    tabuSearchTSP(curr_solution, curr_fo, graph, ttl, max_iteration,
                                  iterations_without_improvement);

                cout << "[INFO] Configuracao " << ++i << " concluida!" << endl;

                const auto bt_end = chrono::steady_clock::now();
                const chrono::duration<double, milli> bt_duration = bt_end - bt_start;

                vector<double> csv_values = {(double)max_iteration,
                                             (double)iterations_without_improvement, (double)ttl,
                                             (double)best_fo, (double)bt_duration.count()};
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

void solve(const vector<int>& curr_solution, const int curr_fo, Graph* graph, Timer& timer) {
    const int n = graph->getNumVertices() - 1;

    // Define criterios de parada
    const int max_iterations = 1000 * n;
    const int max_iterations_without_improvement = sqrt(max_iterations);

    // Tempo de vida de um elemento na lista tabu
    const int tabu_list_ttl = 3;

    // Busca Tabu
    auto [best_fo, best_solution] =
        tabuSearchTSP(curr_solution, curr_fo, graph, tabu_list_ttl, max_iterations,
                      max_iterations_without_improvement);

    // Imprime a solucao final encontrada e o tempo gasto
    timer.stop();
    cout << endl;
    string title = "Busca Tabu para o TSP";
    printSolutionTSP(best_solution, best_fo, title);

    return;
}
