#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

#include "backpack.hpp"
#include "bt_backpack.hpp"
#include "build_csv.hpp"
#include "io.hpp"
#include "timer.hpp"

using namespace std;

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
		cerr << "[ERROR] Arquivo de entrada nao especificado." << endl;
		return 1;
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

	if (solution_id == 1) {	 // Solução normal
		cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
		solve(solution, fo, backpack, timer);
	} else if (solution_id == 2) {	// Teste fatorial
		cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
		factorialTest(solution, fo, backpack, timer);
	} else {
		cout << "[ERROR] ID de solucao invalido!" << endl;
		// TODO: especificar o formato certo do comando de make run
		return 1;
	}
	delete backpack;
	return 0;
}

void factorialTest(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack,
				   Timer& timer) {}

void solve(const vector<bool>& curr_solution, const int curr_fo, Backpack* backpack, Timer& timer) {
	// Busca Tabu
	auto [best_fo, best_solution] = tabuSearchBackpack(curr_solution, curr_fo, backpack, timer);
}
