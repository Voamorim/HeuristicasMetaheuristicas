#include <chrono>
#include <iostream>
#include <random>
#include <string>
#include <vector>

#include "backpack.hpp"
#include "build_csv.hpp"
#include "io.hpp"
#include "sa_backpack.hpp"
#include "timer.hpp"

using namespace std;

#define DEFAULT_INPUT_FILE "knapPI_1_2000_1000_1"

void factorialTest(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack,
                   mt19937& gen, Timer& timer);
void solve(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack, mt19937& gen,
           Timer& timer);

int main(int argc, char** argv) {
    random_device rd;
    mt19937 gen(rd());

    string label = "Simulated Annealing para o o Problema da Mochila 0/1";
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
        cout << "[INFO] Arquivo de entrada " << input_file_name << " lido com sucesso!" << endl;
    }
    delete io;

    // Le o problema da entrada
    Backpack* backpack = readInputBackpack();
    const int n = backpack->items.size();
    cout << "[INFO] Mochila lida com sucesso!" << endl << endl;
    cin.rdbuf(cin_buffer);

    // Solucao inicial gulosa
    auto [greedy_fo, greedy_solution] = greedySolutionBackpack(backpack);

    // Obtém o ID da solução
    int solution_id = io->getSolutionId(argc, argv);

    if (solution_id == 1) {  // Solução normal
        cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
        solve(greedy_solution, greedy_fo, backpack, gen, timer);
    } else if (solution_id == 2) {  // Teste fatorial
        cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
        factorialTest(greedy_solution, greedy_fo, backpack, gen, timer);
    } else {
        cout << "[ERROR] ID de solucao invalido! As solucoes disponiveis sao: [1] Solucao Simples "
                "e [2] Teste Fatorial."
             << endl;
        return 1;
    }
    delete backpack;
    return 0;
}

void factorialTest(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack,
                   mt19937& gen, Timer& timer) {
    // Valores a serem testados
    const vector<double> temperatures = {1000.0, 10000.0, 100000.0, 1000000.0};
    const vector<double> alphas = {0.9, 0.95, 0.99};

    // Iterações por temperatura
    const int sa = backpack->items.size();

    // Inicializa csv
    const vector<string> csv_labels = {"Temperatura", "Alpha", "SA", "FO", "Duração (ms)"};
    string csv_path = "Tables/sa_backpack.csv";
    CsvBuilder* csv_builder = new CsvBuilder(csv_path, csv_labels);

    int i = 0;

    // Temperatura inicial
    for (const auto& temperature : temperatures) {
        // Fator de esfriamento
        for (const auto& alpha : alphas) {
            const auto sa_start = chrono::steady_clock::now();

            // Simulated Annealing
            auto [best_fo, best_solution] =
                simulatedAnnealingBackpack(curr_solution, temperature, alpha, sa, backpack, gen);

            cout << "[INFO] Configuracao " << ++i << " concluida!" << endl;

            const auto sa_end = chrono::steady_clock::now();
            const chrono::duration<double, milli> sa_duration = sa_end - sa_start;

            vector<double> csv_values = {temperature, alpha, (double)sa, (double)best_fo,
                                         (double)sa_duration.count()};
            csv_builder->addLine(csv_values);
        }
    }
    cout << "[INFO] Tabela " << csv_path << " construida com sucesso!" << endl;
    timer.stop();
    cout << endl;

    delete csv_builder;
    return;
}

void solve(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack, mt19937& gen,
           Timer& timer) {
    // Temperatura
    const double temperature = 10000.0;

    // Fator de esfriamento
    const double alpha = 0.95;

    // Iterações por temperatura
    const int sa = backpack->items.size();

    // Simulated Annealing
    auto [best_fo, best_solution] =
        simulatedAnnealingBackpack(curr_solution, temperature, alpha, sa, backpack, gen);

    // Imprime a solução encontrada e o tempo gasto
    timer.stop();
    cout << endl;
    string title = "Simulated Annealing para o Problema da Mochila";
    printSolutionBackpack(best_solution, best_fo, title);

    return;
}
