#include <iostream>
#include <random>
#include <vector>

#include "build_csv.hpp"
#include "io.hpp"
#include "sa_tsp.hpp"
#include "timer.hpp"

using namespace std;

void factorialTest(const vector<int>& curr_solution, const int curr_fo, Graph* graph, mt19937& gen,
				   Timer& timer);
void solve(const vector<int>& curr_solution, const int curr_fo, Graph* graph, mt19937& gen,
		   Timer& timer);

int main(int argc, char** argv) {
	random_device rd;
	mt19937 gen(rd());

	string label = "Simulated Annealing para o Probema do Caixeiro Viajante (TSP)";
	Timer timer(label);

	// Coleta o arquivo de entrada
	Io* io = new Io();
	string input_file_name = io->getInputFileName(argc, argv);
	if (input_file_name == "") {
		cerr << "[ERROR] Arquivo de entrada nao especificado." << endl;
		return 1;
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

	// Solução inicial gulosa
	vector<int> curr_solution = getGreedySolutionTSP(graph, n, gen, true);
	int curr_fo = objectiveFunctionTSP(curr_solution, graph, false);

	// Obtém o ID da solução
	int solution_id = io->getSolutionId(argc, argv);

	if (solution_id == 1) {	 // Solução normal
		cout << endl << "[INFO] Opcao \'Solucao\' selecionada!" << endl << endl;
		solve(curr_solution, curr_fo, graph, gen, timer);
	} else if (solution_id == 2) {	// Teste fatorial
		cout << endl << "[INFO] Opcao \'Teste Fatorial\' selecionada!" << endl << endl;
		factorialTest(curr_solution, curr_fo, graph, gen, timer);
	} else {
		cerr << "[ERROR] ID de solucao invalido!" << endl;
		// TODO: espeicificar o comando correto de execução
		return 1;
	}
	delete graph;
	return 0;
}

void factorialTest(const vector<int>& curr_solution, const int curr_fo, Graph* graph, mt19937& gen,
				   Timer& timer) {
	// Valores a serem testados
	const vector<double> temperatures = {1000.0, 10000.0, 100000.0, 1000000.0};
	const vector<double> alphas = {0.9, 0.95, 0.99};

	// Iterações por temperatura
	const int sa = graph->getNumVertices() - 1;

	// Inicializa csv
	int table_idx = 1;
	const vector<string> csv_labels = {"Temperatura", "Alpha", "SA", "FO"};
	string csv_path = "Tables/sa_tsp.csv";
	CsvBuilder* csv_builder = new CsvBuilder(csv_path, csv_labels);

	// Temperatura inicial
	for (const auto& temperature : temperatures) {
		// Fator de esfriamento
		for (const auto& alpha : alphas) {
			// Simulated Annealing
			auto [best_fo, best_solution] =
				simulatedAnnealingTSP(curr_solution, temperature, alpha, sa, graph, gen);

			vector<double> csv_values = {temperature, alpha, (double)sa, (double)best_fo};
			csv_builder->addLine(csv_values);
		}
	}

	cout << "[INFO] Tabela " << csv_path << " construida com sucesso!" << endl;
	timer.stop();
	cout << endl;

	delete csv_builder;
	return;
}

void solve(const vector<int>& curr_solution, const int curr_fo, Graph* graph, mt19937& gen,
		   Timer& timer) {
	// Temperatura
	const double temperature = 10000.0;

	// Fator de esfriamento
	const double alpha = 0.95;

	// Iterações por temperatura
	const int sa = graph->getNumVertices() - 1;

	// Simulated Annealing
	auto [best_fo, best_solution] =
		simulatedAnnealingTSP(curr_solution, temperature, alpha, sa, graph, gen);

	// Imprime solução encontrada e o tempo gasto
	timer.stop();
	cout << endl;
	string title = "Simulated Annealing para o TSP";
	printSolutionTSP(best_solution, best_fo, title);
}
