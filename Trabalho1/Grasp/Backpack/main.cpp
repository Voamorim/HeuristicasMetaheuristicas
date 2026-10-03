#include <chrono>
#include <fstream>
#include <iostream>
#include <random>

#include "backpack.hpp"
#include "build_csv.hpp"
#include "grasp_backpack.hpp"
#include "io.hpp"
#include "timer.hpp"

using namespace std;

#define DEFAULT_INPUT_FILE "knapPI_1_2000_1000_1"

void factorialTest(Backpack* backpack, Timer& timer, mt19937& gen);
void solve(Backpack* backpack, Timer& timer, mt19937& gen);

int main(int argc, char** argv) {
    random_device rd;
    mt19937 gen(rd());

    string label = "Grasp para o Problema da Mochila 0/1";
    Timer timer(label);

    // Coleta o arquivo de entrada
    Io* io = new Io();
    string input_file_name = io->getInputFileName(argc, argv);
    if (input_file_name == "") {
        input_file_name = DEFAULT_INPUT_FILE;
        cerr << "[INFO] Arquivo de entrada nao especificado. Utilizando o arquivo "
             << input_file_name << endl;
    }
    string input_path = "../../Input/Backpack/" + input_file_name;
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

    // Le o problema da entrada
    Backpack* backpack = readInputBackpack();
    const int n = backpack->items.size();
    cout << "[INFO] Mochila lida com sucesso!" << endl << endl;
    cin.rdbuf(cin_buffer);

    // Obtém o ID da solução
    int solution_id = io->getSolutionId(argc, argv);

    if (solution_id == 1) {  // Solução normal
        cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
        solve(backpack, timer, gen);
    } else if (solution_id == 2) {  // Teste fatorial
        cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
        factorialTest(backpack, timer, gen);
    } else {
        cout << "[ERROR] ID de solucao invalido! As solucoes disponiveis sao: [1] Solucao Simples "
                "e [2] Teste Fatorial."
             << endl;
        return 1;
    }

    delete backpack;
    return 0;
}

void factorialTest(Backpack* backpack, Timer& timer, mt19937& gen) {
    const int n = backpack->items.size();

    // Define criterios de parada
    const vector<int> grasp_maxes = {(int)(0.5 * n), n, n * 10};
    const vector<int> max_iterations_local_search = {5, 10};

    // Define alphas
    const vector<double> alphas = {0.1, 0.5, 0.9};

    // Inicializa csv
    const vector<string> csv_labels = {"GraspMAX", "Iterações Busca Local", "Alpha", "FO",
                                       "Duração (ms)"};
    string csv_path = "Tables/grasp_backpack.csv";
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
                    graspBackpack(backpack, grasp_max, alpha, max_iteration_local_search, gen);

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

void solve(Backpack* backpack, Timer& timer, mt19937& gen) {
    const int n = backpack->items.size();

    // Define criterios de parada
    const int grasp_max = n;
    const int max_iterations_local_search = 5;

    // Define alphas
    const double alpha = 0.1;

    // Grasp
    auto [best_fo, best_solution] =
        graspBackpack(backpack, grasp_max, alpha, max_iterations_local_search, gen);

    // Imprime a solucao encontrada e o tempo gasto
    timer.stop();
    cout << endl;
    string title = "Grasp para o Problema da Mochila";
    printSolutionBackpack(best_solution, best_fo, title);

    return;
}
