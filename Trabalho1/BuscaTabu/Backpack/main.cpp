#include <cmath>
#include <iostream>
#include <vector>

#include "backpack.hpp"
#include "bt_backpack.hpp"
#include "build_csv.hpp"
#include "io.hpp"
#include "timer.hpp"

using namespace std;

#define DEFAULT_INPUT_FILE "knapPI_1_2000_1000_1"

void factorialTest(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack,
                   Timer& timer);
void solve(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack, Timer& timer);

int main(int argc, char** argv) {
    string label = "Busca Tabu para o o Problema da Mochila 0/1";
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

    // Solucao inicial gulosa
    auto [fo, solution] = greedySolutionBackpack(backpack);

    // Obtém o ID da solução
    int solution_id = io->getSolutionId(argc, argv);

    if (solution_id == 1) {  // Solução normal
        cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
        solve(solution, fo, backpack, timer);
    } else if (solution_id == 2) {  // Teste fatorial
        cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
        factorialTest(solution, fo, backpack, timer);
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
                   Timer& timer) {
    const int n = backpack->items.size();

    // Define criterios de parada
    const vector<int> max_iterations = {n, 10 * n, 100 * n};

    // Define o tempo de vida de um elemento na lista tabu
    const vector<int> tabu_list_ttls = {1, 3, 5, 10, 20, 50};

    // Inicializa csv
    const vector<string> csv_labels = {"Iterações", "Iterações Sem Melhora", "TTL", "FO",
                                       "Duração (ms)"};
    string csv_path = "Tables/bt_backpack.csv";
    CsvBuilder* csv_builder = new CsvBuilder(csv_path, csv_labels);

    int i = 0;

    // Iteracoes
    for (const auto& max_iteration : max_iterations) {
        // Duracoes tabu
        for (const auto& ttl : tabu_list_ttls) {
            int iterations_without_improvement = sqrt(max_iteration);

            const auto grasp_start = chrono::steady_clock::now();

            // Busca Tabu
            auto [best_fo, best_solution] =
                tabuSearchBackpack(curr_solution, curr_fo, max_iteration,
                                    iterations_without_improvement, ttl, backpack);

            cout << "[INFO] Configuracao " << ++i << " concluida!" << endl;

            const auto grasp_end = chrono::steady_clock::now();
            const chrono::duration<double, milli> grasp_duration = grasp_end - grasp_start;

            vector<double> csv_values = {(double)max_iteration,
                                         (double)iterations_without_improvement, (double)ttl,
                                         (double)best_fo, (double)grasp_duration.count()};
            csv_builder->addLine(csv_values);
        }
    }

    cout << "[INFO] Tabela " << csv_path << " construida com sucesso!" << endl;
    timer.stop();
    cout << endl;

    delete csv_builder;
    return;
}

void solve(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack, Timer& timer) {
    const int n = backpack->items.size();

    // Define criterios de parada
    const int max_iterations = 1000 * n;
    const int max_iterations_without_improvement = sqrt(max_iterations);

    // Define o tempo de vida de um elemento na lista tabu
    const int ttl_tabu_list = 3;

    // Busca Tabu
    auto [best_fo, best_solution] =
        tabuSearchBackpack(curr_solution, curr_fo, max_iterations,
                           max_iterations_without_improvement, ttl_tabu_list, backpack);

    // Imprime a solucao encontrada e o tempo gasto
    timer.stop();
    cout << endl;
    string title = "Buca Tabu para o Problema da Mochila";
    printSolutionBackpack(best_solution, best_fo, title);

    return;
}
